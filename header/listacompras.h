/**
 * @file listacompras.h
 * @brief Definição da classe ListaCompras
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia lista de compras consolidada de itens necessários.
 * Permite calcular custos totais e organizar compras.
 */

// Proteção contra inclusão múltipla
#ifndef LISTACOMPRAS_H  // Se LISTACOMPRAS_H não foi definido
#define LISTACOMPRAS_H  // Define LISTACOMPRAS_H

// Bibliotecas necessárias
#include <string>    // Para trabalhar com strings
#include <vector>    // Para lista de ListaCompras
#include <map>       // Para armazenar itens com chave itemId
#include <iostream>  // Para entrada/saída

using namespace std;  // Namespace padrão

/**
 * @struct ItemCompra
 * @brief Representa um item na lista de compras
 * 
 * Similar aos outros ItemXXX, mas inclui informações de PREÇO
 * STRUCT: dados simples, membros públicos por padrão
 */
struct ItemCompra {
    int itemId;        // ID do item
    string nomeItem;   // Nome do item
    int quantidade;    // Quantidade necessária para comprar
    double preco;      // Preço unitário do item
    double subtotal;   // Subtotal calculado (quantidade * preço)
    
    /**
     * @brief Construtor padrão - inicializa com zeros
     */
    ItemCompra() : itemId(0), nomeItem(""), quantidade(0), preco(0.0), subtotal(0.0) {}
    
    /**
     * @brief Construtor parametrizado - calcula subtotal automaticamente
     * @param id ID do item
     * @param nome Nome do item
     * @param qtd Quantidade a comprar
     * @param preco Preço unitário
     */
    ItemCompra(int id, const string& nome, int qtd, double preco) 
        : itemId(id), nomeItem(nome), quantidade(qtd), preco(preco), 
          subtotal(qtd * preco) {}
    // IMPORTANTE: subtotal é calculado no construtor (qtd * preco)
};  // Fim da struct ItemCompra

/**
 * @class ListaCompras
 * @brief Gerencia lista de compras consolidada
 * 
 * RESPONSABILIDADES:
 * - Adicionar itens à lista com preços
 * - Remover itens da lista
 * - Atualizar quantidades (recalcula subtotais)
 * - Calcular total geral da compra
 * - Exibir lista formatada com valores
 */
class ListaCompras {
private:  // ENCAPSULAMENTO: atributos privados
    int id;                         // ID único da lista
    string descricao;               // Descrição/título da lista
    map<int, ItemCompra> itens;    // Map: chave = itemId, valor = ItemCompra
    
public:  // Interface pública
    /**
     * @brief Construtor padrão - inicializa vazio
     */
    ListaCompras();
    
    /**
     * @brief Construtor parametrizado
     * @param id ID da lista
     * @param descricao Descrição/título da lista
     */
    ListaCompras(int id, const string& descricao);
    
    /**
     * @brief Destrutor - libera recursos
     */
    ~ListaCompras();
    
    // ==================== GETTERS ====================
    int getId() const;             // Retorna ID da lista
    string getDescricao() const;   // Retorna descrição da lista
    
    // ==================== SETTERS ====================
    void setId(int id);                           // Define ID
    void setDescricao(const string& descricao);   // Define descrição
    
    /**
     * @brief Adiciona item à lista de compras
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade a comprar
     * @param preco Preço unitário
     * 
     * Se item já existe: SOMA quantidade e recalcula subtotal
     * Se item não existe: cria novo ItemCompra
     */
    void adicionarItem(int itemId, const string& nomeItem, int quantidade, double preco);
    
    /**
     * @brief Remove item da lista de compras
     * @param itemId ID do item
     * @return true se removido com sucesso
     * 
     * Remove completamente (não subtrai quantidade)
     */
    bool removerItem(int itemId);
    
    /**
     * @brief Atualiza quantidade de um item
     * @param itemId ID do item
     * @param quantidade Nova quantidade (substitui valor anterior)
     * 
     * IMPORTANTE: recalcula subtotal após atualizar quantidade
     */
    void atualizarQuantidade(int itemId, int quantidade);
    
    /**
     * @brief Calcula total geral da lista de compras
     * @return Valor total (soma de todos os subtotais)
     * 
     * Percorre todos os itens somando seus subtotais
     */
    double calcularTotal() const;
    
    /**
     * @brief Limpa toda a lista (remove todos os itens)
     * 
     * Útil para começar nova lista do zero
     */
    void limpar();
    
    /**
     * @brief Exibe informações da lista formatada
     * @return String com tabela de itens e valor total
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador << para cout
     * @param os Stream de saída
     * @param lista Objeto ListaCompras
     * @return Referência ao stream (permite encadeamento)
     * 
     * FRIEND: acessa membros privados
     * Permite: cout << lista;
     */
    friend ostream& operator<<(ostream& os, const ListaCompras& lista);
};  // Fim da classe ListaCompras

/**
 * @class GerenciadorListaCompras
 * @brief Gerencia operações CRUD de listas de compras
 * 
 * Permite ter múltiplas listas de compras
 * (ex: "Compras Semanais", "Compras Mensais", etc)
 */
class GerenciadorListaCompras {
private:  // Atributos privados
    vector<ListaCompras> listas;  // Vector de listas de compras
    int proximoId;                // Contador para gerar IDs únicos
    
public:  // Interface pública CRUD
    /**
     * @brief Construtor - inicializa vazio e proximoId = 1
     */
    GerenciadorListaCompras();
    
    /**
     * @brief Cria nova lista de compras (CREATE)
     * @param descricao Descrição/título da lista
     * @return ID da lista criada
     * 
     * Gera ID automático, cria lista vazia
     */
    int criar(const string& descricao);
    
    /**
     * @brief Busca lista por ID (READ)
     * @param id ID da lista
     * @return Ponteiro para a lista ou nullptr se não encontrada
     * 
     * PONTEIRO: permite adicionar/remover itens da lista
     */
    ListaCompras* buscarPorId(int id);
    
    /**
     * @brief Remove lista de compras (DELETE)
     * @param id ID da lista
     * @return true se removida, false se não encontrada
     * 
     * Remove lista completa com todos os itens
     */
    bool remover(int id);
    
    /**
     * @brief Lista todas as listas de compras (READ ALL)
     * @return Vector com cópias de todas as listas
     */
    vector<ListaCompras> listar() const;
};  // Fim da classe GerenciadorListaCompras

#endif // LISTACOMPRAS_H
// Fim do include guard
