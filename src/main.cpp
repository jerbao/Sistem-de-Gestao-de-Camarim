/**
 * @file main.cpp
 * @brief Programa principal do Sistema de Gestão de Camarim
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Sistema interativo de gestão de camarins para artistas.
 * Demonstra POO completa: encapsulamento, herança, polimorfismo,
 * exceções, CRUD, containers STL, e interface de menu.
 */

// ==================== BIBLIOTECAS ====================
#include <iostream>   // Para cout, cin
#include <string>     // Para trabalhar com strings
#include <limits>     // Para numeric_limits (limpar buffer)
#include <iomanip>    // Para formatação (setw, left, right)

// ==================== HEADERS DO PROJETO ====================
#include "artista.h"      // Classe Artista e GerenciadorArtistas
#include "item.h"         // Classe Item e GerenciadorItens (catálogo)
#include "estoque.h"      // Classe Estoque (controle de estoque)
#include "camarim.h"      // Classe Camarim e GerenciadorCamarins
#include "pedido.h"       // Classe Pedido e GerenciadorPedidos
#include "listacompras.h" // Classe ListaCompras e gerenciador
#include "excecoes.h"     // Hierarquia de exceções customizadas

using namespace std;  // Namespace padrão da STL

// ==================== GERENCIADORES GLOBAIS ====================
// Instâncias globais dos gerenciadores (únicas em todo o programa)
GerenciadorArtistas gerenciadorArtistas;          // Gerencia artistas
GerenciadorItens gerenciadorItens;                // Gerencia catálogo de itens
Estoque estoque;                                   // Controla estoque central
GerenciadorCamarins gerenciadorCamarins;          // Gerencia camarins
GerenciadorPedidos gerenciadorPedidos;            // Gerencia pedidos de itens
GerenciadorListaCompras gerenciadorListaCompras;  // Gerencia listas de compras

/**
 * @brief Limpa buffer de entrada
 * 
 * PROBLEMA: Após ler número com cin >>, sobra '\n' no buffer
 * SOLUÇÃO: Limpa buffer antes de getline()
 * 
 * cin.clear() = limpa flags de erro
 * cin.ignore(max, '\n') = ignora caracteres até encontrar '\n'
 */
void limparBuffer() {
    cin.clear();  // Limpa flags de erro do stream
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // numeric_limits<streamsize>::max() = tamanho máximo do buffer
    // '\n' = delimitador (para ao encontrar quebra de linha)
}

/**
 * @brief Lê valor double aceitando vírgula ou ponto como separador decimal
 * 
 * PROBLEMA: cin >> double não aceita vírgula (padrão brasileiro)
 * SOLUÇÃO: Lê como string, substitui vírgula por ponto, converte para double
 * 
 * Exemplos: "4,5" → 4.5 | "10,99" → 10.99 | "3.14" → 3.14
 * 
 * @return Valor double lido e convertido
 */
double lerDouble() {
    string entrada;  // Lê entrada como string
    cin >> entrada;  // Lê string (até espaço/enter)
    
    // Substitui vírgula por ponto
    // Percorre cada caractere da string
    for (size_t i = 0; i < entrada.length(); i++) {
        // size_t = tipo para tamanhos/índices (unsigned)
        
        if (entrada[i] == ',') {  // Se encontrou vírgula
            entrada[i] = '.';      // Substitui por ponto
        }
    }
    
    // Converte string para double
    try {
        return stod(entrada);  
        // stod() = string to double
        // Lança invalid_argument se string não for número válido
    } catch (const invalid_argument& e) {
        // Se conversão falhar, retorna 0.0
        cout << "\n[AVISO] Valor inválido, usando 0.0" << endl;
        return 0.0;
    } catch (const out_of_range& e) {
        // Se número for muito grande
        cout << "\n[AVISO] Valor fora do alcance, usando 0.0" << endl;
        return 0.0;
    }
}

// ==================== Funções de Itens (Catálogo) ====================

/**
 * @brief Exibe todos os itens cadastrados no catálogo
 * 
 * Lista itens do CATÁLOGO (não do estoque!)
 * Catálogo = definição de itens disponíveis no sistema
 */
void exibirItens() {
    // Busca todos os itens do catálogo
    vector<Item> itens = gerenciadorItens.listar();
    
    if (itens.empty()) {  // Se não há itens cadastrados
        cout << "\nNenhum item cadastrado no catálogo.\n" << endl;
        return;  // Retorna cedo (early return)
    }
    
    cout << "\n=== Catálogo de Itens ===" << endl;
    // Percorre vector de itens
    for (const auto& item : itens) {
        // const auto& = referência constante (não copia, não modifica)
        cout << item.exibir() << endl;  // Chama método exibir() de cada item
    }
}

/**
 * @brief Cadastra novo item no catálogo
 * 
 * IMPORTANTE: Cadastra no CATÁLOGO, não no estoque!
 * Estoque é gerenciado separadamente (entrada/saída de quantidades)
 */
void cadastrarItem() {
    string nome;   // Nome do item
    double preco;  // Preço unitário
    
    cout << "\n=== Cadastrar Item no Catálogo ===" << endl;
    limparBuffer();  // Limpa buffer antes de getline()
    
    cout << "Nome do Item: ";
    getline(cin, nome);  // Lê linha completa (permite espaços)
    
    cout << "Preço unitário: R$ ";
    preco = lerDouble();  // Lê valor double aceitando vírgula ou ponto
    
    // TRY-CATCH: Captura exceções lançadas durante cadastro
    try {
        int id = gerenciadorItens.cadastrar(nome, preco);
        // Cadastra item e recebe ID gerado automaticamente
        
        cout << "\n[OK] Item cadastrado no catálogo com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        // Captura TODAS as exceções derivadas de ExcecaoBase
        // Polimorfismo: catch da classe base captura classes derivadas
        
        cout << "\n[ERRO] " << e.what() << endl;
        // what() = método virtual que retorna mensagem de erro
    }
}

/**
 * @brief Remove item do catálogo
 * 
 * ATENÇÃO: Remove do catálogo, não do estoque!
 */
void removerItem() {
    int id;  // ID do item a remover
    
    cout << "\n=== Remover Item do Catálogo ===" << endl;
    cout << "Digite o ID do item: ";
    cin >> id;
    
    try {
        if (gerenciadorItens.remover(id)) {
            // remover() retorna true se encontrou e removeu
            cout << "\n[OK] Item removido do catálogo com sucesso!" << endl;
        } else {
            // remover() retorna false se não encontrou
            cout << "\n[ERRO] Item não encontrado!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

/**
 * @brief Atualiza dados de um item do catálogo
 * 
 * Permite alterar nome e preço de item existente
 */
void atualizarItem() {
    int id;        // ID do item a atualizar
    string nome;   // Novo nome
    double preco;  // Novo preço
    
    cout << "\n=== Atualizar Item do Catálogo ===" << endl;
    cout << "ID do Item: ";
    cin >> id;
    limparBuffer();  // Limpa buffer após ler número
    
    cout << "Novo Nome: ";
    getline(cin, nome);  // Lê linha completa
    
    cout << "Novo Preço: R$ ";
    preco = lerDouble();  // Lê valor double aceitando vírgula ou ponto
    
    try {
        if (gerenciadorItens.atualizar(id, nome, preco)) {
            cout << "\n[OK] Item atualizado com sucesso!" << endl;
        } else {
            cout << "\n[ERRO] Item não encontrado!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

/**
 * @brief Busca item no catálogo por nome
 * 
 * Busca exata (case-sensitive)
 */
void buscarItemPorNome() {
    string nome;
    
    cout << "\n=== Buscar Item por Nome ===" << endl;
    limparBuffer();
    
    cout << "Nome do Item: ";
    getline(cin, nome);
    
    // Busca retorna PONTEIRO (nullptr se não encontrar)
    Item* item = gerenciadorItens.buscarPorNome(nome);
    
    if (item) {  // Se ponteiro não é nullptr (encontrou)
        cout << "\n" << item->exibir() << endl;
        // item-> = acesso a método através de ponteiro
    } else {
        cout << "\n[AVISO] Item não encontrado no catálogo!" << endl;
    }
}

// ==================== Funções de Artista ====================

/**
 * @brief Exibe todos os artistas cadastrados
 * 
 * Lista artistas com seus IDs e camarins associados
 */
void exibirArtistas() {
    vector<Artista> artistas = gerenciadorArtistas.listar();
    
    if (artistas.empty()) {
        cout << "\nNenhum artista cadastrado.\n" << endl;
        return;
    }
    
    cout << "\n=== Lista de Artistas ===" << endl;
    for (const auto& artista : artistas) {
        // Chama método exibir() polimórfico
        // Artista sobrescreve método de Pessoa
        cout << artista.exibir() << endl;
    }
}

/**
 * @brief Cadastra novo artista no sistema
 * 
 * Artista HERDA de Pessoa
 * Adiciona atributo camarimId específico
 */
void cadastrarArtista() {
    string nome;       // Nome do artista
    int camarimId;     // ID do camarim (0 = sem camarim)
    
    cout << "\n=== Cadastrar Artista ===" << endl;
    limparBuffer();
    
    cout << "Nome: ";
    getline(cin, nome);
    
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    try {
        int id = gerenciadorArtistas.cadastrar(nome, camarimId);
        cout << "\n[OK] Artista cadastrado com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerArtista() {
    int id;
    cout << "\n=== Remover Artista ===" << endl;
    cout << "Digite o ID do artista: ";
    cin >> id;
    
    try {
        gerenciadorArtistas.remover(id);
        cout << "\n[OK] Artista removido com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void atualizarArtista() {
    int id, camarimId;
    string nome;
    
    cout << "\n=== Atualizar Artista ===" << endl;
    cout << "ID do Artista: ";
    cin >> id;
    limparBuffer();
    
    cout << "Novo Nome: ";
    getline(cin, nome);
    
    cout << "Novo ID do Camarim: ";
    cin >> camarimId;
    
    try {
        if (gerenciadorArtistas.atualizar(id, nome, camarimId)) {
            cout << "\n[OK] Artista atualizado com sucesso!" << endl;
        } else {
            cout << "\n[ERRO] Artista não encontrado!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Estoque ====================

void exibirEstoque() {
    auto itens = estoque.listar();
    if (itens.empty()) {
        cout << "\nEstoque vazio.\n" << endl;
        return;
    }
    
    cout << "\n=== Estoque ===" << endl;
    cout << estoque << endl;
}

void cadastrarItemEstoque() {
    int itemId, quantidade;
    
    cout << "\n=== Adicionar Item ao Estoque ===" << endl;
    cout << "ID do Item (do catálogo): ";
    cin >> itemId;
    
    // Buscar item no catálogo
    Item* item = gerenciadorItens.buscarPorId(itemId);
    if (!item) {
        cout << "\n[ERRO] Item não encontrado no catálogo!" << endl;
        cout << "Dica: Cadastre o item no catálogo primeiro (Menu Itens)." << endl;
        return;
    }
    
    cout << "Item selecionado: " << item->getNome() << endl;
    cout << "Quantidade: ";
    cin >> quantidade;
    
    try {
        estoque.adicionarItem(item->getId(), item->getNome(), quantidade);
        cout << "\n[OK] Item adicionado ao estoque!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerItemEstoque() {
    int itemId, quantidade;
    
    cout << "\n=== Remover Item do Estoque ===" << endl;
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Quantidade a remover: ";
    cin >> quantidade;
    
    try {
        estoque.removerItem(itemId, quantidade);
        cout << "\n[OK] Item removido do estoque!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void verificarDisponibilidadeEstoque() {
    int itemId, quantidade;
    cout << "\n=== Verificar Disponibilidade ===" << endl;
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Quantidade desejada: ";
    cin >> quantidade;
    
    if (estoque.verificarDisponibilidade(itemId, quantidade)) {
        cout << "\n[OK] Quantidade disponível em estoque!" << endl;
    } else {
        cout << "\n[AVISO] Quantidade insuficiente em estoque!" << endl;
    }
}

void consultarQuantidadeEstoque() {
    int itemId;
    cout << "\n=== Consultar Quantidade ===" << endl;
    cout << "ID do Item: ";
    cin >> itemId;
    
    int quantidade = estoque.obterQuantidade(itemId);
    
    if (quantidade > 0) {
        cout << "\nQuantidade em estoque: " << quantidade << endl;
    } else {
        cout << "\n[AVISO] Item não encontrado no estoque!" << endl;
    }
}

void atualizarQuantidadeEstoque() {
    int itemId, novaQuantidade;
    cout << "\n=== Atualizar Quantidade ===" << endl;
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Nova Quantidade: ";
    cin >> novaQuantidade;
    
    try {
        estoque.atualizarQuantidade(itemId, novaQuantidade);
        cout << "\n[OK] Quantidade atualizada!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Camarim ====================

void exibirCamarins() {
    vector<Camarim> camarins = gerenciadorCamarins.listar();
    if (camarins.empty()) {
        cout << "\nNenhum camarim cadastrado." << endl;
        return;
    }
    
    cout << "\n=== Lista de Camarins ===" << endl;
    for (const auto& camarim : camarins) {
        cout << camarim.exibir() << endl;
    }
}

void cadastrarCamarim() {
    string nome;
    int artistaId;
    
    cout << "\n=== Cadastrar Camarim ===" << endl;
    limparBuffer();
    
    cout << "Nome do Camarim: ";
    getline(cin, nome);
    
    cout << "ID do Artista: ";
    cin >> artistaId;
    
    try {
        int id = gerenciadorCamarins.cadastrar(nome, artistaId);
        cout << "\n[OK] Camarim cadastrado com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerCamarim() {
    int id;
    cout << "\n=== Remover Camarim ===" << endl;
    cout << "Digite o ID do camarim: ";
    cin >> id;
    
    try {
        if (gerenciadorCamarins.remover(id)) {
            cout << "\n[OK] Camarim removido com sucesso!" << endl;
        } else {
            cout << "\n[ERRO] Camarim não encontrado!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void cadastrarItemCamarim() {
    int camarimId, itemId, quantidade;
    
    cout << "\n=== Adicionar Item ao Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    Camarim* camarim = gerenciadorCamarins.buscarPorId(camarimId);
    if (!camarim) {
        cout << "\n[ERRO] Camarim não encontrado!" << endl;
        return;
    }
    
    cout << "ID do Item (do catálogo): ";
    cin >> itemId;
    
    // Buscar item no catálogo
    Item* item = gerenciadorItens.buscarPorId(itemId);
    if (!item) {
        cout << "\n[ERRO] Item não encontrado no catálogo!" << endl;
        cout << "Dica: Cadastre o item no catálogo primeiro (Menu Itens)." << endl;
        return;
    }
    
    cout << "Item selecionado: " << item->getNome() << endl;
    cout << "Quantidade: ";
    cin >> quantidade;
    
    try {
        camarim->inserirItem(item->getId(), item->getNome(), quantidade);
        cout << "\n[OK] Item adicionado ao camarim!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerItemCamarim() {
    int camarimId, itemId, quantidade;
    
    cout << "\n=== Remover Item do Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    Camarim* camarim = gerenciadorCamarins.buscarPorId(camarimId);
    if (!camarim) {
        cout << "\n[ERRO] Camarim não encontrado!" << endl;
        return;
    }
    
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Quantidade a remover: ";
    cin >> quantidade;
    
    try {
        camarim->removerItem(itemId, quantidade);
        cout << "\n[OK] Item removido do camarim!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void atualizarCamarim() {
    int id, artistaId;
    string nome;
    
    cout << "\n=== Atualizar Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> id;
    limparBuffer();
    
    cout << "Novo Nome: ";
    getline(cin, nome);
    
    cout << "Novo ID do Artista: ";
    cin >> artistaId;
    
    try {
        if (gerenciadorCamarins.atualizar(id, nome, artistaId)) {
            cout << "\n[OK] Camarim atualizado com sucesso!" << endl;
        } else {
            cout << "\n[ERRO] Camarim não encontrado!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void buscarCamarimPorArtista() {
    int artistaId;
    
    cout << "\n=== Buscar Camarim por Artista ===" << endl;
    cout << "ID do Artista: ";
    cin >> artistaId;
    
    Camarim* camarim = gerenciadorCamarins.buscarPorArtista(artistaId);
    
    if (camarim) {
        cout << "\n" << camarim->exibir() << endl;
    } else {
        cout << "\n[AVISO] Nenhum camarim encontrado para este artista!" << endl;
    }
}

// ==================== Funções de Pedidos ====================

void exibirPedidos() {
    vector<Pedido> pedidos = gerenciadorPedidos.listar();
    if (pedidos.empty()) {
        cout << "\nNenhum pedido cadastrado.\n" << endl;
        return;
    }
    
    cout << "\n=== Lista de Pedidos ===" << endl;
    for (const auto& pedido : pedidos) {
        cout << pedido << endl;
    }
}

void cadastrarPedido() {
    int camarimId;
    string nomeArtista;
    
    cout << "\n=== Criar Pedido ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    limparBuffer();
    
    cout << "Nome do Artista: ";
    getline(cin, nomeArtista);
    
    try {
        int id = gerenciadorPedidos.criar(camarimId, nomeArtista);
        cout << "\n[OK] Pedido criado com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerPedido() {
    int id;
    cout << "\n=== Remover Pedido ===" << endl;
    cout << "Digite o ID do pedido: ";
    cin >> id;
    
    try {
        gerenciadorPedidos.remover(id);
        cout << "\n[OK] Pedido removido com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void adicionarItemPedido() {
    int pedidoId, itemId, quantidade;
    
    cout << "\n=== Adicionar Item ao Pedido ===" << endl;
    cout << "ID do Pedido: ";
    cin >> pedidoId;
    
    Pedido* pedido = gerenciadorPedidos.buscarPorId(pedidoId);
    if (!pedido) {
        cout << "\n[ERRO] Pedido não encontrado!" << endl;
        return;
    }
    
    cout << "ID do Item (do catálogo): ";
    cin >> itemId;
    
    // Buscar item no catálogo
    Item* item = gerenciadorItens.buscarPorId(itemId);
    if (!item) {
        cout << "\n[ERRO] Item não encontrado no catálogo!" << endl;
        cout << "Dica: Cadastre o item no catálogo primeiro (Menu Itens)." << endl;
        return;
    }
    
    cout << "Item selecionado: " << item->getNome() << endl;
    cout << "Quantidade: ";
    cin >> quantidade;
    
    try {
        pedido->adicionarItem(item->getId(), item->getNome(), quantidade);
        cout << "\n[OK] Item adicionado ao pedido!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerItemPedido() {
    int pedidoId, itemId;
    
    cout << "\n=== Remover Item do Pedido ===" << endl;
    cout << "ID do Pedido: ";
    cin >> pedidoId;
    
    Pedido* pedido = gerenciadorPedidos.buscarPorId(pedidoId);
    if (!pedido) {
        cout << "\n[ERRO] Pedido não encontrado!" << endl;
        return;
    }
    
    cout << "ID do Item: ";
    cin >> itemId;
    
    try {
        if (pedido->removerItem(itemId)) {
            cout << "\n[OK] Item removido do pedido!" << endl;
        } else {
            cout << "\n[ERRO] Item não encontrado no pedido!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void marcarPedidoAtendido() {
    int pedidoId;
    
    cout << "\n=== Marcar Pedido como Atendido ===" << endl;
    cout << "ID do Pedido: ";
    cin >> pedidoId;
    
    Pedido* pedido = gerenciadorPedidos.buscarPorId(pedidoId);
    if (!pedido) {
        cout << "\n[ERRO] Pedido não encontrado!" << endl;
        return;
    }
    
    try {
        pedido->marcarAtendido();
        cout << "\n[OK] Pedido marcado como atendido!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void listarPedidosPendentes() {
    vector<Pedido> pedidos = gerenciadorPedidos.listarPendentes();
    if (pedidos.empty()) {
        cout << "\nNenhum pedido pendente." << endl;
        return;
    }
    
    cout << "\n=== Pedidos Pendentes ===" << endl;
    for (const auto& pedido : pedidos) {
        cout << pedido.exibir() << endl;
    }
}

void buscarPedidosPorCamarim() {
    int camarimId;
    
    cout << "\n=== Buscar Pedidos por Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    vector<Pedido> pedidos = gerenciadorPedidos.buscarPorCamarim(camarimId);
    
    if (pedidos.empty()) {
        cout << "\nNenhum pedido encontrado para este camarim." << endl;
        return;
    }
    
    cout << "\n=== Pedidos do Camarim " << camarimId << " ===" << endl;
    for (const auto& pedido : pedidos) {
        cout << pedido.exibir() << endl;
    }
}

void buscarArtistasPorCamarim() {
    int camarimId;
    
    cout << "\n=== Buscar Artistas por Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    vector<Artista> artistas = gerenciadorArtistas.buscarPorCamarim(camarimId);
    
    if (artistas.empty()) {
        cout << "\nNenhum artista encontrado para este camarim." << endl;
        return;
    }
    
    cout << "\n=== Artistas do Camarim " << camarimId << " ===" << endl;
    for (const auto& artista : artistas) {
        cout << artista.exibir() << endl;
    }
}

// ==================== Funções de Lista de Compras ====================

void exibirListasCompras() {
    vector<ListaCompras> listas = gerenciadorListaCompras.listar();
    if (listas.empty()) {
        cout << "\nNenhuma lista de compras cadastrada.\n" << endl;
        return;
    }
    
    cout << "\n=== Listas de Compras ===" << endl;
    for (const auto& lista : listas) {
        cout << lista << endl;
    }
}

void cadastrarListaCompras() {
    string descricao;
    
    cout << "\n=== Criar Lista de Compras ===" << endl;
    limparBuffer();
    
    cout << "Descrição: ";
    getline(cin, descricao);
    
    try {
        int id = gerenciadorListaCompras.criar(descricao);
        cout << "\n[OK] Lista de compras criada com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerListaCompras() {
    int id;
    cout << "\n=== Remover Lista de Compras ===" << endl;
    cout << "Digite o ID da lista: ";
    cin >> id;
    
    try {
        gerenciadorListaCompras.remover(id);
        cout << "\n[OK] Lista de compras removida com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void adicionarItemListaCompras() {
    int listaId, itemId, quantidade;
    
    cout << "\n=== Adicionar Item à Lista de Compras ===" << endl;
    cout << "ID da Lista: ";
    cin >> listaId;
    
    ListaCompras* lista = gerenciadorListaCompras.buscarPorId(listaId);
    if (!lista) {
        cout << "\n[ERRO] Lista não encontrada!" << endl;
        return;
    }
    
    cout << "ID do Item (do catálogo): ";
    cin >> itemId;
    
    // Buscar item no catálogo
    Item* item = gerenciadorItens.buscarPorId(itemId);
    if (!item) {
        cout << "\n[ERRO] Item não encontrado no catálogo!" << endl;
        cout << "Dica: Cadastre o item no catálogo primeiro (Menu Itens)." << endl;
        return;
    }
    
    cout << "Item selecionado: " << item->getNome() << " - R$ " << fixed << setprecision(2) << item->getPreco() << endl;
    cout << "Quantidade: ";
    cin >> quantidade;
    
    try {
        lista->adicionarItem(item->getId(), item->getNome(), quantidade, item->getPreco());
        cout << "\n[OK] Item adicionado à lista!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerItemListaCompras() {
    int listaId, itemId;
    
    cout << "\n=== Remover Item da Lista de Compras ===" << endl;
    cout << "ID da Lista: ";
    cin >> listaId;
    
    ListaCompras* lista = gerenciadorListaCompras.buscarPorId(listaId);
    if (!lista) {
        cout << "\n[ERRO] Lista não encontrada!" << endl;
        return;
    }
    
    cout << "ID do Item: ";
    cin >> itemId;
    
    try {
        if (lista->removerItem(itemId)) {
            cout << "\n[OK] Item removido da lista!" << endl;
        } else {
            cout << "\n[ERRO] Item não encontrado na lista!" << endl;
        }
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void atualizarQuantidadeItemLista() {
    int listaId, itemId, quantidade;
    
    cout << "\n=== Atualizar Quantidade de Item ===" << endl;
    cout << "ID da Lista: ";
    cin >> listaId;
    
    ListaCompras* lista = gerenciadorListaCompras.buscarPorId(listaId);
    if (!lista) {
        cout << "\n[ERRO] Lista não encontrada!" << endl;
        return;
    }
    
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Nova Quantidade: ";
    cin >> quantidade;
    
    try {
        lista->atualizarQuantidade(itemId, quantidade);
        cout << "\n[OK] Quantidade atualizada!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void calcularTotalListaCompras() {
    int listaId;
    
    cout << "\n=== Calcular Total da Lista ===" << endl;
    cout << "ID da Lista: ";
    cin >> listaId;
    
    ListaCompras* lista = gerenciadorListaCompras.buscarPorId(listaId);
    if (!lista) {
        cout << "\n[ERRO] Lista não encontrada!" << endl;
        return;
    }
    
    double total = lista->calcularTotal();
    cout << "\n=== TOTAL ===" << endl;
    cout << fixed << setprecision(2);
    cout << "R$ " << total << endl;
}

void limparListaCompras() {
    int listaId;
    
    cout << "\n=== Limpar Lista de Compras ===" << endl;
    cout << "ID da Lista: ";
    cin >> listaId;
    
    ListaCompras* lista = gerenciadorListaCompras.buscarPorId(listaId);
    if (!lista) {
        cout << "\n[ERRO] Lista não encontrada!" << endl;
        return;
    }
    
    try {
        lista->limpar();
        cout << "\n[OK] Lista de compras limpa!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}


void menuPrincipal(){
    cout << "____Menu de Principal___" << endl;
    cout << "1. Catálogo de Itens" << endl;
    cout << "2. Estoque" << endl;
    cout << "3. Camarim" << endl;
    cout << "4. Artista" << endl;
    cout << "5. Lista de Pedidos" << endl;
    cout << "6. Lista de Compras" << endl;
    cout << "0. Finalizar" << endl;
}

void menuSub(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "0. Retornar" << endl;
}

void menuSubItens(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "4. Atualizar" << endl;
    cout << "5. Buscar por Nome" << endl;
    cout << "0. Retornar" << endl;
}

void menuSubEstoque(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar Item" << endl;
    cout << "3. Remover Item" << endl;
    cout << "4. Verificar Disponibilidade" << endl;
    cout << "5. Consultar Quantidade" << endl;
    cout << "6. Atualizar Quantidade" << endl;
    cout << "0. Retornar" << endl;
}

void menuSubArtistas(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "4. Atualizar" << endl;
    cout << "5. Buscar por Camarim" << endl;
    cout << "0. Retornar" << endl;
}

void menuSubCamarins(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "4. Adicionar Item" << endl;
    cout << "5. Remover Item" << endl;
    cout << "6. Atualizar" << endl;
    cout << "7. Buscar por Artista" << endl;
    cout << "0. Retornar" << endl;
}

void menuSubPedidos(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "4. Adicionar Item" << endl;
    cout << "5. Remover Item" << endl;
    cout << "6. Marcar Atendido" << endl;
    cout << "7. Listar Pendentes" << endl;
    cout << "8. Buscar por Camarim" << endl;
    cout << "0. Retornar" << endl;
}

void menuSubListaCompras(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "4. Adicionar Item" << endl;
    cout << "5. Remover Item" << endl;
    cout << "6. Atualizar Quantidade" << endl;
    cout << "7. Calcular Total" << endl;
    cout << "8. Limpar Lista" << endl;
    cout << "0. Retornar" << endl;
}




int main(){
    // Configurar codificação UTF-8 no Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    int opcao1, opcao2;
    
    do {
        menuPrincipal();
        cout << "\nDigite uma opção: ";
        
        cin >> opcao1;
        cout << endl;
        
            switch(opcao1){
                case 1:  
                do {
                    //Chama o submenu 1.Catálogo de Itens e aguarda interação
                    
                    cout << "Menu de Catálogo de Itens: \n";
                    menuSubItens();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirItens();
                        break;
                        
                        case 2: 
                        cadastrarItem();
                        break;
                        
                        case 3: 
                        removerItem();
                        break;
                        
                        case 4:
                        atualizarItem();
                        break;
                        
                        case 5:
                        buscarItemPorNome();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 2:  
                do {
                    //Chama o submenu 2.Estoque e aguarda interação
                    
                    cout << "Menu de Estoque: \n";
                    menuSubEstoque();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirEstoque();
                        break;
                        
                        case 2: 
                        cadastrarItemEstoque();
                        break;
                        
                        case 3: 
                        removerItemEstoque();
                        break;
                        
                        case 4:
                        verificarDisponibilidadeEstoque();
                        break;
                        
                        case 5:
                        consultarQuantidadeEstoque();
                        break;
                        
                        case 6:
                        atualizarQuantidadeEstoque();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 3:  
                do {
                    //Chama o submenu 2.Camarim e aguarda interação
                    
                    cout << "Menu de Camarim: \n";
                    menuSubCamarins();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirCamarins();
                        break;
                        
                        case 2: 
                        cadastrarCamarim();
                        break;
                        
                        case 3: 
                        removerCamarim();
                        break;
                        
                        case 4:
                        cadastrarItemCamarim();
                        break;
                        
                        case 5:
                        removerItemCamarim();
                        break;
                        
                        case 6:
                        atualizarCamarim();
                        break;
                        
                        case 7:
                        buscarCamarimPorArtista();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 4:  
                do {
                    //Chama o submenu 4.Artistas e aguarda interação
                    
                    cout << "Menu de Artistas: \n";
                    menuSubArtistas();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirArtistas();
                        break;
                        
                        case 2: 
                        cadastrarArtista();
                        break;
                        
                        case 3: 
                        removerArtista();
                        break;
                        
                        case 4:
                        atualizarArtista();
                        break;
                        
                        case 5:
                        buscarArtistasPorCamarim();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 5:  
                do {
                    //Chama o submenu 5.Lista de Pedidos e aguarda interação
                    
                    cout << "Menu de Lista de Pedidos: \n";
                    menuSubPedidos();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirPedidos();
                        break;
                        
                        case 2: 
                        cadastrarPedido();
                        break;
                        
                        case 3: 
                        removerPedido();
                        break;
                        
                        case 4:
                        adicionarItemPedido();
                        break;
                        
                        case 5:
                        removerItemPedido();
                        break;
                        
                        case 6:
                        marcarPedidoAtendido();
                        break;
                        
                        case 7:
                        listarPedidosPendentes();
                        break;
                        
                        case 8:
                        buscarPedidosPorCamarim();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 6:  
                do {
                    //Chama o submenu 6.Lista de Compras e aguarda interação
                    
                    cout << "Menu de Lista de Compras: \n";
                    menuSubListaCompras();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirListasCompras();
                        break;
                        
                        case 2: 
                        cadastrarListaCompras();
                        break;
                        
                        case 3: 
                        removerListaCompras();
                        break;
                        
                        case 4:
                        adicionarItemListaCompras();
                        break;
                        
                        case 5:
                        removerItemListaCompras();
                        break;
                        
                        case 6:
                        atualizarQuantidadeItemLista();
                        break;
                        
                        case 7:
                        calcularTotalListaCompras();
                        break;
                        
                        case 8:
                        limparListaCompras();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 0: cout << "Finalizando programa"; break; 
                default: cout <<"Digite uma opção válida...\n" << endl; // retorna ao menu principal
                
            }
            
        
    
    } while (opcao1 != 0);
    
    
}
