# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** LP1
- **Professor:** Prof. Jerffeson Gomes Dutra

  
## Atividade LP1 - Desenvolver uma aplicação funcional, utilizando os principais conceitos da programação orientada a objetos (POO). A aplicação deve conter um conjunto mínimo de funcionalidades que envolvam cadastro, consulta, alteração e remoção de dados (CRUD).

###  **Requisitos Mínimos do Projeto**

1. **Mínimo de 8 Classes  (25 classes implementadas!)**
   - **7 Classes Principais:** Pessoa, Artista, Item, Estoque, Camarim, Pedido, ListaCompras
   - **5 Classes Gerenciadoras:** GerenciadorArtistas, GerenciadorItens, GerenciadorCamarins, GerenciadorPedidos, GerenciadorListaCompras
   - **9 Classes de Exceção:** ExcecaoBase + 8 exceções derivadas
   - **4 Structs Auxiliares:** ItemEstoque, ItemCamarim, ItemPedido, ItemCompra

2. **Encapsulamento de todas as entidades **
   - Todos os atributos declarados como `private` ou `protected`
   - Acesso controlado via **getters e setters** com validações
   - Código **100% comentado** com explicações de POO

3. **Mínimo de 2 Heranças com Classes Base Diferentes **
   - **Hierarquia 1:** Artista herda de Pessoa (com polimorfismo)
   - **Hierarquia 2:** Sistema de exceções → ExcecaoBase + 8 exceções derivadas
   - **Bônus:** Hierarquia de **3 níveis** → EstoqueInsuficienteException → EstoqueException → ExcecaoBase

4. **Classes Bases Distintas **
   - `Pessoa` (base para modelo de domínio)
   - `ExcecaoBase` (base para sistema de exceções customizadas)

5. **Mínimo de 2 Polimorfismos **
   - Método virtual puro `exibir()` em Pessoa, sobrescrito em Artista
   - Método virtual `what()` sobrescrito em todas as 8 exceções

6. **CRUD para mínimo de 6 entidades **
   - **Create, Read, Update, Delete** implementados para:
     Artista | Item | Estoque | Camarim | Pedido | ListaCompras

7. **Sobrecarga do operador << **
   - Implementado em **7 classes:** Pessoa, Artista, Item, Estoque, Camarim, Pedido, ListaCompras

8. **Tratamento de exceções **
   - Try-catch em todas as operações críticas
   - Validações que lançam exceções específicas

9. **Exceções personalizadas **
   - **9 classes** de exceções customizadas
   - Hierarquia organizada em **3 níveis de profundidade**

10. **Validação de dados com exceções **
    - Validações em setters (encapsulamento)
    - Verificações em operações de negócio
    - Tratamento robusto e granular de erros

11. **Diagrama de Classes UML **
    - Arquivo `diagrama.md` (formato Mermaid) com todas as relações

12. **Sistema funcional **
    - Interface interativa via menus
    - Sistema modular e extensível
    - Suporte a **formato brasileiro** (entrada decimal com vírgula)


###  **Observações**
1. Todas as heranças, implementações e polimorfismo devem ser de classes próprias. Herança e implementação de classes oriundas de bibliotecas, frameworks e afins não serão consideradas.

---

## 📋 **Detalhamento dos Requisitos Obrigatórios**

### 1️⃣ **Sobrecarga de Operador << (operator<<)**

A sobrecarga do operador `<<` permite a **saída formatada de objetos** diretamente em streams (como `cout`), tornando a impressão de dados intuitiva e elegante. Implementada em todas as 7 classes principais do sistema.

#### **📍 Localização das Implementações:**

| Classe | Arquivo Header | Arquivo Implementação | Linha (aprox.) |
|--------|---------------|----------------------|----------------|
| **Pessoa** | `header/pessoa.h` | `src/pessoa.cpp` | ~40-50 |
| **Artista** | `header/artista.h` | `src/artista.cpp` | ~50-60 |
| **Item** | `header/item.h` | `src/item.cpp` | ~80-90 |
| **Estoque** | `header/estoque.h` | `src/estoque.cpp` | ~150-170 |
| **Camarim** | `header/camarim.h` | `src/camarim.cpp` | ~140-160 |
| **Pedido** | `header/pedido.h` | `src/pedido.cpp` | ~170-190 |
| **ListaCompras** | `header/listacompras.h` | `src/listacompras.cpp` | ~180-200 |

#### **💡 Implementação Técnica:**

```cpp
// Declaração em pessoa.h (friend function para acessar membros privados)
friend ostream& operator<<(ostream& os, const Pessoa& pessoa);

// Implementação em pessoa.cpp
ostream& operator<<(ostream& os, const Pessoa& pessoa) {
    os << pessoa.exibir();  // Utiliza polimorfismo para chamar a versão correta
    return os;              // Retorna stream para permitir encadeamento
}
```

**Benefício:** Sintaxe simplificada e intuitiva
```cpp
Pessoa* artista = new Artista(1, "João Silva", 10);
cout << *artista;  // Sintaxe limpa! operator<< usa exibir() polimórfico
```

---

### 2️⃣ **Herança (2 Hierarquias Independentes)**

O projeto implementa **duas hierarquias de herança completamente distintas**, cumprindo o requisito de classes base diferentes.

#### **Hierarquia 1: Modelo de Domínio (Pessoa → Artista)**
- **Classe Base:** `Pessoa` (classe abstrata com método virtual puro)
- **Classe Derivada:** `Artista` (herda atributos e comportamentos de Pessoa)
- **Arquivos:** `header/pessoa.h`, `header/artista.h`, `src/pessoa.cpp`, `src/artista.cpp`

```cpp
// pessoa.h - Classe base abstrata
class Pessoa {
protected:
    int id;          // Atributos protegidos: acessíveis na classe derivada
    string nome;
public:
    virtual ~Pessoa() {}                    // Destrutor virtual (essencial em hierarquias)
    virtual string exibir() const = 0;      // Método virtual puro = classe abstrata
};

// artista.h - Classe derivada concreta
class Artista : public Pessoa {             // Herança pública
private:
    int camarimId;                          // Atributo específico de Artista
public:
    string exibir() const override;         // Implementa o método abstrato
};
```

**Benefício:** Reutilização de código e polimorfismo de tipos relacionados.

#### **Hierarquia 2: Sistema de Exceções (3 Níveis de Profundidade!)**
- **1º Nível (Base):** `ExcecaoBase` (herda de `std::exception`)
- **2º Nível (Específicas):** `EstoqueException`, `ValidacaoException`, `ArtistaException`, etc.
- **3º Nível (Especializadas):** `EstoqueInsuficienteException` (herda de `EstoqueException`)
- **Arquivo:** `header/excecoes.h`

```cpp
// 1º Nível - Base de todas as exceções customizadas
class ExcecaoBase : public exception {
protected:
    string mensagem;                             // Mensagem de erro encapsulada
public:
    virtual const char* what() const noexcept override;  // Polimorfismo
};

// 2º Nível - Exceções de categorias específicas
class EstoqueException : public ExcecaoBase { };

// 3º Nível - Exceções altamente especializadas (HIERARQUIA DE 3 NÍVEIS!)
class EstoqueInsuficienteException : public EstoqueException { };
```

**Benefício:** Hierarquia de 3 níveis permite tratamento de erros em diferentes níveis de granularidade (catch genérico ou específico).

---

### 3️⃣ **Polimorfismo (Comportamento Dinâmico em Tempo de Execução)**

O polimorfismo permite que **objetos de classes derivadas sejam tratados como objetos da classe base**, com o método correto sendo chamado dinamicamente. Implementado em múltiplos contextos no sistema.

#### **Polimorfismo 1: Método Virtual `exibir()`**
- **Classe Base:** `Pessoa::exibir()` (método virtual puro - interface obrigatória)
- **Classe Derivada:** `Artista::exibir()` (implementação concreta)
- **Localização:** `header/pessoa.h`, `src/artista.cpp` (linhas ~50-60)

```cpp
// Uso prático: Ponteiro de classe base aponta para objeto derivado
Pessoa* p = new Artista(1, "João Silva", 10);
cout << p->exibir();  // Chama Artista::exibir() - POLIMORFISMO DINÂMICO!
                      // O método correto é resolvido em tempo de execução (late binding)
```

**Benefício:** Flexibilidade para tratar diferentes tipos de Pessoa de forma uniforme.

#### **Polimorfismo 2: Método Virtual `what()` nas Exceções**
- **Classe Base:** `ExcecaoBase::what()` (herdado de `std::exception`)
- **Classes Derivadas:** Todas as 8 exceções customizadas sobrescrevem `what()`
- **Localização:** `header/excecoes.h`, implementações em diversos arquivos `.cpp`

```cpp
try {
    throw EstoqueInsuficienteException("Quantidade insuficiente no estoque");
} catch (const exception& e) {  // Captura polimórfica (tipo base std::exception)
    cout << e.what();           // Chama what() da classe derivada correta
}                               // Permite catch genérico para qualquer exceção
```

**Benefício:** Sistema de exceções hierárquico com tratamento flexível (específico ou genérico).

---

### 4️⃣ **Encapsulamento (Proteção e Controle de Acesso aos Dados)**

**Todos os atributos** das classes são declarados como `private` ou `protected`, garantindo que o acesso seja **controlado exclusivamente por métodos públicos** (getters/setters), permitindo validações e mantendo a integridade dos dados.

#### **📋 Exemplos de Encapsulamento por Classe:**

| Arquivo | Classe | Atributos Encapsulados | Nível de Acesso |
|---------|--------|------------------------|-----------------|
| `pessoa.h` | Pessoa | `int id; string nome;` | `protected` (acessível em classes derivadas) |
| `artista.h` | Artista | `int camarimId;` | `private` (acesso apenas via métodos) |
| `item.h` | Item | `int id; string nome; double preco;` | `private` |
| `estoque.h` | Estoque | `map<int, ItemEstoque> itens;` | `private` |
| `camarim.h` | Camarim | `int id; string nome; int artistaId;` | `private` |

#### **🛡️ Validações nos Setters (Garantia de Integridade):**
```cpp
// Exemplo em item.cpp - Setter com validação
void Item::setPreco(double novoPreco) {
    if (novoPreco <= 0) {  // Validação: preço deve ser positivo
        throw ValidacaoException("Preço deve ser maior que zero");
    }
    preco = novoPreco;  // Atualiza apenas se a validação passar
}
```

**Benefício:** Impossibilita a criação de objetos em estados inválidos e centraliza a lógica de validação.

---

### 5️⃣ **Tratamento de Exceções (Sistema Robusto de Erros)**

O sistema implementa **9 classes de exceções customizadas** organizadas hierarquicamente, permitindo tratamento de erros granular e específico para cada contexto.

#### **📦 Hierarquia Completa das Exceções:**
Todas definidas em `header/excecoes.h`:

```
ExcecaoBase (1º nível - base)
├── ValidacaoException          (erros de validação de dados)
├── ArtistaException            (erros relacionados a artistas)
├── ItemException               (erros relacionados a itens)
├── EstoqueException            (erros gerais de estoque)
│   └── EstoqueInsuficienteException  (3º NÍVEL - estoque insuficiente)
├── CamarimException            (erros relacionados a camarins)
├── PedidoException             (erros relacionados a pedidos)
└── ListaComprasException       (erros relacionados a listas de compras)
```
**Total: 9 classes** (1 base + 8 derivadas, incluindo 1 de 3º nível)

#### **🔧 Exemplo Prático de Uso:**

```cpp
// LANÇAMENTO - Em estoque.cpp: validação que lança exceção específica
void Estoque::retirarItem(int idItem, int quantidade) {
    if (quantidade > itens[idItem].quantidade) {
        throw EstoqueInsuficienteException("Quantidade solicitada excede o estoque disponível");
    }
    itens[idItem].quantidade -= quantidade;  // Operação segura
}

// TRATAMENTO - Em main.cpp: captura hierárquica (do mais específico ao mais genérico)
try {
    estoque.retirarItem(1, 100);
} 
catch (const EstoqueInsuficienteException& e) {  // Trata erro específico
    cerr << "⚠️ Estoque insuficiente: " << e.what() << endl;
} 
catch (const EstoqueException& e) {              // Trata categoria de erros
    cerr << "❌ Erro de estoque: " << e.what() << endl;
}
catch (const ExcecaoBase& e) {                   // Trata qualquer exceção customizada
    cerr << "❌ Erro no sistema: " << e.what() << endl;
}
```

**Benefício:** Tratamento de erros em diferentes níveis de especificidade, melhorando a robustez e manutenibilidade.

---

### 6️⃣ **CRUD Completo (6 Entidades com Operações Completas)**

O sistema implementa **Create, Read, Update, Delete** para 6 entidades principais, permitindo gerenciamento completo dos dados.

| Entidade | Gerenciador | Arquivo Implementação | Create | Read | Update | Delete |
|----------|------------|----------------------|--------|------|--------|--------|
| **Artista** | GerenciadorArtistas | `src/artista.cpp` |  adicionar() |  buscarPorId() |  setters |  remover() |
| **Item** | GerenciadorItens | `src/item.cpp` |  adicionar() |  buscarPorId() |  setters |  remover() |
| **Estoque** | Estoque | `src/estoque.cpp` |  adicionarItem() |  listarItens() |  atualizarQtd() |  removerItem() |
| **Camarim** | GerenciadorCamarins | `src/camarim.cpp` |  adicionar() |  buscarPorId() |  setters |  remover() |
| **Pedido** | GerenciadorPedidos | `src/pedido.cpp` |  adicionar() |  buscarPorId() |  atenderPedido() |  remover() |
| **ListaCompras** | GerenciadorListaCompras | `src/listacompras.cpp` |  adicionar() |  buscarPorId() |  setters |  remover() |

#### **💡 Exemplo de Fluxo CRUD:**
```cpp
// CREATE - Adiciona novo artista ao sistema
artistas.adicionar(make_shared<Artista>(1, "João Silva", 10));

// READ - Busca artista por ID
auto artista = artistas.buscarPorId(1);
cout << artista->getNome();  // Acesso encapsulado via getter

// UPDATE - Atualiza dados do artista
artista->setNome("João Pedro Silva");      // Validação automática no setter
artista->setCamarimId(15);

// DELETE - Remove artista do sistema
artistas.remover(1);  // Remove permanentemente
```

**Benefício:** Gerenciamento completo do ciclo de vida dos dados com operações padronizadas.

---

### 📂 **Estrutura de Diretórios**


```
.
├── bin/         # Executáveis gerados após a compilação
├── header/      # Arquivos de cabeçalho (.h) - 100% comentados
├── src/         # Implementação das classes (.cpp) - 100% comentados
├── .gitignore   # Arquivos/diretórios ignorados pelo Git
├── makefile     # Automação da compilação e execução
├── diagrama.md  # Diagrama UML das classes
└── README.md    # Este arquivo
```

---

### 🛠️ **Implementação das Operações do Sistema**

#### 📌 **Arquivos de Interface (header/):**
Define a **estrutura de classes** e suas **interfaces públicas** (contratos):

- **`pessoa.h`**: Classe base abstrata com método virtual puro `exibir()`
- **`artista.h`**: Classe Artista (herda de Pessoa) + GerenciadorArtistas
- **`item.h`**: Classe Item (produtos do sistema) + GerenciadorItens
- **`estoque.h`**: Classe Estoque (gerencia inventário com map de itens)
- **`camarim.h`**: Classe Camarim (atribuído a artistas) + GerenciadorCamarins
- **`pedido.h`**: Classe Pedido (solicitações de itens) + GerenciadorPedidos
- **`listacompras.h`**: Classe ListaCompras (compras necessárias) + GerenciadorListaCompras
- **`excecoes.h`**: Hierarquia de 9 exceções personalizadas (3 níveis de profundidade)

#### 📌 **Arquivos de Implementação (src/):**
Contém a **lógica de negócio**, **validações** e **operações CRUD**:

- **`pessoa.cpp`**: Implementação da classe base (destrutor, operator<<)
- **`artista.cpp`**: Gerenciamento completo de artistas (CRUD + validações)
- **`item.cpp`**: Operações com produtos e catálogo
- **`estoque.cpp`**: Controle de inventário (entrada/saída com verificações de quantidade)
- **`camarim.cpp`**: Gerenciamento de camarins e associação com artistas
- **`pedido.cpp`**: Sistema de pedidos com controle de status (atendido/pendente)
- **`listacompras.cpp`**: Listas de compras com cálculo de valores totais
- **`main.cpp`**: Interface de usuário (menus interativos) e orquestração do sistema

---

### 📦 **Como Compilar e Executar**

O projeto utiliza **Makefile** (Linux) para automação da compilação e execução.

#### 🐧 **Comandos do Makefile:**

| Comando | Descrição |
|---------|-----------|
| `make` ou `make all` | Compila todo o projeto (gera executável em `bin/main`) |
| `make run` | Compila (se necessário) e executa o programa |
| `make clean` | Remove arquivos objeto (`.o`, `.d`) e executáveis |

#### 📌 **Fluxo de Trabalho Recomendado:**

```bash
# 1. Limpar compilações anteriores (opcional, mas recomendado)
make clean

# 2. Compilar o projeto
make

# 3. Executar o programa
make run

# OU executar diretamente:
./bin/main
```

#### ⚙️ **Requisitos de Sistema:**
- **Compilador:** g++ com suporte a **C++11** ou superior
- **Sistema Operacional:** Linux | Windows
- **Dependências:** Nenhuma biblioteca externa necessária (apenas STL padrão)

---

### 🌟 **Recursos Adicionais Implementados**

1. **📝 Documentação Completa do Código:**
   - Todos os arquivos `.h` e `.cpp` possuem **comentários linha por linha**
   - Explicações detalhadas dos **conceitos de POO** aplicados
   - Documentação de **decisões de design** e arquitetura

2. **🔢 Suporte a Formato Brasileiro (vírgula decimal):**
   - Função `lerDouble()` implementada em `main.cpp` (linhas 65-93)
   - Aceita **vírgula** como separador decimal: `4,50` → `R$ 4.50`
   - Também aceita **ponto**: `1500.99` → `R$ 1500.99`
   - Conversão **automática e transparente** para o usuário

3. **🏗️ Arquitetura Modular e Robusta:**
   - Padrão **CRUD** consistente em todas as entidades
   - **Separação clara de responsabilidades** (classes gerenciadoras)
   - **Validações centralizadas** nos setters e métodos de negócio
   - Sistema de **exceções hierárquico** para tratamento de erros granular

---

### 📊 **Estrutura Hierárquica do Código**

#### **Hierarquia de Herança - Modelo de Domínio:**
```
Pessoa (classe base abstrata)
└── Artista (classe derivada concreta)
```

#### **Hierarquia de Herança - Sistema de Exceções (3 Níveis!):**
```
ExcecaoBase (1º nível - base customizada que herda de std::exception)
├── ValidacaoException (2º nível - validações de entrada)
├── ArtistaException (2º nível - erros de artistas)
├── ItemException (2º nível - erros de itens)
├── EstoqueException (2º nível - erros gerais de estoque)
│   └── EstoqueInsuficienteException (3º NÍVEL - caso específico de estoque!)
├── CamarimException (2º nível - erros de camarins)
├── PedidoException (2º nível - erros de pedidos)
└── ListaComprasException (2º nível - erros de listas)
```

---

### 🎯 **Conceitos de POO Implementados**

| Conceito | Implementação | Localização |
|----------|--------------|-------------|
| **1. Encapsulamento** | Atributos `private`/`protected` com getters/setters validados | Todas as classes em `header/` |
| **2. Herança** | Pessoa → Artista, ExcecaoBase → 8 Exceções | `pessoa.h`, `artista.h`, `excecoes.h` |
| **3. Herança Multinível** | EstoqueInsuficienteException (3 níveis) | `excecoes.h` |
| **4. Polimorfismo** | Métodos virtuais `exibir()` e `what()` sobrescritos | `pessoa.h/cpp`, `artista.cpp`, exceções |
| **5. Abstração** | Classe base abstrata (Pessoa com virtual puro) | `pessoa.h` |
| **6. Sobrecarga de Operadores** | `operator<<` em 7 classes | Todos os arquivos `.cpp` |
| **7. Tratamento de Exceções** | Hierarquia de 9 exceções customizadas | `excecoes.h` + validações em `.cpp` |

