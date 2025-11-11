/**
 * @file camarim.cpp
 * @brief Implementação da classe Camarim e GerenciadorCamarins
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa toda a lógica de gerenciamento de camarins e itens.
 */

// Inclui o header da classe
#include "camarim.h"
// Inclui exceções customizadas
#include "excecoes.h"
// Algoritmos STL (find, remove_if, etc)
#include <algorithm>
// Para usar stringstream (construir strings formatadas)
#include <sstream>
// Para formatação (setw, left, etc)
#include <iomanip>

// ==================== Classe Camarim ====================

/**
 * Construtor padrão - inicializa com valores vazios/zero
 */
Camarim::Camarim() : id(0), nome(""), artistaId(0) {}
// Lista de inicialização: mais eficiente que atribuição no corpo

/**
 * Construtor parametrizado - inicializa com valores fornecidos
 */
Camarim::Camarim(int id, const string& nome, int artistaId)
    : id(id), nome(nome), artistaId(artistaId) {}
// Inicializa diretamente os atributos privados
// artistaId = 0 significa que não há artista associado ainda

/**
 * Destrutor - libera recursos
 */
Camarim::~Camarim() {}
// Map é destruído automaticamente (RAII - Resource Acquisition Is Initialization)

// ==================== GETTERS (métodos const que retornam valores) ====================

/**
 * Retorna o ID do camarim
 */
int Camarim::getId() const {
    return id;  // Retorna cópia do atributo privado
}

/**
 * Retorna o nome do camarim
 */
string Camarim::getNome() const {
    return nome;  // Retorna cópia da string
}

/**
 * Retorna o ID do artista associado
 */
int Camarim::getArtistaId() const {
    return artistaId;  // 0 = sem artista
}

// ==================== SETTERS (métodos que modificam atributos) ====================

/**
 * Define o ID do camarim com validação
 */
void Camarim::setId(int id) {
    if (id < 0) {  // Validação: ID não pode ser negativo
        throw ValidacaoException("ID do camarim inválido");
        // Lança exceção específica de validação
    }
    this->id = id;  // this-> diferencia parâmetro de atributo
}

/**
 * Define o nome do camarim com validação
 */
void Camarim::setNome(const string& nome) {
    if (nome.empty()) {  // Validação: nome não pode ser vazio
        throw ValidacaoException("Nome do camarim não pode ser vazio");
    }
    this->nome = nome;  // Atualiza atributo privado
}

/**
 * Define o artista associado ao camarim
 */
void Camarim::setArtistaId(int artistaId) {
    this->artistaId = artistaId;  // Permite 0 (sem artista)
}

/**
 * Adiciona ou atualiza quantidade de um item no camarim
 */
void Camarim::inserirItem(int itemId, const string& nomeItem, int quantidade) {
    // VALIDAÇÕES:
    if (itemId < 0) {  // ID deve ser positivo
        throw ValidacaoException("ID do item inválido");
    }
    
    if (nomeItem.empty()) {  // Nome não pode ser vazio
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (quantidade <= 0) {  // Quantidade deve ser positiva
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    // MAP: find() retorna iterator para o elemento ou end() se não encontrar
    if (itens.find(itemId) != itens.end()) {
        // Item JÁ EXISTE no camarim: soma à quantidade existente
        itens[itemId].quantidade += quantidade;
        // Acesso por [] no map retorna referência ao valor
    } else {
        // Item NÃO EXISTE: cria novo ItemCamarim no map
        itens[itemId] = ItemCamarim(itemId, nomeItem, quantidade);
        // Chama construtor parametrizado de ItemCamarim
        // Insere par chave-valor no map
    }
}

/**
 * Remove quantidade de um item do camarim
 */
bool Camarim::removerItem(int itemId, int quantidade) {
    // Verifica se item existe no camarim
    if (itens.find(itemId) == itens.end()) {
        // find() == end() significa que não encontrou
        throw CamarimException("Item não encontrado no camarim");
    }
    
    if (quantidade <= 0) {  // Validação de quantidade
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    if (itens[itemId].quantidade < quantidade) {
        // Não há quantidade suficiente no camarim
        throw CamarimException("Quantidade insuficiente no camarim");
    }
    
    // Subtrai quantidade
    itens[itemId].quantidade -= quantidade;
    
    // Se quantidade chegar a zero, remove item do map
    if (itens[itemId].quantidade == 0) {
        itens.erase(itemId);  // erase() remove elemento do map
    }
    
    return true;  // Sucesso na remoção
}

/**
 * Exibe todas as informações do camarim formatadas
 */
string Camarim::exibir() const {
    stringstream ss;  // String stream para construir string formatada
    ss << "=== CAMARIM ===" << endl;
    ss << "ID: " << id << endl;
    ss << "Nome: " << nome << endl;
    ss << "Artista ID: " << artistaId << endl;
    
    // Calcula total de itens percorrendo o map
    int total = 0;
    for (const auto& par : itens) {  
        // Range-based for: percorre cada par chave-valor do map
        // auto& = tipo deduzido automaticamente (pair<int, ItemCamarim>)
        // const = não modifica o par
        
        total += par.second.quantidade;
        // par.first = chave (itemId)
        // par.second = valor (ItemCamarim)
        // Soma quantidade de cada item
    }
    ss << "Total de itens: " << total << endl;
    
    ss << "\nItens:" << endl;  // \n = quebra de linha
    
    if (itens.empty()) {  // Se map está vazio
        ss << "  Nenhum item no camarim" << endl;
    } else {
        // Cabeçalho da tabela com formatação
        ss << left << setw(5) << "  ID" << setw(30) << "Nome" 
           << setw(10) << "Quantidade" << endl;
        // left = alinhamento à esquerda
        // setw(n) = define largura de n caracteres
        
        ss << "  " << string(42, '-') << endl;
        // string(n, char) = cria string com n repetições do caractere
        // Linha separadora com 42 hífens
        
        // Percorre todos os itens do map
        for (const auto& par : itens) {
            const ItemCamarim& item = par.second;
            // Referência constante ao ItemCamarim (evita cópia)
            
            ss << left << setw(5) << "  " + to_string(item.itemId)
               << setw(30) << item.nomeItem
               << setw(10) << item.quantidade << endl;
            // to_string() = converte número para string
            // Cada linha da tabela formatada
        }
    }
    
    return ss.str();  // Converte stringstream para string
}

/**
 * Sobrecarga do operador << para permitir cout << camarim
 */
ostream& operator<<(ostream& os, const Camarim& camarim) {
    // ostream& = referência a stream de saída (cout, ofstream, etc)
    // Retorna referência para permitir encadeamento: cout << c1 << c2;
    
    os << camarim.exibir();  // Chama método exibir() e insere no stream
    return os;  // Retorna stream para permitir encadeamento
}

// ==================== Classe GerenciadorCamarins ====================

/**
 * Construtor - inicializa próximo ID como 1
 */
GerenciadorCamarins::GerenciadorCamarins() : proximoId(1) {}
// IDs começam em 1 (0 geralmente significa "nenhum")

/**
 * Cadastra novo camarim (CREATE)
 */
int GerenciadorCamarins::cadastrar(const string& nome, int artistaId) {
    if (nome.empty()) {  // Validação: nome obrigatório
        throw ValidacaoException("Nome do camarim não pode ser vazio");
    }
    
    // Cria novo camarim com ID automático
    Camarim novoCamarim(proximoId, nome, artistaId);
    
    // Adiciona ao vector de camarins
    camarins.push_back(novoCamarim);
    // push_back() adiciona ao final do vector (faz cópia do objeto)
    
    return proximoId++;  // Retorna ID usado e incrementa para próximo
    // Pós-incremento: retorna valor atual, depois incrementa
}

/**
 * Busca camarim por ID (READ)
 */
Camarim* GerenciadorCamarins::buscarPorId(int id) {
    // Range-based for com referência não-const (permite modificação)
    for (auto& camarim : camarins) {
        // auto& = referência a cada Camarim no vector
        // & = não faz cópia, permite modificar original
        
        if (camarim.getId() == id) {  // Se encontrou
            return &camarim;  // Retorna PONTEIRO para o objeto no vector
            // & = operador address-of (retorna endereço do objeto)
        }
    }
    return nullptr;  // Não encontrado: retorna ponteiro nulo
}

/**
 * Busca camarim por artista associado (READ)
 */
Camarim* GerenciadorCamarins::buscarPorArtista(int artistaId) {
    for (auto& camarim : camarins) {
        if (camarim.getArtistaId() == artistaId) {
            return &camarim;  // Retorna ponteiro para o camarim encontrado
        }
    }
    return nullptr;  // Artista não tem camarim associado
}

/**
 * Remove camarim por ID (DELETE)
 */
bool GerenciadorCamarins::remover(int id) {
    // PADRÃO REMOVE-ERASE:
    // 1. remove_if move elementos a remover para o final
    // 2. erase remove elementos do final
    
    auto it = remove_if(camarins.begin(), camarins.end(),
                       [id](const Camarim& c) { return c.getId() == id; });
    // remove_if(início, fim, predicado) 
    // Retorna iterator para primeiro elemento "removido"
    // LAMBDA: [id](const Camarim& c) { return c.getId() == id; }
    //   [id] = captura variável id por valor
    //   (const Camarim& c) = parâmetro (cada camarim)
    //   { return ... } = corpo da função (critério de remoção)
    
    if (it != camarins.end()) {  // Se encontrou elemento(s) a remover
        camarins.erase(it, camarins.end());
        // erase(início, fim) remove range do vector
        // Remove todos desde it até o final
        return true;  // Sucesso
    }
    return false;  // Não encontrado
}

/**
 * Lista todos os camarins (READ ALL)
 */
vector<Camarim> GerenciadorCamarins::listar() const {
    return camarins;  // Retorna CÓPIA do vector completo
    // Vector faz deep copy de todos os objetos
}

/**
 * Atualiza dados de um camarim (UPDATE)
 */
bool GerenciadorCamarins::atualizar(int id, const string& nome, int artistaId) {
    Camarim* camarim = buscarPorId(id);
    // Busca ponteiro para o camarim (nullptr se não encontrar)
    
    if (camarim == nullptr) {  // Verifica se encontrou
        throw CamarimException("Camarim com ID " + to_string(id) + " não encontrado");
        // Concatenação de strings com operador +
    }
    
    // Atualiza campos usando setters (que fazem validação)
    camarim->setNome(nome);
    // -> = acesso a membro através de ponteiro (equivale a (*camarim).setNome(nome))
    camarim->setArtistaId(artistaId);
    
    return true;  // Sucesso na atualização
}
