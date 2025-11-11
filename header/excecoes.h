/**
 * @file excecoes.h
 * @brief Definição de exceções personalizadas do sistema
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Este arquivo contém todas as exceções personalizadas utilizadas
 * no sistema de gestão de camarim, implementando tratamento de erros
 * conforme requisitos do projeto.
 */

// Proteção contra inclusão múltipla
#ifndef EXCECOES_H  // Se EXCECOES_H não foi definido
#define EXCECOES_H  // Define EXCECOES_H

// Inclui a biblioteca exception da STL para herdar de std::exception
#include <exception>
// Inclui string para trabalhar com mensagens de erro
#include <string>

// Usa namespace padrão
using namespace std;

/**
 * @class ExcecaoBase
 * @brief Classe base para todas as exceções do sistema
 * 
 * HIERARQUIA DE EXCEÇÕES:
 * Todas as exceções customizadas herdam desta classe base,
 * que por sua vez herda de std::exception
 */
class ExcecaoBase : public exception {  // HERDA de std::exception
    // : public exception = herança pública da classe exception da STL
    
protected:  // Protected: classes filhas podem acessar
    string mensagem;  // Mensagem de erro armazenada como string
    
public:  // Métodos públicos
    /**
     * @brief Construtor com mensagem
     * @param msg Mensagem de erro
     */
    explicit ExcecaoBase(const string& msg) : mensagem(msg) {}  
    // explicit = previne conversões implícitas indesejadas
    // Recebe mensagem e inicializa o atributo mensagem
    
    /**
     * @brief Retorna a mensagem de erro
     * @return Mensagem de erro como C-string
     */
    virtual const char* what() const noexcept override {
        // virtual = pode ser sobrescrito por classes derivadas
        // const = não modifica o estado do objeto
        // noexcept = garante que não lança exceções
        // override = SOBRESCREVE método da classe base (std::exception)
        
        return mensagem.c_str();  // Converte string C++ para C-string
        // c_str() retorna ponteiro para char* (compatível com C)
    }
    
    /**
     * @brief Destrutor virtual
     */
    virtual ~ExcecaoBase() noexcept {}  
    // virtual = permite destruição polimórfica correta
    // noexcept = garante que destrutor não lança exceções (boa prática)
};  // Fim da classe base de exceções

/**
 * @class ValidacaoException
 * @brief Exceção para erros de validação de dados
 * 
 * EXCEÇÃO DERIVADA:
 * Herda de ExcecaoBase, usada quando dados inválidos são fornecidos
 * (ex: preço negativo, quantidade inválida, campos vazios)
 */
class ValidacaoException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de validação
     * @param msg Descrição do erro de validação
     */
    explicit ValidacaoException(const string& msg) 
        : ExcecaoBase("Erro de Validação: " + msg) {}
    // Chama construtor da classe base com mensagem formatada
    // Concatena "Erro de Validação: " + mensagem específica
};  // Fim da classe ValidacaoException

/**
 * @class ArtistaException
 * @brief Exceção relacionada a operações com artistas
 * 
 * Lançada quando ocorrem erros em operações de artistas
 * (ex: artista não encontrado, ID duplicado, camarim já ocupado)
 */
class ArtistaException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de erro de artista
     * @param msg Descrição do erro
     */
    explicit ArtistaException(const string& msg)
        : ExcecaoBase("Erro com Artista: " + msg) {}
    // Formata mensagem: "Erro com Artista: " + detalhes
};  // Fim da classe ArtistaException

/**
 * @class ItemException
 * @brief Exceção relacionada a operações com itens
 * 
 * Lançada quando ocorrem erros em operações de itens
 * (ex: item não encontrado, ID duplicado, dados inválidos)
 */
class ItemException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de erro de item
     * @param msg Descrição do erro
     */
    explicit ItemException(const string& msg)
        : ExcecaoBase("Erro com Item: " + msg) {}
    // Formata mensagem: "Erro com Item: " + detalhes
};  // Fim da classe ItemException

/**
 * @class EstoqueException
 * @brief Exceção relacionada a operações de estoque
 * 
 * Lançada quando ocorrem erros gerais no estoque
 * (ex: item não encontrado no estoque, operação inválida)
 */
class EstoqueException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de erro de estoque
     * @param msg Descrição do erro
     */
    explicit EstoqueException(const string& msg)
        : ExcecaoBase("Erro de Estoque: " + msg) {}
    // Formata mensagem: "Erro de Estoque: " + detalhes
};  // Fim da classe EstoqueException

/**
 * @class EstoqueInsuficienteException
 * @brief Exceção quando não há quantidade suficiente em estoque
 * 
 * HIERARQUIA DE TRÊS NÍVEIS:
 * EstoqueInsuficienteException → EstoqueException → ExcecaoBase → exception
 * 
 * Demonstra herança em cadeia: herda de EstoqueException (não de ExcecaoBase)
 * Usada quando tentam retirar mais itens do que há disponível
 */
class EstoqueInsuficienteException : public EstoqueException {  
    // HERDA de EstoqueException (que herda de ExcecaoBase)
    // Hierarquia: exception → ExcecaoBase → EstoqueException → EstoqueInsuficienteException
    
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de estoque insuficiente
     * @param msg Descrição detalhada (quantidade necessária vs disponível)
     */
    explicit EstoqueInsuficienteException(const string& msg)
        : EstoqueException("Estoque insuficiente: " + msg) {}
    // Chama construtor de EstoqueException (classe PAI)
    // que por sua vez chama ExcecaoBase (classe AVÔ)
    // Mensagem final: "Erro de Estoque: Estoque insuficiente: " + detalhes
};  // Fim da classe EstoqueInsuficienteException

/**
 * @class CamarimException
 * @brief Exceção relacionada a operações com camarins
 * 
 * Lançada quando ocorrem erros em operações de camarins
 * (ex: camarim não encontrado, ID duplicado, capacidade excedida)
 */
class CamarimException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de erro de camarim
     * @param msg Descrição do erro
     */
    explicit CamarimException(const string& msg)
        : ExcecaoBase("Erro com Camarim: " + msg) {}
    // Formata mensagem: "Erro com Camarim: " + detalhes
};  // Fim da classe CamarimException

/**
 * @class PedidoException
 * @brief Exceção relacionada a operações com pedidos
 * 
 * Lançada quando ocorrem erros em operações de pedidos
 * (ex: pedido não encontrado, status inválido, operação não permitida)
 */
class PedidoException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de erro de pedido
     * @param msg Descrição do erro
     */
    explicit PedidoException(const string& msg)
        : ExcecaoBase("Erro com Pedido: " + msg) {}
    // Formata mensagem: "Erro com Pedido: " + detalhes
};  // Fim da classe PedidoException

/**
 * @class ListaComprasException
 * @brief Exceção relacionada a operações com lista de compras
 * 
 * Lançada quando ocorrem erros em operações da lista de compras
 * (ex: lista não encontrada, item já na lista, operação inválida)
 */
class ListaComprasException : public ExcecaoBase {  // HERDA de ExcecaoBase
public:  // Construtor público
    /**
     * @brief Construtor que formata mensagem de erro de lista de compras
     * @param msg Descrição do erro
     */
    explicit ListaComprasException(const string& msg)
        : ExcecaoBase("Erro com Lista de Compras: " + msg) {}
    // Formata mensagem: "Erro com Lista de Compras: " + detalhes
};  // Fim da classe ListaComprasException

/**
 * RESUMO DA HIERARQUIA DE EXCEÇÕES:
 * 
 * std::exception (STL)
 *     ↓
 * ExcecaoBase (base customizada)
 *     ├── ValidacaoException (erros de validação)
 *     ├── ArtistaException (erros de artistas)
 *     ├── ItemException (erros de itens)
 *     ├── EstoqueException (erros de estoque)
 *     │       ↓
 *     │   EstoqueInsuficienteException (estoque insuficiente - 3 níveis!)
 *     ├── CamarimException (erros de camarins)
 *     ├── PedidoException (erros de pedidos)
 *     └── ListaComprasException (erros de lista de compras)
 * 
 * VANTAGENS:
 * 1. Tratamento específico com catch(TipoException& e)
 * 2. Mensagens formatadas automaticamente
 * 3. Polimorfismo: catch(ExcecaoBase& e) captura todas
 * 4. Hierarquia clara e organizada
 * 5. Demonstra herança de 3 níveis (EstoqueInsuficienteException)
 */

#endif // EXCECOES_H
// Fim do include guard - fecha a proteção contra inclusão múltipla
