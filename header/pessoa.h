/**
 * @file pessoa.h
 * @brief Definição da classe base Pessoa
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Esta classe serve como base para Usuario e Artista, implementando
 * herança e polimorfismo conforme requisitos do projeto.
 */

// Proteção contra inclusão múltipla do header (include guard)
#ifndef PESSOA_H
#define PESSOA_H

// Inclusão da biblioteca string para usar a classe string
#include <string>
// Inclusão da biblioteca iostream para operações de entrada/saída
#include <iostream>

// Usando o namespace padrão para evitar std:: antes de cada tipo
using namespace std;

/**
 * @class Pessoa
 * @brief Classe base abstrata que representa uma pessoa no sistema
 * 
 * Implementa conceitos de POO:
 * - Encapsulamento: atributos privados com getters/setters
 * - Herança: classe base para Usuario e Artista
 * - Polimorfismo: método virtual exibir()
 */
class Pessoa {
protected: // Modificador de acesso: acessível pela própria classe e classes derivadas
    int id;           // Identificador único da pessoa (número inteiro)
    string nome;      // Nome completo da pessoa (tipo string)
    
public: // Modificador de acesso: acessível de qualquer parte do programa
    /**
     * @brief Construtor padrão
     */
    Pessoa(); // Construtor sem parâmetros, cria pessoa com valores padrão
    
    /**
     * @brief Construtor parametrizado
     * @param id Identificador da pessoa
     * @param nome Nome da pessoa
     */
    Pessoa(int id, const string& nome); // Construtor com parâmetros para inicializar id e nome
    
    /**
     * @brief Destrutor virtual para suportar polimorfismo
     */
    virtual ~Pessoa(); // Destrutor virtual permite destruição correta de objetos derivados
    
    // Getters - Métodos para ler os valores dos atributos (const = não modificam o objeto)
    int getId() const; // Retorna o id da pessoa
    string getNome() const; // Retorna o nome da pessoa
    
    // Setters - Métodos para modificar os valores dos atributos
    void setId(int id); // Define um novo id para a pessoa
    void setNome(const string& nome); // Define um novo nome para a pessoa
    
    /**
     * @brief Método virtual puro para exibir informações (polimorfismo)
     * @return String formatada com informações da pessoa
     */
    virtual string exibir() const = 0; // Método abstrato (=0), deve ser implementado nas classes derivadas
    
    /**
     * @brief Sobrecarga do operador << para exibição
     * @param os Stream de saída
     * @param pessoa Objeto Pessoa a ser exibido
     * @return Stream de saída
     */
    friend ostream& operator<<(ostream& os, const Pessoa& pessoa); // Permite usar cout << pessoa
}; // Fim da classe Pessoa

#endif // PESSOA_H - Fim da proteção contra inclusão múltipla
