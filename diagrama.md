classDiagram
      class Pessoa {
        <<abstract>>
        #int id
        #string nome
        +Pessoa()
        +Pessoa(int id, string nome)
        +string exibir()* abstract
        +getId() int
        +setId(int id) void
        +getNome() string
        +setNome(string nome) void
    }

    class Artista {
        -int camarimId
        +Artista()
        +Artista(int id, string nome, int camarimId)
        +string exibir() override
        +getCamarimId() int
        +setCamarimId(int id) void
    }

    class Item {
        -int id
        -string nome
        -double preco
        +Item()
        +Item(int id, string nome, double preco)
        +getId() int
        +setId(int id) void
        +getNome() string
        +setNome(string nome) void
        +getPreco() double
        +setPreco(double preco) void
        +exibir() string
    }

    class Estoque {
        -map~int, ItemEstoque~ itens
        +Estoque()
        +adicionarItem(int itemId, string nome, int qtd) void
        +removerItem(int itemId, int qtd) bool
        +verificarDisponibilidade(int itemId, int qtd) bool
        +listar() vector~ItemEstoque~
    }

    class Camarim {
        -int id
        -string nome
        -int artistaId
        -map~int, ItemCamarim~ itens
        +Camarim()
        +Camarim(int id, string nome, int artistaId)
        +getId() int
        +setId(int id) void
        +getNome() string
        +setNome(string nome) void
        +getArtistaId() int
        +setArtistaId(int artistaId) void
        +inserirItem(int itemId, string nome, int qtd) void
        +removerItem(int itemId, int qtd) bool
        +listarItens() vector~ItemCamarim~
    }

    class Pedido {
        -int id
        -int camarimId
        -string nomeArtista
        -map~int, ItemPedido~ itens
        -bool atendido
        +Pedido()
        +Pedido(int id, int camarimId, string nomeArtista)
        +getId() int
        +setId(int id) void
        +getCamarimId() int
        +isAtendido() bool
        +setAtendido(bool status) void
        +adicionarItem(int itemId, string nome, int qtd) void
        +listarItens() vector~ItemPedido~
    }

    class ListaCompras {
        -int id
        -string descricao
        -map~int, ItemCompra~ itens
        +ListaCompras()
        +ListaCompras(int id, string descricao)
        +getId() int
        +setId(int id) void
        +getDescricao() string
        +setDescricao(string desc) void
        +adicionarItem(int itemId, string nome, int qtd, double preco) void
        +removerItem(int itemId) bool
        +calcularTotal() double
        +listarItens() vector~ItemCompra~
    }

    class GerenciadorArtistas {
        -vector~Artista~ artistas
        -int proximoId
        +GerenciadorArtistas()
        +cadastrar(string nome, int camarimId) int
        +buscarPorId(int id) Artista*
        +buscarPorCamarim(int camarimId) vector~Artista~
        +atualizar(int id, string nome, int camarimId) bool
        +remover(int id) bool
        +listar() vector~Artista~
    }

    class GerenciadorItens {
        -vector~Item~ itens
        -int proximoId
        +GerenciadorItens()
        +cadastrar(string nome, double preco) int
        +buscarPorId(int id) Item*
        +buscarPorNome(string nome) Item*
        +remover(int id) bool
        +listar() vector~Item~
        +atualizar(int id, string nome, double preco) bool
    }

    class GerenciadorCamarins {
        -vector~Camarim~ camarins
        -int proximoId
        +GerenciadorCamarins()
        +cadastrar(string nome, int artistaId) int
        +buscarPorId(int id) Camarim*
        +buscarPorArtista(int artistaId) Camarim*
        +remover(int id) bool
        +listar() vector~Camarim~
        +atualizar(int id, string nome, int artistaId) bool
    }

    class GerenciadorPedidos {
        -vector~Pedido~ pedidos
        -int proximoId
        +GerenciadorPedidos()
        +criar(int camarimId, string nomeArtista) int
        +buscarPorId(int id) Pedido*
        +buscarPorCamarim(int camarimId) vector~Pedido~
        +listarPendentes() vector~Pedido~
        +remover(int id) bool
        +listar() vector~Pedido~
    }

    class GerenciadorListaCompras {
        -vector~ListaCompras~ listas
        -int proximoId
        +GerenciadorListaCompras()
        +criar(string descricao) int
        +buscarPorId(int id) ListaCompras*
        +remover(int id) bool
        +listar() vector~ListaCompras~
    }

    class ExcecaoBase {
        <<abstract>>
        #string mensagem
        +ExcecaoBase(string msg)
        +const char* what() override
    }

    class ValidacaoException {
        +ValidacaoException(string msg)
        +const char* what() override
    }

    class ArtistaException {
        +ArtistaException(string msg)
        +const char* what() override
    }

    class ItemException {
        +ItemException(string msg)
        +const char* what() override
    }

    class EstoqueException {
        +EstoqueException(string msg)
        +const char* what() override
    }

    class EstoqueInsuficienteException {
        +EstoqueInsuficienteException(string msg)
        +const char* what() override
    }

    class CamarimException {
        +CamarimException(string msg)
        +const char* what() override
    }

    class PedidoException {
        +PedidoException(string msg)
        +const char* what() override
    }

    class ListaComprasException {
        +ListaComprasException(string msg)
        +const char* what() override
    }

    class ItemEstoque {
        +int itemId
        +string nomeItem
        +int quantidade
    }

    class ItemCamarim {
        +int itemId
        +string nomeItem
        +int quantidade
    }

    class ItemPedido {
        +int itemId
        +string nomeItem
        +int quantidade
    }

    class ItemCompra {
        +int itemId
        +string nomeItem
        +int quantidade
        +double preco
        +double subtotal
    }

    Pessoa <|-- Artista
    ExcecaoBase <|-- ValidacaoException
    ExcecaoBase <|-- ArtistaException
    ExcecaoBase <|-- ItemException
    ExcecaoBase <|-- EstoqueException
    EstoqueException <|-- EstoqueInsuficienteException
    ExcecaoBase <|-- CamarimException
    ExcecaoBase <|-- PedidoException
    ExcecaoBase <|-- ListaComprasException

    Estoque "1" *-- "0..*" ItemEstoque
    Camarim "1" *-- "0..*" ItemCamarim
    Pedido "1" *-- "0..*" ItemPedido
    ListaCompras "1" *-- "0..*" ItemCompra
    
    GerenciadorArtistas "1" --> "0..*" Artista
    GerenciadorItens "1" --> "0..*" Item
    GerenciadorCamarins "1" --> "0..*" Camarim
    GerenciadorPedidos "1" --> "0..*" Pedido
    GerenciadorListaCompras "1" --> "0..*" ListaCompras

    Pedido --> Item : utiliza
    ListaCompras --> Item : referencia
    Camarim --> Artista : alocado para
    Estoque --> Item : contém
