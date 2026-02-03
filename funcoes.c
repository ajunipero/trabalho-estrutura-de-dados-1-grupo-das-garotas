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
void adicionar_carrinho(Produto **topo);
void listar_carrinho(Produto *topo);
void remover_carrinho(Produto **topo);
void limpar_carrinho(Produto **topo);

// Menus
void menu_clientes(Cliente **listaClientes);
void menu_produtos(Produto **listaProdutos);
void menu_carrinho(Produto **carrinho);

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
    printf("\nNome do produto (ou 'fim' para cancelar): ");
    ler_string(novo->nome, sizeof(novo->nome));
    if (strcmp(novo->nome, "fim") == 0) {
        free(novo);
        return lista;
    }
    do {
        printf("Codigo: ");
        scanf("%d", &novo->codigo);
        if (codigoExiste(lista, novo->codigo)) printf("Codigo ja existe! Tente outro.\n");
    } while (codigoExiste(lista, novo->codigo));
    printf("Preco: "); scanf("%f", &novo->preco);
    printf("Quantidade: "); scanf("%d", &novo->quantidade);
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

void adicionar_carrinho(Produto **topo) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    printf("\nNome do item: "); ler_string(novo->nome, sizeof(novo->nome));
    printf("Preco: "); scanf("%f", &novo->preco);
    printf("Quantidade: "); scanf("%d", &novo->quantidade);
    limpar_buffer_entrada();
    novo->proximo = *topo;
    novo->prox = NULL;
    *topo = novo;
    printf("Item adicionado ao carrinho!\n");
}

void listar_carrinho(Produto *topo) {
    float total = 0;
    if (!topo) {
        printf("\nO carrinho esta vazio.\n");
    } else {
        printf("\n--- ITENS NO CARRINHO ---\n");
        while (topo) {
            printf("%s - %d x R$ %.2f (Subtotal: R$ %.2f)\n", 
                   topo->nome, topo->quantidade, topo->preco, (topo->preco * topo->quantidade));
            total += (topo->preco * topo->quantidade);
            topo = topo->proximo;
        }
        printf("--------------------------\n");
        printf("TOTAL DA COMPRA: R$ %.2f\n", total);
    }
    pausar_tela();
}

void remover_carrinho(Produto **topo) {
    char nome[100];
    printf("\nDigite o nome do item para remover do carrinho: "); 
    ler_string(nome, sizeof(nome));
    Produto *atual = *topo, *ant = NULL;
    while (atual && strcmp(atual->nome, nome) != 0) {
        ant = atual;
        atual = atual->proximo;
    }
    if (atual) {
        if (!ant) *topo = atual->proximo;
        else ant->proximo = atual->proximo;
        free(atual);
        printf("Item removido do carrinho!\n");
    } else printf("Item nao encontrado no carrinho.\n");
    pausar_tela();
}

void limpar_carrinho(Produto **topo) {
    while (*topo) {
        Produto *prox = (*topo)->proximo;
        free(*topo);
        *topo = prox;
    }
    *topo = NULL;
}

/*  MENUS DE NAVEGAÇÃO */

void menu_clientes(Cliente **lista) {
    int op;
    do {
        printf("\n--- GERENCIAMENTO DE CLIENTES ---");
        printf("\n1. Cadastrar Cliente");
        printf("\n2. Listar Clientes");
        printf("\n3. Editar Cliente");
        printf("\n4. Remover Cliente");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nEscolha: ");
        if (scanf("%d", &op) != 1) { limpar_buffer_entrada(); continue; }
        limpar_buffer_entrada();
        switch(op) {
            case 1: *lista = cadastrar_cliente(*lista); break;
            case 2: listar_clientes(*lista); break;
            case 3: editar_cliente(*lista); break;
            case 4: *lista = remover_cliente(*lista); break;
        }
    } while(op != 0);
}

void menu_produtos(Produto **lista) {
    int op, cod;
    do {
        printf("\n--- GERENCIAMENTO DE PRODUTOS ---");
        printf("\n1. Cadastrar Produto");
        printf("\n2. Listar Estoque");
        printf("\n3. Remover Produto");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nEscolha: ");
        if (scanf("%d", &op) != 1) { limpar_buffer_entrada(); continue; }
        limpar_buffer_entrada();
        switch(op) {
            case 1: *lista = cadastrarProduto(*lista); break;
            case 2: imprimirProdutos(*lista); break;
            case 3: 
                printf("Digite o codigo do produto: "); 
                scanf("%d", &cod); 
                limpar_buffer_entrada();
                *lista = removerProduto(*lista, cod); 
                pausar_tela();
                break;
        }
    } while(op != 0);
}

void menu_carrinho(Produto **carro) {
    int op;
    do {
        printf("\n--- CARRINHO DE COMPRAS ---");
        printf("\n1. Adicionar Item");
        printf("\n2. Visualizar Carrinho");
        printf("\n3. Remover Item");
        printf("\n0. Finalizar e Sair do Carrinho");
        printf("\nEscolha: ");
        if (scanf("%d", &op) != 1) { limpar_buffer_entrada(); continue; }
        limpar_buffer_entrada();
        switch(op) {
            case 1: adicionar_carrinho(carro); break;
            case 2: listar_carrinho(*carro); break;
            case 3: remover_carrinho(carro); break;
            case 0: limpar_carrinho(carro); printf("Carrinho finalizado.\n"); break;
        }
    } while(op != 0);
}

/* MAIN */

int main() {
    Cliente *lClientes = NULL;
    Produto *lProdutos = NULL;
    Produto *carrinho = NULL;
    int op;

    do {
        printf("\n====================================");
        printf("\n   SISTEMA DE GESTAO INTEGRADA");
        printf("\n====================================");
        printf("\n1. Gerenciamento de Clientes");
        printf("\n2. Gerenciamento de Produtos");
        printf("\n3. Carrinho de Compras");
        printf("\n0. Sair do Sistema");
        printf("\nEscolha uma opcao: ");
        
        if (scanf("%d", &op) != 1) {
            limpar_buffer_entrada();
            printf("Opcao invalida!\n");
            continue;
        }
        limpar_buffer_entrada();

        switch(op) {
            case 1: menu_clientes(&lClientes); break;
            case 2: menu_produtos(&lProdutos); break;
            case 3: menu_carrinho(&carrinho); break;
            case 0: printf("\nEncerrando o sistema...\n"); break;
            default: printf("\nOpcao inexistente!\n"); pausar_tela();
        }
    } while(op != 0);

    liberar_clientes(lClientes);
    
    while (lProdutos) {
        Produto *p = lProdutos->prox;
        free(lProdutos);
        lProdutos = p;
    }

    return 0;
}
