/**
 * @file listacompras.cpp
 * @brief Implementação da classe ListaCompras e GerenciadorListaCompras
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa lógica de gerenciamento de listas de compras com cálculos de custos.
 */

// Inclui header da classe
#include "listacompras.h"
// Inclui exceções customizadas
#include "excecoes.h"
// Algoritmos STL (remove_if, etc)
#include <algorithm>
// Para stringstream (construir strings)
#include <sstream>
// Para formatação (setw, fixed, setprecision)
#include <iomanip>

// ==================== Classe ListaCompras ====================

/**
 * Construtor padrão - inicializa com valores vazios
 */
ListaCompras::ListaCompras() : id(0), descricao("") {}

/**
 * Construtor parametrizado
 */
ListaCompras::ListaCompras(int id, const string& descricao)
    : id(id), descricao(descricao) {}
// Lista começa vazia (map itens vazio)

/**
 * Destrutor - libera recursos
 */
ListaCompras::~ListaCompras() {}
// Map é destruído automaticamente

// ==================== GETTERS ====================

/**
 * Retorna ID da lista
 */
int ListaCompras::getId() const {
    return id;
}

/**
 * Retorna descrição/título da lista
 */
string ListaCompras::getDescricao() const {
    return descricao;
}

// ==================== SETTERS ====================

/**
 * Define ID com validação
 */
void ListaCompras::setId(int id) {
    if (id < 0) {
        throw ValidacaoException("ID da lista inválido");
    }
    this->id = id;
}

/**
 * Define descrição com validação
 */
void ListaCompras::setDescricao(const string& descricao) {
    if (descricao.empty()) {
        throw ValidacaoException("Descrição não pode ser vazia");
    }
    this->descricao = descricao;
}

/**
 * Adiciona item à lista de compras
 */
void ListaCompras::adicionarItem(int itemId, const string& nomeItem, int quantidade, double preco) {
    // VALIDAÇÕES:
    if (itemId < 0) {
        throw ValidacaoException("ID do item inválido");
    }
    
    if (nomeItem.empty()) {
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (quantidade <= 0) {
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    if (preco < 0) {  // Preço pode ser 0 (item gratuito), mas não negativo
        throw ValidacaoException("Preço não pode ser negativo");
    }
    
    // Se item já existe: SOMA quantidade e RECALCULA subtotal
    if (itens.find(itemId) != itens.end()) {
        itens[itemId].quantidade += quantidade;  // Soma quantidade
        
        // IMPORTANTE: recalcula subtotal após atualizar quantidade
        itens[itemId].subtotal = itens[itemId].quantidade * itens[itemId].preco;
        // subtotal = quantidade total * preço unitário
    } else {
        // Item NÃO EXISTE: cria novo ItemCompra
        itens[itemId] = ItemCompra(itemId, nomeItem, quantidade, preco);
        // Construtor de ItemCompra já calcula subtotal
    }
}

/**
 * Remove item da lista
 */
bool ListaCompras::removerItem(int itemId) {
    // Busca item no map
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {  // Não encontrou
        return false;  // Item não está na lista
    }
    
    // Remove completamente do map
    itens.erase(itemId);
    return true;  // Sucesso
}

/**
 * Atualiza quantidade de um item (SUBSTITUI valor)
 */
void ListaCompras::atualizarQuantidade(int itemId, int quantidade) {
    // Verifica se item existe
    if (itens.find(itemId) == itens.end()) {
        throw ListaComprasException("Item não encontrado na lista");
    }
    
    if (quantidade <= 0) {  // Quantidade deve ser positiva
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    // SUBSTITUI quantidade (não soma)
    itens[itemId].quantidade = quantidade;
    
    // CRUCIAL: recalcula subtotal após atualizar quantidade
    itens[itemId].subtotal = quantidade * itens[itemId].preco;
    // subtotal = nova quantidade * preço unitário
}

/**
 * Calcula total geral da lista de compras
 */
double ListaCompras::calcularTotal() const {
    double total = 0.0;  // Inicializa acumulador como 0.0 (double)
    
    // Percorre todos os itens do map
    for (const auto& par : itens) {
        // par.first = itemId (não usado aqui)
        // par.second = ItemCompra
        
        total += par.second.subtotal;
        // Soma subtotal de cada item ao total geral
    }
    
    return total;  // Retorna soma de todos os subtotais
}

/**
 * Limpa toda a lista (remove todos os itens)
 */
void ListaCompras::limpar() {
    itens.clear();  // Método clear() do map remove todos os elementos
}

/**
 * Exibe informações da lista formatadas
 */
string ListaCompras::exibir() const {
    stringstream ss;  // String stream para construir string
    
    // FORMATAÇÃO DE VALORES MONETÁRIOS:
    ss << fixed << setprecision(2);
    // fixed = notação de ponto fixo (não científica)
    // setprecision(2) = duas casas decimais (R$ 10.50)
    
    ss << "=== LISTA DE COMPRAS ===" << endl;
    ss << "ID: " << id << endl;
    ss << "Descrição: " << descricao << endl;
    ss << "\nItens:" << endl;
    
    if (itens.empty()) {  // Se lista está vazia
        ss << "  Lista vazia" << endl;
    } else {
        // Cabeçalho da tabela com colunas de valores
        ss << left << setw(5) << "  ID" << setw(25) << "Nome" 
           << setw(8) << "Qtd" << setw(12) << "Preço Unit."
           << setw(12) << "Subtotal" << endl;
        // left = alinhamento à esquerda
        // setw(n) = largura de n caracteres
        
        ss << "  " << string(60, '-') << endl;
        // Linha separadora com 60 hífens
        
        // Percorre todos os itens
        for (const auto& par : itens) {
            const ItemCompra& item = par.second;
            
            ss << left << setw(5) << "  " + to_string(item.itemId)
               << setw(25) << item.nomeItem
               << setw(8) << item.quantidade
               << "R$ " << setw(9) << item.preco        // Preço unitário formatado
               << "R$ " << setw(9) << item.subtotal << endl;  // Subtotal formatado
            // R$ = símbolo da moeda
            // Valores com 2 casas decimais devido a setprecision(2)
        }
        
        ss << "  " << string(60, '-') << endl;
        // Linha separadora antes do total
        
        // TOTAL GERAL alinhado à direita
        ss << right << setw(50) << "TOTAL: R$ " << setw(9) << calcularTotal() << endl;
        // right = alinhamento à direita (valor fica no fim da linha)
        // Chama calcularTotal() para somar todos os subtotais
    }
    
    return ss.str();  // Converte stringstream para string
}

/**
 * Sobrecarga do operador << para cout
 */
ostream& operator<<(ostream& os, const ListaCompras& lista) {
    os << lista.exibir();  // Chama método exibir()
    return os;  // Retorna stream para encadeamento
}

// ==================== Classe GerenciadorListaCompras ====================

/**
 * Construtor - inicializa próximo ID como 1
 */
GerenciadorListaCompras::GerenciadorListaCompras() : proximoId(1) {}

/**
 * Cria nova lista de compras (CREATE)
 */
int GerenciadorListaCompras::criar(const string& descricao) {
    if (descricao.empty()) {  // Validação
        throw ValidacaoException("Descrição não pode ser vazia");
    }
    
    // Cria nova lista com ID automático
    ListaCompras novaLista(proximoId, descricao);
    
    // Adiciona ao vector
    listas.push_back(novaLista);
    // push_back() faz cópia do objeto
    
    return proximoId++;  // Retorna ID usado e incrementa
}

/**
 * Busca lista por ID (READ)
 */
ListaCompras* GerenciadorListaCompras::buscarPorId(int id) {
    // Percorre vector de listas
    for (auto& lista : listas) {
        // auto& = referência (permite modificar)
        
        if (lista.getId() == id) {  // Se encontrou
            return &lista;  // Retorna PONTEIRO para a lista
            // Ponteiro permite adicionar/remover itens
        }
    }
    return nullptr;  // Não encontrou
}

/**
 * Remove lista de compras (DELETE)
 */
bool GerenciadorListaCompras::remover(int id) {
    // PADRÃO REMOVE-ERASE:
    auto it = remove_if(listas.begin(), listas.end(),
                       [id](const ListaCompras& l) { return l.getId() == id; });
    // LAMBDA: [id](const ListaCompras& l) { return l.getId() == id; }
    //   [id] = captura variável id
    //   (const ListaCompras& l) = parâmetro (cada lista)
    //   { return ... } = critério de remoção
    
    if (it != listas.end()) {  // Se encontrou lista(s) a remover
        listas.erase(it, listas.end());
        // Remove do vector
        return true;  // Sucesso
    }
    return false;  // Não encontrou
}

/**
 * Lista todas as listas de compras (READ ALL)
 */
vector<ListaCompras> GerenciadorListaCompras::listar() const {
    return listas;  // Retorna CÓPIA de todo o vector
}
