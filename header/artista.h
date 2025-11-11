/**
 * @file artista.h
 * @brief Definição da classe Artista (herda de Pessoa)
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa herança da classe base Pessoa e adiciona
 * funcionalidades específicas para artistas.
 */

// Proteção contra inclusão múltipla
#ifndef ARTISTA_H  // Se ARTISTA_H não foi definido
#define ARTISTA_H  // Define ARTISTA_H

// Inclui o header da classe base Pessoa (necessário para herança)
#include "pessoa.h"
// Inclui biblioteca vector para armazenar lista de artistas
#include <vector>

/**
 * @class Artista
 * @brief Representa um artista com camarim associado
 * 
 * Herda de Pessoa e adiciona funcionalidades específicas para artistas.
 */
class Artista : public Pessoa {  // : public Pessoa = HERANÇA pública de Pessoa
    // Artista É UMA (is-a) Pessoa, herda id e nome
    
private:  // Atributos adicionais (específicos de Artista)
    int camarimId;    // ID do camarim associado ao artista (número do camarim)
    
public:  // Métodos públicos
    /**
     * @brief Construtor padrão
     */
    Artista();  // Construtor sem parâmetros
    
    /**
     * @brief Construtor parametrizado
     * @param id Identificador do artista
     * @param nome Nome do artista
     * @param camarimId ID do camarim associado
     */
    Artista(int id, const string& nome, int camarimId);  
    // Construtor que recebe id, nome (herdados) e camarimId (específico)
    
    /**
     * @brief Destrutor
     */
    ~Artista();  // Destrutor da classe derivada
    
    // Getters - Métodos para ler atributos
    int getCamarimId() const;  // Retorna o ID do camarim do artista
    
    // Setters - Métodos para modificar atributos
    void setCamarimId(int camarimId);  // Define novo camarimId
    
    /**
     * @brief Implementação do método virtual exibir (polimorfismo)
     * @return String formatada com informações do artista
     */
    string exibir() const override;  
    // override = SOBRESCREVE o método virtual puro da classe base Pessoa
    // POLIMORFISMO: implementa comportamento específico para Artista
};  // Fim da classe Artista (classe derivada)

/**
 * @class GerenciadorArtistas
 * @brief Gerencia operações CRUD de artistas
 */
class GerenciadorArtistas {  // Classe gerenciadora para operações com artistas
private:  // Atributos privados (ENCAPSULAMENTO)
    vector<Artista> artistas;  // Vetor que armazena todos os artistas cadastrados
    int proximoId;             // Contador para gerar IDs únicos sequencialmente
    
public:  // Métodos públicos (interface CRUD)
    /**
     * @brief Construtor
     */
    GerenciadorArtistas();  // Inicializa o gerenciador
    
    /**
     * @brief Cadastra novo artista
     * @param nome Nome do artista
     * @param camarimId ID do camarim
     * @return ID do artista cadastrado
     */
    int cadastrar(const string& nome, int camarimId);  
    // CREATE: Cria novo artista e retorna o ID gerado
    
    /**
     * @brief Busca artista por ID
     * @param id ID do artista
     * @return Ponteiro para o artista ou nullptr se não encontrado
     */
    Artista* buscarPorId(int id);  
    // READ: Busca e retorna ponteiro para o artista (ou nullptr)
    
    /**
     * @brief Busca artistas por camarim
     * @param camarimId ID do camarim
     * @return Vector com artistas do camarim
     */
    vector<Artista> buscarPorCamarim(int camarimId) const;  
    // READ: Retorna todos os artistas de um camarim específico
    
    /**
     * @brief Remove artista por ID
     * @param id ID do artista
     * @return true se removido com sucesso
     */
    bool remover(int id);  
    // DELETE: Remove artista do vetor, retorna true se conseguiu
    
    /**
     * @brief Lista todos os artistas
     * @return Vector com todos os artistas
     */
    vector<Artista> listar() const;  
    // READ: Retorna cópia do vetor com todos os artistas
    
    /**
     * @brief Atualiza dados de um artista
     * @param id ID do artista
     * @param nome Novo nome
     * @param camarimId Novo ID de camarim
     * @return true se atualizado com sucesso
     */
    bool atualizar(int id, const string& nome, int camarimId);  
    // UPDATE: Modifica dados de um artista existente, retorna true se conseguiu
};  // Fim da classe GerenciadorArtistas

#endif // ARTISTA_H - Fim da proteção contra inclusão múltipla
