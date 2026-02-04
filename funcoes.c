#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*  ESTRUTURAS DE DADOS */

typedef struct Cliente {
    char cpf[15];
    char nome[100];
    char email[100];
    char telefone[20];
    char dataNascimento[15];
    struct Cliente *proximo;
} Cliente;

typedef struct Produto {
    int codigo;
    char nome[100];
    float preco;
    int quantidade;
    struct Produto *proximo; 
    struct Produto *prox;    
} Produto;

typedef struct Compra {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    struct Compra *proximo;
} Compra;

/*  PROTÓTIPOS DAS FUNÇÕES */

// Utilitários
void limpar_buffer_entrada();
void ler_string(char *buffer, int tamanho);
void pausar_tela();
int validar_cpf(const char *cpf);

// Clientes
Cliente* cadastrar_cliente(Cliente *listaClientes);
void listar_clientes(Cliente *listaClientes);
Cliente* buscar_cliente(Cliente *listaClientes, const char *cpf);
void editar_cliente(Cliente *listaClientes);
Cliente* remover_cliente(Cliente *listaClientes);
void liberar_clientes(Cliente *listaClientes);

// Produtos
Produto* cadastrarProduto(Produto *lista);
void imprimirProdutos(Produto *lista);
Produto* buscarProduto(Produto *lista, int codigo);
int codigoExiste(Produto *lista, int codigo);
Produto* removerProduto(Produto *lista, int codigo);

// Carrinho
void adicionar_carrinho(Compra **topo);
void listar_carrinho(Compra *topo);
void remover_carrinho(Compra **topo);
void limpar_carrinho(Compra **topo);

// Menus
void menu_clientes(Cliente **listaClientes);
void menu_produtos(Produto **listaProdutos);
void menu_carrinho(Compra **carrinho);

/* IMPLEMENTAÇÃO DAS FUNÇÕES UTILITÁRIAS */

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ler_string(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

void pausar_tela() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

int validar_cpf(const char *cpf) {
    int cont = 0;
    while (cpf[cont] != '\0') {
        if (!isdigit(cpf[cont])) return 0;
        cont++;
    }
    return (cont == 11);
}

/*  GESTÃO DE CLIENTES */

Cliente* buscar_cliente(Cliente *listaClientes, const char *cpf) {
    Cliente *atual = listaClientes;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

Cliente* cadastrar_cliente(Cliente *listaClientes) {
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (!novo) return listaClientes;

    printf("\n--- CADASTRAR CLIENTE ---\n");
    do {
        printf("CPF (apenas 11 digitos): ");
        ler_string(novo->cpf, sizeof(novo->cpf));
        if (!validar_cpf(novo->cpf)) printf("Erro: CPF deve conter exatamente 11 numeros.\n");
    } while (!validar_cpf(novo->cpf));

    printf("Nome: ");
    ler_string(novo->nome, sizeof(novo->nome));
    printf("Email: ");
    ler_string(novo->email, sizeof(novo->email));
    printf("Telefone: ");
    ler_string(novo->telefone, sizeof(novo->telefone));
    printf("Data de Nascimento: ");
    ler_string(novo->dataNascimento, sizeof(novo->dataNascimento));

    novo->proximo = listaClientes;
    printf("\nCliente cadastrado com sucesso!\n");
    pausar_tela();
    return novo;
}

void listar_clientes(Cliente *listaClientes) {
    Cliente *atual = listaClientes;
    if (!atual) {
        printf("\nNenhum cliente cadastrado.\n");
    } else {
        printf("\n--- LISTA DE CLIENTES ---\n");
        while (atual) {
            printf("CPF: %s | Nome: %s | Email: %s\n", atual->cpf, atual->nome, atual->email);
            atual = atual->proximo;
        }
    }
    pausar_tela();
}

void editar_cliente(Cliente *listaClientes) {
    char cpf[15];
    printf("\nDigite o CPF para editar: ");
    ler_string(cpf, sizeof(cpf));
    Cliente *c = buscar_cliente(listaClientes, cpf);
    if (c) {
        printf("Novo Nome: "); ler_string(c->nome, sizeof(c->nome));
        printf("Novo Email: "); ler_string(c->email, sizeof(c->email));
        printf("Cliente atualizado com sucesso!\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }
    pausar_tela();
}

Cliente* remover_cliente(Cliente *listaClientes) {
    char cpf[15];
    printf("\nDigite o CPF para remover: ");
    ler_string(cpf, sizeof(cpf));
    Cliente *atual = listaClientes, *ant = NULL;
    while (atual && strcmp(atual->cpf, cpf) != 0) {
        ant = atual;
        atual = atual->proximo;
    }
    if (atual) {
        if (!ant) listaClientes = atual->proximo;
        else ant->proximo = atual->proximo;
        free(atual);
        printf("Cliente removido com sucesso!\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }
    pausar_tela();
    return listaClientes;
}

void liberar_clientes(Cliente *listaClientes) {
    while (listaClientes) {
        Cliente *prox = listaClientes->proximo;
        free(listaClientes);
        listaClientes = prox;
    }
}

/*  GESTÃO DE PRODUTOS */

int codigoExiste(Produto *lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo) return 1;
        lista = lista->prox;
    }
    return 0;
}

Produto* cadastrarProduto(Produto *lista) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));

    printf("\nNome do produto: ");
    ler_string(novo->nome, sizeof(novo->nome));

    do {
        printf("Codigo: ");
        scanf("%d", &novo->codigo);
        if (codigoExiste(lista, novo->codigo))
            printf("Codigo ja existe! Tente outro.\n");
    } while (codigoExiste(lista, novo->codigo));

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);

    limpar_buffer_entrada();

    novo->prox = lista;
    novo->proximo = NULL;

    printf("Produto cadastrado!\n");
    return novo;
}


void imprimirProdutos(Produto *lista) {
    if (!lista) printf("\nNenhum produto em estoque.\n");
    else {
        printf("\n--- ESTOQUE DE PRODUTOS ---\n");
        while (lista) {
            printf("Cod: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n", 
                   lista->codigo, lista->nome, lista->preco, lista->quantidade);
            lista = lista->prox;
        }
    }
    pausar_tela();
}

Produto* buscarProduto(Produto *lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo) return lista;
        lista = lista->prox;
    }
    return NULL;
}

Produto* removerProduto(Produto *lista, int codigo) {
    Produto *atual = lista, *ant = NULL;
    while (atual && atual->codigo != codigo) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual) {
        if (!ant) lista = atual->prox;
        else ant->prox = atual->prox;
        free(atual);
        printf("\nProduto removido com sucesso!\n");
    } else printf("\nProduto nao encontrado.\n");
    return lista;
}

/*  GESTÃO DO CARRINHO */

void adicionar_carrinho(Compra **topo) {
    Compra *novo = malloc(sizeof(Compra));

    printf("\nNome do item: ");
    ler_string(novo->nome, sizeof(novo->nome));

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    limpar_buffer_entrada();

    novo->proximo = *topo;
    *topo = novo;

    printf("Item adicionado ao carrinho!\n");
}

void listar_carrinho(Compra *topo) {
    float total = 0;

    if (!topo) {
        printf("\nCarrinho vazio.\n");
    } else {
        printf("\n--- CARRINHO ---\n");
        while (topo) {
            float sub = topo->preco * topo->quantidade;
            printf("%s | %d x %.2f = %.2f\n",
                   topo->nome, topo->quantidade, topo->preco, sub);
            total += sub;
            topo = topo->proximo;
        }
        printf("TOTAL: R$ %.2f\n", total);
    }
    pausar_tela();
}

void remover_carrinho(Compra **topo) {
    char nome[100];

    printf("\nDigite o nome do item para remover do carrinho: ");
    ler_string(nome, sizeof(nome));

    Compra *atual = *topo;
    Compra *ant = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        ant = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (ant == NULL) {
            *topo = atual->proximo;
        } else {
            ant->proximo = atual->proximo;
        }
        free(atual);
        printf("Item removido do carrinho!\n");
    } else {
        printf("Item nao encontrado no carrinho.\n");
    }

    pausar_tela();
}

void limpar_carrinho(Compra **topo) {
    while (*topo != NULL) {
        Compra *prox = (*topo)->proximo;
        free(*topo);
        *topo = prox;
    }
    *topo = NULL;
}