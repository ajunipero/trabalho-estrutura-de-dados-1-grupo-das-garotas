#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ================= ESTRUTURAS ================= */

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
    struct Produto *prox;
} Produto;

typedef struct Compra {
    char nome[50];
    float preco;
    int quantidade;
    struct Compra *proximo;
} Compra;

/* ================= UTILITÁRIOS ================= */

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ler_string(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void pausar_tela() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

int validar_cpf(const char *cpf) {
    int i;
    if (strlen(cpf) != 11) return 0;
    for (i = 0; i < 11; i++)
        if (!isdigit(cpf[i])) return 0;
    return 1;
}

/* ================= CLIENTES ================= */

Cliente* buscar_cliente(Cliente *lista, const char *cpf) {
    while (lista) {
        if (strcmp(lista->cpf, cpf) == 0)
            return lista;
        lista = lista->proximo;
    }
    return NULL;
}

Cliente* cadastrar_cliente(Cliente *lista) {
    Cliente *novo = malloc(sizeof(Cliente));
    if (!novo) return lista;

    printf("\n--- CADASTRAR CLIENTE ---\n");

    do {
        printf("CPF (11 digitos): ");
        ler_string(novo->cpf, sizeof(novo->cpf));
        if (!validar_cpf(novo->cpf))
            printf("CPF invalido!\n");
    } while (!validar_cpf(novo->cpf));

    printf("Nome: ");
    ler_string(novo->nome, sizeof(novo->nome));

    printf("Email: ");
    ler_string(novo->email, sizeof(novo->email));

    printf("Telefone: ");
    ler_string(novo->telefone, sizeof(novo->telefone));

    printf("Data de Nascimento: ");
    ler_string(novo->dataNascimento, sizeof(novo->dataNascimento));

    novo->proximo = lista;

    printf("\nCliente cadastrado com sucesso!\n");
    pausar_tela();
    return novo;
}

void listar_clientes(Cliente *lista) {
    if (!lista) {
        printf("\nNenhum cliente cadastrado.\n");
    } else {
        printf("\n--- LISTA DE CLIENTES ---\n");
        while (lista) {
            printf(
                "CPF: %s | Nome: %s | Email: %s | Telefone: %s | Data Nasc.: %s\n",
                lista->cpf,
                lista->nome,
                lista->email,
                lista->telefone,
                lista->dataNascimento
            );
            lista = lista->proximo;
        }
    }
    pausar_tela();
}

void editar_cliente(Cliente *lista) {
    char cpf[15];
    printf("\nDigite o CPF para editar: ");
    ler_string(cpf, sizeof(cpf));

    Cliente *c = buscar_cliente(lista, cpf);
    if (!c) {
        printf("Cliente nao encontrado.\n");
        pausar_tela();
        return;
    }

    printf("Novo Nome: ");
    ler_string(c->nome, sizeof(c->nome));

    printf("Novo Email: ");
    ler_string(c->email, sizeof(c->email));

    printf("Novo Telefone: ");
    ler_string(c->telefone, sizeof(c->telefone));

    printf("Nova Data de Nascimento: ");
    ler_string(c->dataNascimento, sizeof(c->dataNascimento));

    printf("\nCliente atualizado com sucesso!\n");
    pausar_tela();
}

Cliente* remover_cliente(Cliente *lista) {
    char cpf[15];
    printf("\nDigite o CPF para remover: ");
    ler_string(cpf, sizeof(cpf));

    Cliente *atual = lista, *ant = NULL;

    while (atual && strcmp(atual->cpf, cpf) != 0) {
        ant = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Cliente nao encontrado.\n");
    } else {
        if (!ant) lista = atual->proximo;
        else ant->proximo = atual->proximo;
        free(atual);
        printf("Cliente removido com sucesso!\n");
    }

    pausar_tela();
    return lista;
}

void liberar_clientes(Cliente *lista) {
    while (lista) {
        Cliente *prox = lista->proximo;
        free(lista);
        lista = prox;
    }
}

/* ================= PRODUTOS ================= */

int codigoExiste(Produto *lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo) return 1;
        lista = lista->prox;
    }
    return 0;
}

Produto* cadastrarProduto(Produto *lista) {
    Produto *novo = malloc(sizeof(Produto));
    if (!novo) return lista;

    printf("\nNome do produto: ");
    ler_string(novo->nome, sizeof(novo->nome));

    do {
        printf("Codigo: ");
        scanf("%d", &novo->codigo);
        limpar_buffer_entrada();
        if (codigoExiste(lista, novo->codigo))
            printf("Codigo ja existe!\n");
    } while (codigoExiste(lista, novo->codigo));

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    limpar_buffer_entrada();

    novo->prox = lista;

    printf("Produto cadastrado com sucesso!\n");
    return novo;
}

void imprimirProdutos(Produto *lista) {
    if (!lista) {
        printf("\nNenhum produto cadastrado.\n");
    } else {
        printf("\n--- ESTOQUE ---\n");
        while (lista) {
            printf("Cod: %d | Nome: %s | Preco: %.2f | Qtd: %d\n",
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

    if (!atual) {
        printf("Produto nao encontrado.\n");
    } else {
        if (!ant) lista = atual->prox;
        else ant->prox = atual->prox;
        free(atual);
        printf("Produto removido com sucesso!\n");
    }

    return lista;
}

/* ================= CARRINHO ================= */

void adicionar_carrinho(Compra **topo) {
    Compra *novo = malloc(sizeof(Compra));
    if (!novo) return;

    printf("\nNome do produto: ");
    ler_string(novo->nome, sizeof(novo->nome));

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    limpar_buffer_entrada();

    novo->proximo = *topo;
    *topo = novo;

    printf("Produto adicionado ao carrinho!\n");
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
    char nome[50];
    printf("\nNome do item para remover: ");
    ler_string(nome, sizeof(nome));

    Compra *atual = *topo, *ant = NULL;

    while (atual && strcmp(atual->nome, nome) != 0) {
        ant = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Item nao encontrado.\n");
    } else {
        if (!ant) *topo = atual->proximo;
        else ant->proximo = atual->proximo;
        free(atual);
        printf("Item removido!\n");
    }
    pausar_tela();
}

void limpar_carrinho(Compra **topo) {
    while (*topo) {
        Compra *prox = (*topo)->proximo;
        free(*topo);
        *topo = prox;
    }
}