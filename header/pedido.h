/**
 * @file pedido.h
 * @brief Definição da classe Pedido
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia pedidos de itens para camarins.
 * Permite artistas solicitarem itens do estoque para seus camarins.
 */

// Proteção contra inclusão múltipla
#ifndef PEDIDO_H  // Se PEDIDO_H não foi definido
#define PEDIDO_H  // Define PEDIDO_H

// Bibliotecas necessárias
#include <string>    // Para trabalhar com strings
#include <vector>    // Para lista de pedidos
#include <map>       // Para armazenar itens do pedido
#include <iostream>  // Para entrada/saída

using namespace std;  // Namespace padrão

/**
 * @struct ItemPedido
 * @brief Representa um item em um pedido
 * 
 * Similar a ItemEstoque/ItemCamarim, mas específico para pedidos
 * STRUCT: dados simples sem lógica complexa, membros públicos
 */
struct ItemPedido {
    int itemId;        // ID do item solicitado
    string nomeItem;   // Nome do item
    int quantidade;    // Quantidade solicitada
    
    /**
     * @brief Construtor padrão
     */
    ItemPedido() : itemId(0), nomeItem(""), quantidade(0) {}
    
    /**
     * @brief Construtor parametrizado
     */
    ItemPedido(int id, const string& nome, int qtd) 
        : itemId(id), nomeItem(nome), quantidade(qtd) {}
};  // Fim da struct ItemPedido

/**
 * @class Pedido
 * @brief Representa um pedido de itens para um camarim
 * 
 * RESPONSABILIDADES:
 * - Armazenar informações do pedido (quem solicitou, o quê, quando)
 * - Gerenciar itens do pedido
 * - Controlar status (atendido ou pendente)
 * - Exibir informações formatadas
 */
class Pedido {
private:  // ENCAPSULAMENTO: atributos privados
    int id;                         // ID único do pedido
    int camarimId;                  // ID do camarim que fez o pedido
    string nomeArtista;             // Nome do artista (para facilitar exibição)
    map<int, ItemPedido> itens;    // Map: chave = itemId, valor = ItemPedido
    bool atendido;                  // Status: true = atendido, false = pendente
    
public:  // Interface pública
    /**
     * @brief Construtor padrão - inicializa com valores vazios
     */
    Pedido();
    
    /**
     * @brief Construtor parametrizado
     * @param id ID do pedido
     * @param camarimId ID do camarim solicitante
     * @param nomeArtista Nome do artista
     */
    Pedido(int id, int camarimId, const string& nomeArtista);
    
    /**
     * @brief Destrutor - libera recursos
     */
    ~Pedido();
    
    // ==================== GETTERS (retornam valores) ====================
    int getId() const;              // Retorna ID do pedido
    int getCamarimId() const;       // Retorna ID do camarim
    string getNomeArtista() const;  // Retorna nome do artista
    bool isAtendido() const;        // Retorna status (atendido ou não)
    
    // ==================== SETTERS (modificam atributos) ====================
    void setId(int id);                              // Define ID
    void setCamarimId(int camarimId);                // Define camarim
    void setNomeArtista(const string& nomeArtista);  // Define artista
    void setAtendido(bool atendido);                 // Define status
    
    /**
     * @brief Adiciona item ao pedido
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade solicitada
     * 
     * Se item já existe: soma quantidade
     * Se item não existe: cria novo ItemPedido
     */
    void adicionarItem(int itemId, const string& nomeItem, int quantidade);
    
    /**
     * @brief Remove item do pedido
     * @param itemId ID do item
     * @return true se removido com sucesso
     * 
     * Remove completamente (não subtrai quantidade)
     */
    bool removerItem(int itemId);
    
    /**
     * @brief Marca pedido como atendido
     * 
     * Chamado após transferir itens do estoque para o camarim
     * Muda atributo atendido de false para true
     */
    void marcarAtendido();
    
    /**
     * @brief Exibe informações completas do pedido
     * @return String formatada com ID, camarim, artista, status e itens
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador << para cout
     * @param os Stream de saída
     * @param pedido Objeto Pedido
     * @return Referência ao stream (permite encadeamento)
     * 
     * FRIEND: acessa membros privados
     * Permite: cout << pedido;
     */
    friend ostream& operator<<(ostream& os, const Pedido& pedido);
};  // Fim da classe Pedido

/**
 * @class GerenciadorPedidos
 * @brief Gerencia operações CRUD de pedidos
 * 
 * CRUD: Create (criar), Read (buscar/listar), Update (atender), Delete (remover)
 * Centraliza gerenciamento de todos os pedidos do sistema
 */
class GerenciadorPedidos {
private:  // Atributos privados
    vector<Pedido> pedidos;  // Vector dinâmico de pedidos
    int proximoId;           // Contador para gerar IDs únicos
    
public:  // Interface pública (métodos CRUD)
    /**
     * @brief Construtor - inicializa lista vazia e proximoId = 1
     */
    GerenciadorPedidos();
    
    /**
     * @brief Cria novo pedido (CREATE)
     * @param camarimId ID do camarim solicitante
     * @param nomeArtista Nome do artista
     * @return ID do pedido criado
     * 
     * Gera ID automático, cria Pedido vazio (sem itens ainda)
     * Itens são adicionados depois com adicionarItem()
     */
    int criar(int camarimId, const string& nomeArtista);
    
    /**
     * @brief Busca pedido por ID (READ)
     * @param id ID do pedido
     * @return Ponteiro para o pedido ou nullptr se não encontrado
     * 
     * PONTEIRO: permite modificar pedido original (adicionar itens, marcar atendido)
     */
    Pedido* buscarPorId(int id);
    
    /**
     * @brief Busca todos os pedidos de um camarim (READ)
     * @param camarimId ID do camarim
     * @return Vector com cópias dos pedidos deste camarim
     * 
     * Útil para ver histórico de pedidos de um artista
     */
    vector<Pedido> buscarPorCamarim(int camarimId) const;
    
    /**
     * @brief Lista pedidos pendentes (READ com filtro)
     * @return Vector com pedidos que ainda não foram atendidos
     * 
     * Útil para gerenciar fila de pedidos a processar
     */
    vector<Pedido> listarPendentes() const;
    
    /**
     * @brief Remove pedido (DELETE)
     * @param id ID do pedido
     * @return true se removido, false se não encontrado
     * 
     * Usa remove_if + erase
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os pedidos (READ ALL)
     * @return Vector com cópias de todos os pedidos
     */
    vector<Pedido> listar() const;
};  // Fim da classe GerenciadorPedidos

#endif // PEDIDO_H
// Fim do include guard
