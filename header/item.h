/**
 * @file item.h
 * @brief Definição da classe Item
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Classe que representa itens do sistema (produtos)
 * com encapsulamento completo e sobrecarga de operadores.
 */

// Proteção contra inclusão múltipla do header
#ifndef ITEM_H  // Se ITEM_H ainda não foi definido
#define ITEM_H  // Define ITEM_H para marcar que este arquivo foi incluído

// Inclui biblioteca para trabalhar com strings (texto)
#include <string>
// Inclui biblioteca para operações de entrada e saída (cout, cin)
#include <iostream>
// Inclui biblioteca para trabalhar com vetores (arrays dinâmicos)
#include <vector>

// Usa o namespace padrão para evitar escrever std:: antes de cada tipo
using namespace std;

/**
 * @class Item
 * @brief Representa um item/produto no sistema
 * 
 * Implementa encapsulamento completo com atributos privados,
 * getters/setters e sobrecarga do operador <<.
 */
class Item {  // Declaração da classe Item
private:  // Modificador de acesso: só acessível dentro da própria classe (ENCAPSULAMENTO)
    int id;           // Identificador único do item (número inteiro)
    string nome;      // Nome do item (texto/string)
    double preco;     // Preço unitário do item (número decimal de precisão dupla)
    
public:  // Modificador de acesso: acessível de qualquer lugar do programa
    /**
     * @brief Construtor padrão
     */
    Item();  // Construtor sem parâmetros, inicializa com valores padrão
    
    /**
     * @brief Construtor parametrizado
     * @param id Identificador do item
     * @param nome Nome do item
     * @param preco Preço do item
     */
    Item(int id, const string& nome, double preco);  // Construtor que recebe valores iniciais
    // const string& = referência constante (não copia, não modifica)
    
    /**
     * @brief Destrutor
     */
    ~Item();  // Destrutor, executado quando o objeto é destruído (libera recursos)
    
    // Getters - Métodos para LER os valores dos atributos privados
    int getId() const;  // Retorna o ID do item (const = não modifica o objeto)
    string getNome() const;  // Retorna o nome do item
    double getPreco() const;  // Retorna o preço do item
    
    // Setters com validação - Métodos para MODIFICAR os valores dos atributos
    void setId(int id);  // Define um novo ID (com validação)
    void setNome(const string& nome);  // Define um novo nome (com validação)
    void setPreco(double preco);  // Define um novo preço (com validação)
    
    /**
     * @brief Exibe informações do item
     * @return String formatada com informações do item
     */
    string exibir() const;  // Método que retorna string com dados formatados do item
    
    /**
     * @brief Sobrecarga do operador << para exibição
     * @param os Stream de saída
     * @param item Item a ser exibido
     * @return Stream de saída
     */
    friend ostream& operator<<(ostream& os, const Item& item);  
    // Sobrecarga do operador << para permitir cout << item
    // friend = pode acessar membros privados da classe
    // ostream& = retorna referência ao stream para permitir encadeamento (cout << i1 << i2)
    
    /**
     * @brief Sobrecarga do operador == para comparação
     * @param outro Item a comparar
     * @return true se itens são iguais
     */
    bool operator==(const Item& outro) const;  
    // Sobrecarga do operador == para comparar dois itens
    // Retorna true se forem iguais, false caso contrário
};  // Fim da classe Item

/**
 * @class GerenciadorItens
 * @brief Gerencia operações CRUD de itens
 */
class GerenciadorItens {  // Classe que gerencia todos os itens do sistema
private:  // Atributos privados (ENCAPSULAMENTO)
    vector<Item> itens;    // Vetor (array dinâmico) que armazena todos os itens cadastrados
    int proximoId;         // Contador para gerar próximo ID único disponível
    
public:  // Métodos públicos (interface da classe)
    /**
     * @brief Construtor
     */
    GerenciadorItens();  // Construtor, inicializa o gerenciador
    
    /**
     * @brief Cadastra novo item
     * @param nome Nome do item
     * @param preco Preço do item
     * @return ID do item cadastrado
     */
    int cadastrar(const string& nome, double preco);  
    // Cria um novo item e adiciona ao vetor
    // Retorna o ID gerado para o item criado
    
    /**
     * @brief Busca item por ID
     * @param id ID do item
     * @return Ponteiro para o item ou nullptr se não encontrado
     */
    Item* buscarPorId(int id);  
    // Procura um item pelo seu ID
    // Retorna ponteiro para o item se encontrado, ou nullptr (ponteiro nulo) se não encontrado
    
    /**
     * @brief Busca item por nome
     * @param nome Nome do item
     * @return Ponteiro para o item ou nullptr se não encontrado
     */
    Item* buscarPorNome(const string& nome);  
    // Procura um item pelo seu nome
    // Retorna ponteiro para o item se encontrado, ou nullptr se não encontrado
    
    /**
     * @brief Remove item por ID
     * @param id ID do item
     * @return true se removido com sucesso
     */
    bool remover(int id);  
    // Remove um item do vetor pelo seu ID
    // Retorna true se conseguiu remover, false se não encontrou o item
    
    /**
     * @brief Lista todos os itens
     * @return Vector com todos os itens
     */
    vector<Item> listar() const;  
    // Retorna uma cópia do vetor com todos os itens cadastrados
    // const = não modifica o estado do gerenciador
    
    /**
     * @brief Atualiza dados de um item
     * @param id ID do item
     * @param nome Novo nome
     * @param preco Novo preço
     * @return true se atualizado com sucesso
     */
    bool atualizar(int id, const string& nome, double preco);  
    // Busca um item pelo ID e atualiza seus dados (nome e preço)
    // Retorna true se atualizou com sucesso, false se não encontrou
};  // Fim da classe GerenciadorItens

#endif // ITEM_H - Fim da proteção contra inclusão múltipla
