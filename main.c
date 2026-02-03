// main.c
#include "funcoes.c" // Ao incluir o .c, ele traz o .h e a structs.c automaticamente

int main() {
    Produto *carrinho = NULL; // Variável local obrigatória
    int opcao;

    do {
        printf("\n--- MENU CARRINHO ---");
        printf("\n1. Adicionar Produto");
        printf("\n2. Listar Carrinho");
        printf("\n3. Remover Produto");
        printf("\n0. Sair e Finalizar");
        printf("\nEscolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa o buffer em caso de erro
            continue;
        }

        switch(opcao) {
            case 1: adicionar(&carrinho); break;
            case 2: listar(carrinho); break;
            case 3: remover(&carrinho); break;
            case 0: limparCarrinho(&carrinho); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

//main.c - Gerenciamento de produtos

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    Produto *lista = NULL;
    int opcaoMenu;
    int codigo;
    Produto *resultado;

    do {
        printf("\n--- MENU PRODUTOS ---\n");
        printf("1. Cadastrar produtos\n");
        printf("2. Listar produtos\n");
        printf("3. Buscar produto\n");
        printf("4. Editar produto\n");
        printf("5. Remover produto\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {

        case 1:
            printf("\nDigite os dados do produto (digite 'fim' no nome para encerrar):\n");
            while (1) {
                Produto *antes = lista;
                lista = cadastrarProduto(lista);
                if (lista == antes)
                    break;
            }
            break;

        case 2:
            imprimirProdutos(lista);
            break;

        case 3:
            printf("Digite o codigo do produto: ");
            scanf("%d", &codigo);

            resultado = buscarProduto(lista, codigo);

            if (resultado != NULL) {
                printf("\nCodigo: %d\n", resultado->codigo);
                printf("Nome: %s\n", resultado->nome);
                printf("Preco: %.2f\n", resultado->preco);
                printf("Quantidade: %d\n", resultado->quantidade);
            } else {
                printf("\nProduto nao encontrado.\n");
            }
            break;

        case 4:
            printf("Digite o codigo do produto a editar: ");
            scanf("%d", &codigo);

            resultado = buscarProduto(lista, codigo);

            if (resultado != NULL) {
                printf("Novo nome: ");
                scanf(" %[^\n]", resultado->nome);

                printf("Novo preco: ");
                scanf("%f", &resultado->preco);

                printf("Nova quantidade: ");
                scanf("%d", &resultado->quantidade);

                printf("\nProduto atualizado!\n");
                imprimirProdutos(lista);
            } else {
                printf("\nProduto nao encontrado.\n");
            }
            break;

        case 5:
            printf("Digite o codigo do produto a remover: ");
            scanf("%d", &codigo);

            lista = removerProduto(lista, codigo);
            imprimirProdutos(lista);
            break;

        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("\nOpcao invalida.\n");
        }

    } while (opcaoMenu != 0);

    return 0;
}


    return 0;

}

