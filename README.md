# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** LP1
- **Professor:** Prof. Jerffeson Gomes Dutra

  
## Atividade LP1 - Desenvolver uma aplicação funcional, utilizando os principais conceitos da programação orientada a objetos (POO). A aplicação deve conter um conjunto mínimo de funcionalidades que envolvam cadastro, consulta, alteração e remoção de dados (CRUD).

### ✅ **Requisitos Mínimos**
1. **8 Classes ✅**
   - Pessoa (classe base abstrata)
   - Usuario (herda de Pessoa)
   - Artista (herda de Pessoa)
   - Item
   - Estoque
   - Camarim
   - Pedido
   - ListaCompras
   - **+7 Classes Gerenciadoras** (GerenciadorArtistas, GerenciadorItens, etc.)
   - **+9 Classes de Exceção** (ExcecaoBase, ValidacaoException, etc.)

2. **Encapsulamento de todas as entidades ✅**
   - Todos os atributos são privados/protected
   - Acesso via getters e setters com validação
   - **Código 100% comentado** explicando cada conceito de POO

3. **2 Heranças ✅**
   - Artista herda de Pessoa (com polimorfismo)
   - **Hierarquia de exceções:** ExcecaoBase → 8 exceções derivadas
   - **Herança de 3 níveis:** EstoqueInsuficienteException → EstoqueException → ExcecaoBase

4. **Classes Bases Diferentes ✅**
   - Pessoa (base para Artista)
   - ExcecaoBase (base para todas as exceções personalizadas)

5. **Min 2 Polimorfismos ✅**
   - Método virtual puro `exibir()` em Pessoa
   - Sobrescrito em Artista
   - Método virtual `what()` nas exceções

6. **Criar, ler, atualizar e remover registros de 6 entidades ✅**
   - Artista: CRUD completo
   - Item: CRUD completo
   - Estoque: CRUD completo
   - Camarim: CRUD completo
   - Pedido: CRUD completo
   - ListaCompras: CRUD completo

7. **Implementar a sobrecarga do operador << ✅**
   - Pessoa (e suas derivadas)
   - Item
   - Estoque
   - Camarim
   - Pedido
   - ListaCompras

8. **Tratamento de exceções ✅**
   - Try-catch em todas as operações críticas
   - Validações lançam exceções específicas

9. **Exceções personalizadas ✅**
   - 9 classes de exceções customizadas
   - Hierarquia de herança de exceções (3 níveis)

10. **Tratar validação de dados com exceções ✅**
    - Validações em setters
    - Verificações em operações de negócio
    - Tratamento robusto de erros

11. **Diagrama de Classes – UML ✅**
    - Arquivo diagrama.md com todas as relações

12. **Funcionamento do Sistema ✅**
    - Interação com usuário via menus
    - Sistema modular e extensível
    - **Suporte a entrada decimal com vírgula** (formato brasileiro)


### ✅ **Observações**
1. Todas as heranças, implementações e polimorfismo devem ser de classes próprias. Herança e implementação de classes oriundas de bibliotecas, frameworks e afins não serão consideradas.


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
Define a estrutura de todas as classes e suas operações públicas:

- **`pessoa.h`**: Classe base abstrata com polimorfismo ✅ **100% comentado**
- **`artista.h`**: Classe Artista (herda de Pessoa) + GerenciadorArtistas ✅ **100% comentado**
- **`item.h`**: Classe Item + GerenciadorItens ✅ **100% comentado**
- **`estoque.h`**: Classe Estoque para gerenciar inventário ✅ **100% comentado**
- **`camarim.h`**: Classe Camarim + GerenciadorCamarins ✅ **100% comentado**
- **`pedido.h`**: Classe Pedido + GerenciadorPedidos ✅ **100% comentado**
- **`listacompras.h`**: Classe ListaCompras + GerenciadorListaCompras ✅ **100% comentado**
- **`excecoes.h`**: Hierarquia de exceções personalizadas ✅ **100% comentado**

#### 📌 **Arquivo de Implementação (src/):**
Contém a lógica completa de todas as operações CRUD e validações:

- **`pessoa.cpp`**: Implementação da classe base ✅ **100% comentado**
- **`artista.cpp`**: Gerenciamento de artistas e camarins ✅ **100% comentado**
- **`item.cpp`**: Operações com itens/produtos ✅ **100% comentado**
- **`estoque.cpp`**: Controle de estoque com validações ✅ **100% comentado**
- **`camarim.cpp`**: Gerenciamento de camarins e seus itens ✅ **100% comentado**
- **`pedido.cpp`**: Sistema de pedidos ✅ **100% comentado**
- **`listacompras.cpp`**: Lista de compras com cálculo de totais ✅ **100% comentado**
- **`main.cpp`**: Interface do usuário e integração (parcialmente comentado)

---

### 📦 **Como Compilar e Executar**

O projeto pode ser compilado usando **make** (Linux) ou scripts PowerShell (Windows).

#### 🐧 **Linux (Makefile):**

| Comando               | Descrição                             |
|-----------------------|---------------------------------------|
| `make` ou `make all`  | Compila o programa.                   |
| `make run`            | Executa o programa (`bin/main`).      |
| `make clean`          | Remove arquivos objeto e executáveis. |

#### 📌 **Exemplos de Uso:**

```bash
# Linux
make clean    # Limpar compilações anteriores
make          # Compilar tudo
make run      # Executar programa

# Windows PowerShell
.\compilar.ps1  # Compilar e executar
```

#### ⚙️ **Requisitos:**
- **Compilador:** g++ com suporte a C++
- **Sistema:** Windows e Linux

---

### 🌟 **Recursos Adicionais Implementados**

1. **📝 Código 100% Documentado:**
   - Todos os arquivos `.h` e `.cpp` possuem comentários linha por linha
   - Explicações detalhadas de conceitos de POO
   - Documentação de padrões de projeto utilizados

2. **🔢 Suporte a Formato Monetário com vírgula:**
   - Função `lerDouble()` aceita vírgula como separador decimal
   - Exemplos: `4,50` → `R$ 4.50` | `1500,99` → `R$ 1500.99`
   - Conversão automática e transparente

4. **🏗️ Arquitetura Robusta:**
   - Padrão CRUD para todas as entidades
   - Separação de responsabilidades
   - Validações centralizadas

---

### 📊 **Estrutura do Código**

```
Pessoa (classe base abstrata)
└── Artista (herda de Pessoa)

ExcecaoBase (classe base de exceções)
├── ValidacaoException
├── ArtistaException
├── ItemException
├── EstoqueException
│   └── EstoqueInsuficienteException (3 níveis de herança!)
├── CamarimException
├── PedidoException
└── ListaComprasException
```

### 🎯 **Conceitos de POO Implementados:**

1. **Encapsulamento**: Atributos privados com getters/setters validados
2. **Herança**: Pessoa → Artista, ExcecaoBase → 8 Exceções
3. **Herança Múltipla de Níveis**: EstoqueInsuficienteException (3 níveis)
4. **Polimorfismo**: Métodos virtuais sobrescritos (`exibir()`, `what()`)
5. **Abstração**: Classes base abstratas (Pessoa com método virtual puro)
6. **Sobrecarga de Operadores**: `<<` para todas as classes principais
7. **Tratamento de Exceções**: Sistema robusto com hierarquia de exceções

