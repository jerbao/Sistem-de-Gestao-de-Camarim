/**
 * @file estoque.cpp
 * @brief Implementação da classe Estoque
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa controle centralizado de estoque de itens.
 */

// Inclui header da classe
#include "estoque.h"
// Inclui exceções customizadas
#include "excecoes.h"
// Para stringstream (construir strings)
#include <sstream>
// Para formatação (setw, left)
#include <iomanip>

/**
 * Construtor - inicializa map vazio
 */
Estoque::Estoque() {}
// Map é inicializado vazio automaticamente

/**
 * Destrutor - libera recursos
 */
Estoque::~Estoque() {}
// Map é destruído automaticamente (RAII)

/**
 * Adiciona quantidade de item ao estoque (ENTRADA)
 */
void Estoque::adicionarItem(int itemId, const string& nomeItem, int quantidade) {
    // VALIDAÇÕES:
    if (itemId < 0) {  // ID deve ser positivo
        throw ValidacaoException("ID do item inválido");
    }
    
    if (nomeItem.empty()) {  // Nome não pode ser vazio
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (quantidade < 0) {  // Quantidade não pode ser negativa
        throw ValidacaoException("Quantidade não pode ser negativa");
    }
    
    // Verifica se item já existe no estoque
    if (itens.find(itemId) != itens.end()) {
        // Item JÁ EXISTE: SOMA à quantidade existente
        itens[itemId].quantidade += quantidade;
        // Operador [] retorna referência ao ItemEstoque
    } else {
        // Item NÃO EXISTE: cria novo ItemEstoque no map
        itens[itemId] = ItemEstoque(itemId, nomeItem, quantidade);
        // Chama construtor parametrizado de ItemEstoque
    }
}

/**
 * Remove quantidade de item do estoque (SAÍDA)
 */
bool Estoque::removerItem(int itemId, int quantidade) {
    // Verifica se item existe
    if (itens.find(itemId) == itens.end()) {
        // find() == end() = não encontrou
        throw EstoqueException("Item não encontrado no estoque (ID: " + to_string(itemId) + ")");
        // to_string() converte int para string
    }
    
    if (quantidade < 0) {  // Validação de quantidade
        throw ValidacaoException("Quantidade não pode ser negativa");
    }
    
    // Verifica se há quantidade suficiente
    if (itens[itemId].quantidade < quantidade) {
        // EXCEÇÃO DE ESTOQUE INSUFICIENTE (3 níveis de herança!)
        throw EstoqueInsuficienteException(
            "Quantidade insuficiente. Disponível: " + to_string(itens[itemId].quantidade) +
            ", Solicitado: " + to_string(quantidade)
        );
        // Mensagem formatada com valores atuais
    }
    
    // Subtrai quantidade
    itens[itemId].quantidade -= quantidade;
    
    // Remove item do map se quantidade chegar a zero
    if (itens[itemId].quantidade == 0) {
        itens.erase(itemId);  // erase() remove elemento do map
    }
    
    return true;  // Sucesso
}

/**
 * Verifica se há quantidade suficiente de um item
 */
bool Estoque::verificarDisponibilidade(int itemId, int quantidade) const {
    // Busca item no map
    auto it = itens.find(itemId);
    // auto = tipo deduzido (map<int, ItemEstoque>::const_iterator)
    // const_iterator porque método é const
    
    if (it == itens.end()) {  // Item não existe
        return false;  // Não há disponibilidade
    }
    
    // Verifica se quantidade disponível é suficiente
    return it->second.quantidade >= quantidade;
    // it->first = chave (itemId)
    // it->second = valor (ItemEstoque)
    // -> = acesso a membro através de iterator (comporta-se como ponteiro)
}

/**
 * Obtém quantidade atual de um item
 */
int Estoque::obterQuantidade(int itemId) const {
    // Busca item no map
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {  // Item não existe
        return 0;  // Retorna quantidade zero
    }
    
    return it->second.quantidade;  // Retorna quantidade disponível
}

/**
 * Lista todos os itens do estoque
 */
vector<ItemEstoque> Estoque::listar() const {
    vector<ItemEstoque> lista;  // Cria vector vazio
    
    // Percorre todos os itens do map
    for (const auto& par : itens) {
        // Range-based for: percorre cada par chave-valor
        // const auto& = referência constante (não copia, não modifica)
        
        lista.push_back(par.second);
        // par.first = chave (itemId)
        // par.second = valor (ItemEstoque) - este é adicionado ao vector
        // push_back() adiciona cópia ao final do vector
    }
    
    return lista;  // Retorna vector com cópias de todos os ItemEstoque
}

/**
 * Atualiza quantidade de um item (SUBSTITUI valor)
 */
void Estoque::atualizarQuantidade(int itemId, int novaQuantidade) {
    // Verifica se item existe
    if (itens.find(itemId) == itens.end()) {
        throw EstoqueException("Item não encontrado no estoque");
    }
    
    if (novaQuantidade < 0) {  // Validação
        throw ValidacaoException("Quantidade não pode ser negativa");
    }
    
    // SUBSTITUI quantidade (não soma como adicionarItem)
    itens[itemId].quantidade = novaQuantidade;
    
    // Remove item se nova quantidade for zero
    if (novaQuantidade == 0) {
        itens.erase(itemId);
    }
}

/**
 * Exibe informações formatadas do estoque
 */
string Estoque::exibir() const {
    stringstream ss;  // String stream para construir string
    ss << "=== ESTOQUE ===" << endl;
    
    if (itens.empty()) {  // Se map está vazio
        ss << "Estoque vazio" << endl;
    } else {
        // Cabeçalho da tabela
        ss << left << setw(5) << "ID" << setw(30) << "Nome" 
           << setw(10) << "Quantidade" << endl;
        // left = alinha à esquerda
        // setw(n) = define largura de n caracteres
        
        ss << string(45, '-') << endl;
        // Linha separadora com 45 hífens
        
        // Percorre todos os itens do map
        for (const auto& par : itens) {
            const ItemEstoque& item = par.second;
            // Referência constante ao ItemEstoque (evita cópia)
            
            ss << left << setw(5) << item.itemId 
               << setw(30) << item.nomeItem
               << setw(10) << item.quantidade << endl;
            // Formata cada linha da tabela
        }
    }
    
    return ss.str();  // Converte stringstream para string
}

/**
 * Sobrecarga do operador << para permitir cout << estoque
 */
ostream& operator<<(ostream& os, const Estoque& estoque) {
    // ostream& = referência a stream de saída
    // friend = acessa membros privados de Estoque
    
    os << estoque.exibir();  // Chama método exibir()
    return os;  // Retorna stream para encadeamento
}
