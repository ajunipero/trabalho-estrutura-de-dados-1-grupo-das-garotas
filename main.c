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

    return 0;
}