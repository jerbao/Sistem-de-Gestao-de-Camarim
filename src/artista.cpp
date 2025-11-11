/**
 * @file artista.cpp
 * @brief Implementação da classe Artista e GerenciadorArtistas
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

// Inclui o header da classe Artista com as declarações
#include "artista.h"
// Inclui as exceções customizadas do sistema
#include "excecoes.h"
// Inclui algoritmos STL (remove_if, etc)
#include <algorithm>
// Inclui stringstream para construir strings formatadas
#include <sstream>

// ==================== Classe Artista ====================

// Construtor padrão - Inicializa artista com valores padrão
Artista::Artista() : Pessoa(), camarimId(0) {}  
// Pessoa() = chama construtor padrão da classe BASE (inicializa id=0, nome="")
// camarimId(0) = inicializa atributo específico da classe DERIVADA
// HERANÇA: construtor da classe filha DEVE chamar construtor da classe pai

// Construtor parametrizado - Recebe todos os valores necessários
Artista::Artista(int id, const string& nome, int camarimId)
    : Pessoa(id, nome), camarimId(camarimId) {}  
// Pessoa(id, nome) = chama construtor parametrizado da classe BASE
// Passa id e nome para a classe pai inicializar seus atributos
// camarimId(camarimId) = inicializa atributo adicional da classe DERIVADA

// Destrutor - Executado quando objeto Artista é destruído
Artista::~Artista() {}  
// Corpo vazio porque não há recursos para liberar
// Destrutor da classe BASE (Pessoa) será chamado automaticamente depois

// ==================== Getters ====================

int Artista::getCamarimId() const {
    return camarimId;  // Retorna o ID do camarim associado ao artista
}

// ==================== Setters com Validação ====================

void Artista::setCamarimId(int camarimId) {
    if (camarimId < 0) {  // VALIDAÇÃO: camarimId não pode ser negativo
        throw ValidacaoException("ID de camarim inválido");
    }
    this->camarimId = camarimId;  // Atribui novo valor se válido
}

// POLIMORFISMO: Implementação do método virtual puro da classe base
string Artista::exibir() const {
    stringstream ss;  // Cria stream para construir string formatada
    ss << "Artista [ID: " << id << ", Nome: " << nome 
       << ", Camarim ID: " << camarimId << "]";
    // Acessa 'id' e 'nome' que são PROTECTED na classe base Pessoa
    // HERANÇA permite acessar membros protected do pai
    return ss.str();  // Retorna string construída
}

// ==================== Classe GerenciadorArtistas ====================

// Construtor - Inicializa o gerenciador
GerenciadorArtistas::GerenciadorArtistas() : proximoId(1) {}  
// proximoId(1) = primeiro artista terá ID = 1
// Vetor 'artistas' é inicializado automaticamente vazio

// Cadastra novo artista no sistema (CREATE)
int GerenciadorArtistas::cadastrar(const string& nome, int camarimId) {
    // ========== VALIDAÇÕES ==========
    
    if (nome.empty()) {  // Verifica se nome não está vazio
        throw ValidacaoException("Nome do artista não pode ser vazio");
    }
    
    if (camarimId < 0) {  // Verifica se camarimId é válido
        throw ValidacaoException("ID de camarim inválido");
    }
    
    // ========== CADASTRO ==========
    
    Artista novoArtista(proximoId, nome, camarimId);  // Cria novo objeto Artista
    artistas.push_back(novoArtista);  // Adiciona ao vetor (no final)
    
    return proximoId++;  // Retorna ID usado e incrementa para próximo
}

// Busca artista por ID (READ)
Artista* GerenciadorArtistas::buscarPorId(int id) {
    // Percorre todos os artistas usando range-based for
    for (auto& artista : artistas) {  // auto = Artista (deduzido automaticamente)
        // & = referência (não copia, acessa diretamente)
        
        if (artista.getId() == id) {  // Compara ID do artista com ID buscado
            return &artista;  // Retorna PONTEIRO para o artista encontrado
        }
    }
    return nullptr;  // Se não encontrou, retorna ponteiro nulo
}

// Busca todos os artistas de um camarim específico (READ)
vector<Artista> GerenciadorArtistas::buscarPorCamarim(int camarimId) const {
    vector<Artista> resultado;  // Cria vetor vazio para armazenar resultado
    
    // Percorre todos os artistas
    for (const auto& artista : artistas) {  // const = não modifica
        if (artista.getCamarimId() == camarimId) {  // Se artista pertence ao camarim
            resultado.push_back(artista);  // Adiciona ao vetor resultado
        }
    }
    
    return resultado;  // Retorna vetor com todos os artistas do camarim
}

// Remove artista por ID (DELETE)
bool GerenciadorArtistas::remover(int id) {
    // Usa algoritmo remove_if da STL
    auto it = remove_if(artistas.begin(), artistas.end(),
                       [id](const Artista& a) { return a.getId() == id; });
    // Lambda [id] captura variável id do escopo externo
    // Lambda recebe cada artista e retorna true se deve ser removido
    // remove_if move elementos a serem removidos para o final do vetor
    
    if (it != artistas.end()) {  // Se encontrou artista para remover
        artistas.erase(it, artistas.end());  // Remove efetivamente do vetor
        return true;  // Retorna sucesso
    }
    return false;  // Se não encontrou, retorna falha
}

// Lista todos os artistas cadastrados (READ)
vector<Artista> GerenciadorArtistas::listar() const {
    return artistas;  // Retorna CÓPIA do vetor inteiro com todos os artistas
    // const = não modifica o estado do gerenciador
}

// Atualiza dados de um artista existente (UPDATE)
bool GerenciadorArtistas::atualizar(int id, const string& nome, int camarimId) {
    // Busca o artista pelo ID
    Artista* artista = buscarPorId(id);  // Recebe ponteiro para o artista
    
    if (artista == nullptr) {  // Se não encontrou (ponteiro nulo)
        // Lança exceção específica de Artista
        throw ArtistaException("Artista com ID " + to_string(id) + " não encontrado");
    }
    
    // Atualiza os dados usando setters (que fazem validação)
    artista->setNome(nome);  // Atualiza nome via ponteiro
    // -> = operador de acesso a membro via ponteiro
    artista->setCamarimId(camarimId);  // Atualiza camarimId via ponteiro
    
    return true;  // Retorna true indicando sucesso
}
