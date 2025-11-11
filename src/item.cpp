/**
 * @file item.cpp
 * @brief Implementação da classe Item e GerenciadorItens
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

// Inclui o header da classe Item com as declarações
#include "item.h"
// Inclui as classes de exceções customizadas do sistema
#include "excecoes.h"
// Inclui algoritmos da STL (find_if, remove_if, etc)
#include <algorithm>
// Inclui stringstream para manipulação de strings
#include <sstream>
// Inclui manipuladores de formato (setprecision, fixed)
#include <iomanip>

// ==================== Classe Item ====================

// Construtor padrão - Inicializa item com valores padrão
// Lista de inicialização (:) inicializa atributos antes do corpo do construtor
Item::Item() : id(0), nome(""), preco(0.0) {}  
// id = 0, nome = string vazia, preco = 0.0

// Construtor parametrizado - Recebe valores como parâmetros
Item::Item(int id, const string& nome, double preco)
    : id(id), nome(nome), preco(preco) {}  
// Inicializa os atributos com os valores recebidos como parâmetros
// const string& = referência constante (não copia a string, economiza memória)

// Destrutor - Executado quando objeto é destruído
Item::~Item() {}  
// Corpo vazio porque não há recursos dinâmicos para liberar (sem new/malloc)

// ==================== Getters ====================
// Métodos para LER os valores dos atributos privados
// const após a assinatura = método não modifica o estado do objeto

int Item::getId() const {
    return id;  // Retorna cópia do valor do id
}

string Item::getNome() const {
    return nome;  // Retorna cópia da string nome
}

double Item::getPreco() const {
    return preco;  // Retorna cópia do valor do preço
}

// ==================== Setters com Validação ====================
// Métodos para MODIFICAR os valores dos atributos privados
// Incluem validações para garantir integridade dos dados

void Item::setId(int id) {
    if (id < 0) {  // VALIDAÇÃO: id não pode ser negativo
        // Lança exceção se a validação falhar
        throw ValidacaoException("ID do item não pode ser negativo");
    }
    this->id = id;  // this-> diferencia o atributo do parâmetro
    // Só atribui se passou na validação
}

void Item::setNome(const string& nome) {
    if (nome.empty()) {  // VALIDAÇÃO: nome não pode ser string vazia
        // empty() retorna true se a string está vazia
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    this->nome = nome;  // Atribui o novo nome ao atributo
}

void Item::setPreco(double preco) {
    if (preco < 0) {  // VALIDAÇÃO: preço não pode ser negativo (mas pode ser 0 = grátis)
        throw ValidacaoException("Preço do item não pode ser negativo");
    }
    this->preco = preco;  // Atribui o novo preço ao atributo
}

// Exibe informações do item formatadas
string Item::exibir() const {
    stringstream ss;  // Cria um stream de string para construir a saída formatada
    ss << fixed << setprecision(2);  
    // fixed = notação decimal fixa (não científica)
    // setprecision(2) = 2 casas decimais após a vírgula (ex: 2.50)
    
    ss << "Item [ID: " << id << ", Nome: " << nome 
       << ", Preço: R$ " << preco << "]";
    // Concatena as informações do item em uma string formatada
    
    return ss.str();  // str() converte o stringstream para string e retorna
}

// Sobrecarga do operador << para permitir cout << item
ostream& operator<<(ostream& os, const Item& item) {
    os << item.exibir();  // Usa o método exibir() para formatar a saída
    return os;  // Retorna o stream para permitir encadeamento (cout << item1 << item2)
}

// Sobrecarga do operador == para comparar dois itens
bool Item::operator==(const Item& outro) const {
    return this->id == outro.id;  // Compara apenas pelo ID (identificador único)
    // Retorna true se IDs são iguais, false caso contrário
}

// ==================== Classe GerenciadorItens ====================

// Construtor - Inicializa o gerenciador
GerenciadorItens::GerenciadorItens() : proximoId(1) {}  
// Inicializa proximoId com 1 (primeiro ID disponível)
// Vetor itens é inicializado automaticamente vazio

// Cadastra novo item no sistema
int GerenciadorItens::cadastrar(const string& nome, double preco) {
    // ========== VALIDAÇÕES ==========
    
    if (nome.empty()) {  // Verifica se o nome está vazio
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (preco < 0) {  // Verifica se o preço é negativo
        throw ValidacaoException("Preço do item não pode ser negativo");
    }
    
    // Verifica se já existe item com este nome
    if (buscarPorNome(nome) != nullptr) {  // nullptr = ponteiro nulo
        // Se encontrou (não é nullptr), lança exceção
        throw ItemException("Item já existe com este nome: " + nome);
    }
    
    // ========== CADASTRO ==========
    
    Item novoItem(proximoId, nome, preco);  // Cria novo item com ID atual
    itens.push_back(novoItem);  // Adiciona o item no FINAL do vetor
    // push_back() adiciona elemento ao final do vector
    
    return proximoId++;  // Retorna o ID usado e depois incrementa para o próximo
    // proximoId++ = usa o valor atual, DEPOIS incrementa
}

// Busca item por ID no vetor
Item* GerenciadorItens::buscarPorId(int id) {
    // Range-based for: percorre cada elemento do vetor
    for (auto& item : itens) {  // auto = tipo deduzido automaticamente (Item)
        // & = referência (não copia o item, acessa diretamente)
        
        if (item.getId() == id) {  // Se encontrou o item com este ID
            return &item;  // Retorna PONTEIRO para o item (endereço de memória)
            // & = operador de endereço (retorna ponteiro)
        }
    }
    return nullptr;  // Se não encontrou, retorna ponteiro nulo
}

// Busca item por nome no vetor
Item* GerenciadorItens::buscarPorNome(const string& nome) {
    // Percorre todos os itens do vetor
    for (auto& item : itens) {
        if (item.getNome() == nome) {  // Compara o nome do item com o nome buscado
            return &item;  // Se encontrou, retorna ponteiro para o item
        }
    }
    return nullptr;  // Se não encontrou, retorna nullptr
}

// Remove item por ID do vetor
bool GerenciadorItens::remover(int id) {
    // Usa algoritmo remove_if da STL (Standard Template Library)
    auto it = remove_if(itens.begin(), itens.end(),
                       [id](const Item& i) { return i.getId() == id; });
    // remove_if move elementos que atendem à condição para o final
    // Lambda [id]: captura a variável id do escopo externo
    // Lambda (const Item& i): recebe cada item como parâmetro
    // Lambda { return ... }: retorna true se o item deve ser removido
    // Retorna iterador apontando para o início dos elementos "removidos"
    
    if (it != itens.end()) {  // Se encontrou elementos para remover
        // end() retorna iterador para "após o último elemento"
        itens.erase(it, itens.end());  // erase() realmente REMOVE do vetor
        // Remove do iterador 'it' até o fim
        return true;  // Retorna true indicando sucesso
    }
    return false;  // Retorna false se não encontrou o item
}

// Lista todos os itens cadastrados
vector<Item> GerenciadorItens::listar() const {
    return itens;  // Retorna uma CÓPIA do vetor inteiro
    // const = não modifica o estado do gerenciador
}

// Atualiza dados de um item existente
bool GerenciadorItens::atualizar(int id, const string& nome, double preco) {
    // Busca o item pelo ID
    Item* item = buscarPorId(id);  // Recebe ponteiro para o item
    
    if (item == nullptr) {  // Se não encontrou (ponteiro é nulo)
        // Lança exceção informando que o item não existe
        throw ItemException("Item com ID " + to_string(id) + " não encontrado");
        // to_string() converte número para string
    }
    
    // Verifica se o novo nome já está sendo usado por OUTRO item
    Item* itemComNome = buscarPorNome(nome);  // Busca por nome
    if (itemComNome != nullptr && itemComNome->getId() != id) {
        // Se encontrou um item com este nome E não é o próprio item sendo atualizado
        // -> = operador de acesso a membro via ponteiro (equivale a (*item).getId())
        throw ItemException("Já existe outro item com este nome: " + nome);
    }
    
    // Se todas as validações passaram, atualiza os dados
    item->setNome(nome);   // Chama o setter via ponteiro (item->setNome)
    item->setPreco(preco); // Chama o setter via ponteiro
    
    return true;  // Retorna true indicando sucesso na atualização
}
