/**
 * @file estoque.h
 * @brief Definição da classe Estoque
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia o estoque centralizado de itens no sistema.
 * Controla entradas, saídas e disponibilidade de itens.
 */

// Proteção contra inclusão múltipla
#ifndef ESTOQUE_H  // Se ESTOQUE_H não foi definido
#define ESTOQUE_H  // Define ESTOQUE_H

// Inclui header de Item para usar tipos relacionados
#include "item.h"
// Map para armazenar itens com chave itemId
#include <map>
// Vector para retornar listas de itens
#include <vector>

/**
 * @struct ItemEstoque
 * @brief Estrutura que representa um item no estoque
 * 
 * Similar a ItemCamarim, mas específica para o estoque central
 * STRUCT: membros públicos por padrão, usada para dados simples
 */
struct ItemEstoque {
    int itemId;        // ID do item (referência ao catálogo)
    string nomeItem;   // Nome do item (cópia para facilitar acesso)
    int quantidade;    // Quantidade disponível no estoque central
    
    /**
     * @brief Construtor padrão - inicializa vazio
     */
    ItemEstoque() : itemId(0), nomeItem(""), quantidade(0) {}
    
    /**
     * @brief Construtor parametrizado
     */
    ItemEstoque(int id, const string& nome, int qtd) 
        : itemId(id), nomeItem(nome), quantidade(qtd) {}
};  // Fim da struct ItemEstoque

/**
 * @class Estoque
 * @brief Gerencia o estoque centralizado de itens
 * 
 * RESPONSABILIDADES:
 * - Adicionar itens (entrada de estoque)
 * - Remover itens (saída de estoque)
 * - Verificar disponibilidade antes de operações
 * - Controlar quantidades
 * - Listar itens disponíveis
 */
class Estoque {
private:  // ENCAPSULAMENTO: atributo privado
    map<int, ItemEstoque> itens;  // Map: chave = itemId, valor = ItemEstoque
    // MAP: acesso O(log n), sem chaves duplicadas, ordenado por chave
    
public:  // Interface pública
    /**
     * @brief Construtor - inicializa estoque vazio
     */
    Estoque();
    
    /**
     * @brief Destrutor - libera recursos
     */
    ~Estoque();
    
    /**
     * @brief Adiciona quantidade de um item ao estoque (ENTRADA)
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade a adicionar
     * 
     * Se item já existe: soma quantidade
     * Se item não existe: cria novo ItemEstoque
     */
    void adicionarItem(int itemId, const string& nomeItem, int quantidade);
    
    /**
     * @brief Remove quantidade de um item do estoque (SAÍDA)
     * @param itemId ID do item
     * @param quantidade Quantidade a remover
     * @return true se removido com sucesso
     * @throws EstoqueInsuficienteException se não houver quantidade suficiente
     * 
     * Verifica disponibilidade antes de remover
     * Se quantidade ficar 0: remove item do map
     */
    bool removerItem(int itemId, int quantidade);
    
    /**
     * @brief Verifica se há quantidade suficiente de um item
     * @param itemId ID do item
     * @param quantidade Quantidade desejada
     * @return true se há quantidade suficiente, false caso contrário
     * 
     * CRUCIAL: deve ser chamado ANTES de tentar remover itens
     */
    bool verificarDisponibilidade(int itemId, int quantidade) const;
    
    /**
     * @brief Obtém quantidade atual de um item em estoque
     * @param itemId ID do item
     * @return Quantidade disponível (0 se item não existe)
     */
    int obterQuantidade(int itemId) const;
    
    /**
     * @brief Lista todos os itens em estoque (READ ALL)
     * @return Vector com cópias de todos os ItemEstoque
     */
    vector<ItemEstoque> listar() const;
    
    /**
     * @brief Atualiza quantidade de um item (UPDATE)
     * @param itemId ID do item
     * @param novaQuantidade Nova quantidade (substitui valor anterior)
     * 
     * Diferente de adicionarItem: SUBSTITUI ao invés de somar
     */
    void atualizarQuantidade(int itemId, int novaQuantidade);
    
    /**
     * @brief Exibe informações do estoque formatadas
     * @return String com tabela de todos os itens e quantidades
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador << para cout
     * @param os Stream de saída
     * @param estoque Objeto Estoque
     * @return Referência ao stream (permite encadeamento)
     * 
     * FRIEND: acessa membros privados
     * Permite: cout << estoque;
     */
    friend ostream& operator<<(ostream& os, const Estoque& estoque);
};  // Fim da classe Estoque

#endif // ESTOQUE_H
// Fim do include guard
