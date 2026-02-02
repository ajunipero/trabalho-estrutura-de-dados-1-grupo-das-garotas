#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da lista
typedef struct Produto {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    struct Produto *proximo;
} Produto;

// Protótipos das funções (Passagem por parâmetros)
void adicionar(Produto **topo);
void listar(Produto *topo);
void remover(Produto **topo);
void limparCarrinho(Produto **topo);

int main() {
    Produto *carrinho = NULL; // Variável local (proibido global)
    int opcao;

    do {
        printf("\n--- MENU CARRINHO ---");
        printf("\n1. Adicionar Produto");
        printf("\n2. Listar Carrinho");
        printf("\n3. Remover Produto");
        printf("\n0. Sair e Finalizar");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: adicionar(&carrinho); break;
            case 2: listar(carrinho); break;
            case 3: remover(&carrinho); break;
            case 0: limparCarrinho(&carrinho); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

void adicionar(Produto **topo) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    if (novo == NULL) return;

    printf("Nome do produto: ");
    scanf(" %[^\n]", novo->nome);
    printf("Preco: ");
    scanf("%f", &novo->preco);
    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    
    // Inserção no início (mais simples em lista encadeada)
    novo->proximo = *topo;
    *topo = novo;
    printf("Produto adicionado com sucesso!\n");
}

void listar(Produto *topo) {
    if (topo == NULL) {
        printf("\nCarrinho vazio!\n");
        return;
    }

    float totalGeral = 0;
    int totalItens = 0;
    Produto *atual = topo;

    printf("\n--- ITENS NO CARRINHO --- \n");
    while (atual != NULL) {
        float subtotal = atual->preco * atual->quantidade;
        printf("Prod: %s | Qtd: %d | Preco Un: %.2f | Subtotal: %.2f\n", 
                atual->nome, atual->quantidade, atual->preco, subtotal);
        
        totalGeral += subtotal;
        totalItens += atual->quantidade;
        atual = atual->proximo;
    }
    printf("--------------------------");
    printf("\nTOTAL: R$ %.2f | ITENS: %d\n", totalGeral, totalItens);
}

void remover(Produto **topo) {
    if (*topo == NULL) return;

    char nomeRemover[50];
    printf("Digite o nome exato do produto para remover: ");
    scanf(" %[^\n]", nomeRemover);

    Produto *atual = *topo;
    Produto *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nomeRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado!\n");
        return;
    }

    if (anterior == NULL) { // Remove o primeiro da lista
        *topo = atual->proximo;
    } else { // Remove do meio ou fim
        anterior->proximo = atual->proximo;
    }

    free(atual); // Importante: Liberação de memória!
    printf("Produto removido!\n");
}

void limparCarrinho(Produto **topo) {
    Produto *atual = *topo;
    while (atual != NULL) {
        Produto *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
    printf("Memoria liberada. Saindo...\n");
}
