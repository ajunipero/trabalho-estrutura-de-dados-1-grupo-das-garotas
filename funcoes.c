// funcoes.c
#include "funcoes.h"

void adicionar(Produto **topo) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    if (novo == NULL) return;

    printf("Nome do produto: ");
    scanf(" %[^\n]", novo->nome);
    printf("Preco: ");
    scanf("%f", &novo->preco);
    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    
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

    if (anterior == NULL) {
        *topo = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
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

//funcoes.c gerenciamento de produtos 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Produto* cadastrarProduto(Produto *lista) {
   Produto *novo = malloc(sizeof(Produto)); 

   printf("Nome: "); 
   scanf(" %[^\n]", novo->nome);

   if (strcmp(novo->nome, "fim") == 0) {
    free(novo);
    return lista;
   }

int existe;

do {
    printf("Codigo: ");
    scanf("%d", &novo->codigo);

    existe = codigoExiste(lista, novo->codigo);

    if (existe) {
        printf("Codigo ja cadastrado! Digite outro.\n");
    }

} while (existe);



   printf("Preco: "); 
   scanf("%f", &novo->preco);

   printf("Quantidade: "); 
   scanf("%d", &novo->quantidade);

   novo->prox = lista; 
   return novo;

}

void imprimirProdutos(Produto *lista) {
    Produto *aux = lista;

    if (aux == NULL) {
        printf("\nNenhum produto cadastrado.\n");
    return;

    }

    printf("\n--- PRODUTOS CADASTRADOS ---\n");

    while (aux != NULL) {
        printf("Codigo: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome);
        printf("Preco: %.2f\n", aux->preco);
        printf("Quantidade: %d\n\n", aux->quantidade);

        aux = aux->prox;
    }

}

Produto* buscarProduto(Produto *lista, int codigo) {
    Produto *aux = lista;

    while (aux != NULL) {
        if (aux->codigo == codigo) {
            return aux;   
        }
        aux = aux->prox;
    }

    return NULL; 
}

int codigoExiste(Produto *lista, int codigo) {
    Produto *aux = lista;

    while (aux != NULL) {
        if (aux->codigo == codigo) {
            return 1; 
        }
        aux = aux->prox;
    }

    return 0; 
}

Produto* removerProduto(Produto *lista, int codigo) {
    Produto *atual = lista;
    Produto *anterior = NULL;

    if (lista == NULL) {
        printf("\nLista vazia.\n");
        return lista;
    }

    if (atual->codigo == codigo) {
        lista = atual->prox;
        free(atual);
        printf("\nProduto removido com sucesso!\n");
        return lista;
    }

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nProduto nao encontrado.\n");
        return lista;
    }

    anterior->prox = atual->prox;
    free(atual);

    printf("\nProduto removido com sucesso!\n");
    return lista;
}
