/**
 * @file pedido.cpp
 * @brief Implementação da classe Pedido e GerenciadorPedidos
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa lógica de gerenciamento de pedidos de itens.
 */

// Inclui header da classe
#include "pedido.h"
// Inclui exceções customizadas
#include "excecoes.h"
// Algoritmos STL (remove_if, etc)
#include <algorithm>
// Para stringstream (construir strings)
#include <sstream>
// Para formatação (setw, left)
#include <iomanip>

// ==================== Classe Pedido ====================

/**
 * Construtor padrão - inicializa com valores vazios
 */
Pedido::Pedido() : id(0), camarimId(0), nomeArtista(""), atendido(false) {}
// atendido = false: pedido começa como PENDENTE

/**
 * Construtor parametrizado - inicializa com dados fornecidos
 */
Pedido::Pedido(int id, int camarimId, const string& nomeArtista)
    : id(id), camarimId(camarimId), nomeArtista(nomeArtista), atendido(false) {}
// Pedido sempre começa como não atendido (pendente)

/**
 * Destrutor - libera recursos
 */
Pedido::~Pedido() {}
// Map é destruído automaticamente

// ==================== GETTERS ====================

/**
 * Retorna ID do pedido
 */
int Pedido::getId() const {
    return id;  // Retorna cópia
}

/**
 * Retorna ID do camarim solicitante
 */
int Pedido::getCamarimId() const {
    return camarimId;
}

/**
 * Retorna nome do artista
 */
string Pedido::getNomeArtista() const {
    return nomeArtista;  // Retorna cópia da string
}

/**
 * Retorna status do pedido (atendido ou não)
 */
bool Pedido::isAtendido() const {
    return atendido;  // true = atendido, false = pendente
    // Convenção: is<Nome>() para métodos que retornam bool
}

// ==================== SETTERS ====================

/**
 * Define ID do pedido com validação
 */
void Pedido::setId(int id) {
    if (id < 0) {  // Validação
        throw ValidacaoException("ID do pedido inválido");
    }
    this->id = id;  // this-> diferencia parâmetro de atributo
}

/**
 * Define camarim solicitante com validação
 */
void Pedido::setCamarimId(int camarimId) {
    if (camarimId < 0) {  // ID deve ser positivo
        throw ValidacaoException("ID do camarim inválido");
    }
    this->camarimId = camarimId;
}

/**
 * Define nome do artista com validação
 */
void Pedido::setNomeArtista(const string& nomeArtista) {
    if (nomeArtista.empty()) {  // Nome não pode ser vazio
        throw ValidacaoException("Nome do artista não pode ser vazio");
    }
    this->nomeArtista = nomeArtista;
}

/**
 * Define status do pedido
 */
void Pedido::setAtendido(bool atendido) {
    this->atendido = atendido;  // Permite mudar de volta para pendente se necessário
}

/**
 * Adiciona item ao pedido
 */
void Pedido::adicionarItem(int itemId, const string& nomeItem, int quantidade) {
    // REGRA DE NEGÓCIO: não pode modificar pedido já atendido
    if (atendido) {
        throw PedidoException("Não é possível adicionar itens a um pedido já atendido");
    }
    
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
    
    // Adiciona ou atualiza item no map
    if (itens.find(itemId) != itens.end()) {
        // Item JÁ EXISTE: soma quantidade
        itens[itemId].quantidade += quantidade;
    } else {
        // Item NÃO EXISTE: cria novo ItemPedido
        itens[itemId] = ItemPedido(itemId, nomeItem, quantidade);
    }
}

/**
 * Remove item do pedido
 */
bool Pedido::removerItem(int itemId) {
    // REGRA DE NEGÓCIO: não pode modificar pedido já atendido
    if (atendido) {
        throw PedidoException("Não é possível remover itens de um pedido já atendido");
    }
    
    // Busca item no map
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {  // Não encontrou
        return false;  // Item não está no pedido
    }
    
    // Remove completamente do map (não subtrai quantidade)
    itens.erase(itemId);
    return true;  // Sucesso
}

/**
 * Marca pedido como atendido
 */
void Pedido::marcarAtendido() {
    atendido = true;  // Muda status para ATENDIDO
    // Chamado após transferir itens do estoque para o camarim
}

/**
 * Exibe informações completas do pedido
 */
string Pedido::exibir() const {
    stringstream ss;  // String stream para construir string
    ss << "=== PEDIDO ===" << endl;
    ss << "ID: " << id << endl;
    ss << "Camarim ID: " << camarimId << endl;
    ss << "Artista: " << nomeArtista << endl;
    
    // Operador ternário: condição ? valor_se_true : valor_se_false
    ss << "Status: " << (atendido ? "ATENDIDO" : "PENDENTE") << endl;
    
    ss << "\nItens:" << endl;
    
    if (itens.empty()) {  // Se não há itens
        ss << "  Nenhum item no pedido" << endl;
    } else {
        // Cabeçalho da tabela
        ss << left << setw(5) << "  ID" << setw(30) << "Nome" 
           << setw(10) << "Quantidade" << endl;
        ss << "  " << string(42, '-') << endl;
        
        // Lista todos os itens
        for (const auto& par : itens) {
            const ItemPedido& item = par.second;
            ss << left << setw(5) << "  " + to_string(item.itemId)
               << setw(30) << item.nomeItem
               << setw(10) << item.quantidade << endl;
        }
    }
    
    return ss.str();  // Converte para string
}

/**
 * Sobrecarga do operador << para cout
 */
ostream& operator<<(ostream& os, const Pedido& pedido) {
    os << pedido.exibir();  // Chama método exibir()
    return os;  // Retorna stream para encadeamento
}

// ==================== Classe GerenciadorPedidos ====================

/**
 * Construtor - inicializa próximo ID como 1
 */
GerenciadorPedidos::GerenciadorPedidos() : proximoId(1) {}

/**
 * Cria novo pedido (CREATE)
 */
int GerenciadorPedidos::criar(int camarimId, const string& nomeArtista) {
    // VALIDAÇÕES:
    if (camarimId < 0) {
        throw ValidacaoException("ID do camarim inválido");
    }
    
    if (nomeArtista.empty()) {
        throw ValidacaoException("Nome do artista não pode ser vazio");
    }
    
    // Cria pedido com ID automático
    Pedido novoPedido(proximoId, camarimId, nomeArtista);
    // Pedido começa vazio (sem itens) e pendente (não atendido)
    
    // Adiciona ao vector
    pedidos.push_back(novoPedido);
    // push_back() faz cópia do objeto
    
    return proximoId++;  // Retorna ID usado e incrementa para próximo
}

/**
 * Busca pedido por ID (READ)
 */
Pedido* GerenciadorPedidos::buscarPorId(int id) {
    // Percorre vector de pedidos
    for (auto& pedido : pedidos) {
        // auto& = referência (permite modificar)
        
        if (pedido.getId() == id) {  // Se encontrou
            return &pedido;  // Retorna PONTEIRO para o pedido
            // Ponteiro permite adicionar itens, marcar como atendido, etc
        }
    }
    return nullptr;  // Não encontrado
}

/**
 * Busca pedidos de um camarim específico (READ com filtro)
 */
vector<Pedido> GerenciadorPedidos::buscarPorCamarim(int camarimId) const {
    vector<Pedido> resultado;  // Vector vazio para armazenar resultados
    
    // Percorre todos os pedidos
    for (const auto& pedido : pedidos) {
        // const auto& = referência constante (não modifica)
        
        if (pedido.getCamarimId() == camarimId) {
            // Se pedido é deste camarim
            resultado.push_back(pedido);
            // Adiciona CÓPIA do pedido ao resultado
        }
    }
    
    return resultado;  // Retorna vector com todos os pedidos deste camarim
    // Útil para ver histórico de pedidos de um artista
}

/**
 * Lista apenas pedidos pendentes (READ com filtro)
 */
vector<Pedido> GerenciadorPedidos::listarPendentes() const {
    vector<Pedido> pendentes;  // Vector para armazenar apenas pendentes
    
    // Percorre todos os pedidos
    for (const auto& pedido : pedidos) {
        if (!pedido.isAtendido()) {
            // ! = operador NOT (negação)
            // Se NOT atendido = pendente
            
            pendentes.push_back(pedido);
            // Adiciona cópia ao vector
        }
    }
    
    return pendentes;  // Retorna apenas pedidos não atendidos
    // Útil para gerenciar fila de processamento
}

/**
 * Remove pedido (DELETE)
 */
bool GerenciadorPedidos::remover(int id) {
    // PADRÃO REMOVE-ERASE:
    auto it = remove_if(pedidos.begin(), pedidos.end(),
                       [id](const Pedido& p) { return p.getId() == id; });
    // LAMBDA: [id](const Pedido& p) { return p.getId() == id; }
    //   [id] = captura variável id por valor
    //   (const Pedido& p) = parâmetro (cada pedido)
    //   { return ... } = critério de remoção
    
    if (it != pedidos.end()) {  // Se encontrou pedido(s) a remover
        pedidos.erase(it, pedidos.end());
        // erase() remove do vector
        return true;  // Sucesso
    }
    return false;  // Não encontrado
}

/**
 * Lista todos os pedidos (READ ALL)
 */
vector<Pedido> GerenciadorPedidos::listar() const {
    return pedidos;  // Retorna CÓPIA de todo o vector
}
