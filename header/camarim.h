/**
 * @file camarim.h
 * @brief Definição da classe Camarim
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia os camarins e seus itens associados.
 * Demonstra encapsulamento de dados e uso de containers STL (map, vector).
 */

// Proteção contra inclusão múltipla
#ifndef CAMARIM_H  // Se CAMARIM_H não foi definido
#define CAMARIM_H  // Define CAMARIM_H

// Bibliotecas necessárias
#include <string>    // Para trabalhar com strings
#include <vector>    // Para lista dinâmica de camarins
#include <map>       // Para armazenar itens com chave itemId
#include <iostream>  // Para entrada/saída (cout, cin)

using namespace std;  // Namespace padrão da STL

/**
 * @struct ItemCamarim
 * @brief Representa um item dentro de um camarim
 * 
 * STRUCT vs CLASS:
 * Struct = todos os membros são públicos por padrão
 * Usada aqui para estrutura de dados simples sem lógica complexa
 */
struct ItemCamarim {
    int itemId;        // ID do item (referência ao catálogo)
    string nomeItem;   // Nome do item (cópia para facilitar exibição)
    int quantidade;    // Quantidade deste item no camarim
    
    /**
     * @brief Construtor padrão - inicializa com valores vazios
     */
    ItemCamarim() : itemId(0), nomeItem(""), quantidade(0) {}
    // Lista de inicialização: inicializa membros antes do corpo do construtor
    
    /**
     * @brief Construtor parametrizado - inicializa com valores fornecidos
     * @param id ID do item
     * @param nome Nome do item
     * @param qtd Quantidade no camarim
     */
    ItemCamarim(int id, const string& nome, int qtd) 
        : itemId(id), nomeItem(nome), quantidade(qtd) {}
    // Recebe valores e inicializa diretamente os atributos
};  // Fim da struct ItemCamarim

/**
 * @class Camarim
 * @brief Representa um camarim com seus itens
 * 
 * ENCAPSULAMENTO:
 * Atributos privados acessados apenas por getters/setters
 * Garante controle sobre modificações dos dados
 */
class Camarim {
private:  // Atributos privados - ENCAPSULAMENTO
    int id;                          // ID único do camarim
    string nome;                     // Nome identificador do camarim
    int artistaId;                   // ID do artista associado (0 = sem artista)
    map<int, ItemCamarim> itens;    // Map: chave = itemId, valor = ItemCamarim
    // MAP: acesso rápido O(log n) por itemId, não permite chaves duplicadas
    
public:  // Métodos públicos
    /**
     * @brief Construtor padrão - inicializa com valores vazios
     */
    Camarim();
    
    /**
     * @brief Construtor parametrizado - inicializa com dados fornecidos
     * @param id ID do camarim
     * @param nome Nome do camarim
     * @param artistaId ID do artista (0 = nenhum)
     */
    Camarim(int id, const string& nome, int artistaId);
    
    /**
     * @brief Destrutor - limpa recursos (map é limpo automaticamente)
     */
    ~Camarim();
    
    // GETTERS: métodos const que retornam cópias/valores (não modificam objeto)
    int getId() const;          // Retorna ID do camarim
    string getNome() const;     // Retorna nome do camarim
    int getArtistaId() const;   // Retorna ID do artista associado
    
    // SETTERS: métodos que permitem modificar atributos privados
    void setId(int id);                      // Define ID do camarim
    void setNome(const string& nome);        // Define nome do camarim
    void setArtistaId(int artistaId);        // Define artista associado
    
    /**
     * @brief Adiciona ou atualiza item no camarim
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade a adicionar
     * 
     * Se item já existe: soma quantidade
     * Se item não existe: cria novo ItemCamarim no map
     */
    void inserirItem(int itemId, const string& nomeItem, int quantidade);
    
    /**
     * @brief Remove quantidade de um item do camarim
     * @param itemId ID do item
     * @param quantidade Quantidade a remover
     * @return true se removido com sucesso, false se não há quantidade suficiente
     * 
     * Se quantidade ficar 0: remove item do map
     * Se não há quantidade suficiente: retorna false
     */
    bool removerItem(int itemId, int quantidade);
    
    /**
     * @brief Exibe informações completas do camarim
     * @return String formatada com ID, nome, artista e lista de itens
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador << para cout
     * @param os Stream de saída
     * @param camarim Objeto Camarim a ser impresso
     * @return Referência para o stream (permite encadeamento)
     * 
     * FRIEND: permite acesso aos membros privados do Camarim
     * Usado para: cout << camarim;
     */
    friend ostream& operator<<(ostream& os, const Camarim& camarim);
};  // Fim da classe Camarim

/**
 * @class GerenciadorCamarins
 * @brief Gerencia operações CRUD de camarins
 * 
 * CRUD = Create, Read, Update, Delete
 * Centraliza todas as operações de gerenciamento de camarins
 */
class GerenciadorCamarins {
private:  // Atributos privados
    vector<Camarim> camarins;  // Vector dinâmico de camarins
    int proximoId;             // Contador para gerar IDs únicos
    
public:  // Métodos públicos (interface CRUD)
    /**
     * @brief Construtor - inicializa lista vazia e proximoId = 1
     */
    GerenciadorCamarins();
    
    /**
     * @brief Cadastra novo camarim (CREATE)
     * @param nome Nome do camarim
     * @param artistaId ID do artista (0 = sem artista)
     * @return ID do camarim cadastrado
     * 
     * Gera ID automático, cria Camarim, adiciona ao vector
     */
    int cadastrar(const string& nome, int artistaId);
    
    /**
     * @brief Busca camarim por ID (READ)
     * @param id ID do camarim
     * @return Ponteiro para o camarim ou nullptr se não encontrado
     * 
     * PONTEIRO: permite modificar o camarim original
     * nullptr = valor nulo para ponteiros
     */
    Camarim* buscarPorId(int id);
    
    /**
     * @brief Busca camarim associado a um artista (READ)
     * @param artistaId ID do artista
     * @return Ponteiro para o camarim ou nullptr se não encontrado
     * 
     * Usado para verificar se artista já tem camarim
     */
    Camarim* buscarPorArtista(int artistaId);
    
    /**
     * @brief Remove camarim (DELETE)
     * @param id ID do camarim
     * @return true se removido, false se não encontrado
     * 
     * Usa remove_if + erase para remover do vector
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os camarins (READ ALL)
     * @return Vector com cópias de todos os camarins
     */
    vector<Camarim> listar() const;
    
    /**
     * @brief Atualiza dados de um camarim (UPDATE)
     * @param id ID do camarim a atualizar
     * @param nome Novo nome
     * @param artistaId Novo ID de artista
     * @return true se atualizado, false se não encontrado
     * 
     * Busca por ID e atualiza os campos
     */
    bool atualizar(int id, const string& nome, int artistaId);
};  // Fim da classe GerenciadorCamarins

#endif // CAMARIM_H
// Fim do include guard