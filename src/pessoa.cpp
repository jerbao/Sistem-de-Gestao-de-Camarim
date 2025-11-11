/**
 * @file pessoa.cpp
 * @brief Implementação da classe Pessoa
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

// Inclui o header da classe Pessoa com as declarações dos métodos
#include "pessoa.h"

// Construtor padrão - Inicializa id com 0 e nome com string vazia
// Lista de inicialização (:) é mais eficiente que atribuição no corpo
Pessoa::Pessoa() : id(0), nome("") {}

// Construtor parametrizado - Recebe id e nome como parâmetros
// Lista de inicialização inicializa os atributos com os valores recebidos
Pessoa::Pessoa(int id, const string& nome) : id(id), nome(nome) {}

// Destrutor virtual - Permite destruição correta de objetos derivados
// Corpo vazio {} porque não há recursos para liberar nesta classe
Pessoa::~Pessoa() {}

// Métodos Getters - Retornam os valores dos atributos privados
// const após a declaração indica que o método não modifica o objeto
int Pessoa::getId() const {
    return id; // Retorna o valor do atributo id
}

string Pessoa::getNome() const {
    return nome; // Retorna o valor do atributo nome
}

// Métodos Setters - Modificam os valores dos atributos privados
void Pessoa::setId(int id) {
    this->id = id; // this-> diferencia o parâmetro do atributo
}

void Pessoa::setNome(const string& nome) {
    this->nome = nome; // Atribui o valor do parâmetro ao atributo
}

// Sobrecarga do operador << para permitir cout << pessoa
// friend permite acesso aos membros privados da classe
ostream& operator<<(ostream& os, const Pessoa& pessoa) {
    os << pessoa.exibir(); // Chama o método virtual exibir() polimórfico
    return os; // Retorna o stream para permitir encadeamento (cout << p1 << p2)
}
