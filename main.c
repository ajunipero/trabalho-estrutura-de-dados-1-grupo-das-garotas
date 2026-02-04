// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/* --- MENU DE CLIENTES --- */
void menu_clientes(Cliente **listaClientes) {
    int opcao;
    do {
        printf("\n--- GERENCIAMENTO DE CLIENTES ---\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente por CPF\n");
        printf("4. Editar Cliente\n");
        printf("5. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();

        switch (opcao) {
            case 1:
                *listaClientes = cadastrar_cliente(*listaClientes);
                break;

            case 2:
                listar_clientes(*listaClientes);
                break;

            case 3: {
                char cpfBusca[15];
                printf("Digite o CPF do cliente a buscar: ");
                ler_string(cpfBusca, sizeof(cpfBusca));

                Cliente *clienteEncontrado = buscar_cliente(*listaClientes, cpfBusca);
                if (clienteEncontrado != NULL) {
                    printf("\nCliente Encontrado:\n");
                    printf("CPF: %s\n", clienteEncontrado->cpf);
                    printf("Nome: %s\n", clienteEncontrado->nome);
                    printf("Email: %s\n", clienteEncontrado->email);
                    printf("Telefone: %s\n", clienteEncontrado->telefone);
                    printf("Data de Nascimento: %s\n", clienteEncontrado->dataNascimento);
                } else {
                    printf("Cliente com CPF %s nao encontrado.\n", cpfBusca);
                }
                pausar_tela();
                break;
            }

            case 4:
                editar_cliente(*listaClientes);
                break;

            case 5:
                *listaClientes = remover_cliente(*listaClientes);
                break;

            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                pausar_tela();
        }
    } while (opcao != 0);
}

/* --- MENU DE PRODUTOS --- */
void menu_produtos(Produto **listaProdutos) {
    int opcao;
    int codigo;
    Produto *resultado;

    do {
        printf("\n--- GERENCIAMENTO DE PRODUTOS ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto\n");
        printf("4. Editar Produto\n");
        printf("5. Remover Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();

        switch (opcao) {

        case 1:
            *listaProdutos = cadastrarProduto(*listaProdutos);
            break;

        case 2:
            imprimirProdutos(*listaProdutos); // ← pausa já ocorre na função
            break;

        case 3:
            printf("Digite o codigo do produto: ");
            scanf("%d", &codigo);
            limpar_buffer_entrada();

            resultado = buscarProduto(*listaProdutos, codigo);
            if (resultado != NULL) {
                printf("\nCodigo: %d | Nome: %s | Preco: %.2f | Qtd: %d\n",
                       resultado->codigo,
                       resultado->nome,
                       resultado->preco,
                       resultado->quantidade);
            } else {
                printf("\nProduto nao encontrado.\n");
            }
            pausar_tela();
            break;

        case 4:
            printf("Digite o codigo do produto a editar: ");
            scanf("%d", &codigo);
            limpar_buffer_entrada();

            resultado = buscarProduto(*listaProdutos, codigo);
            if (resultado != NULL) {
                printf("\n--- PRODUTO ATUAL ---\n");
                printf("Codigo: %d\n", resultado->codigo);
                printf("Nome: %s\n", resultado->nome);
                printf("Preco: %.2f\n", resultado->preco);
                printf("Quantidade: %d\n\n", resultado->quantidade);

                printf("Novo nome: ");
                ler_string(resultado->nome, sizeof(resultado->nome));

                printf("Novo preco: ");
                scanf("%f", &resultado->preco);

                printf("Nova quantidade: ");
                scanf("%d", &resultado->quantidade);
                limpar_buffer_entrada();

                printf("\nProduto atualizado com sucesso!\n");
            } else {
                printf("\nProduto nao encontrado.\n");
            }
            pausar_tela();
            break;

        case 5:
            printf("Digite o codigo do produto a remover: ");
            scanf("%d", &codigo);
            limpar_buffer_entrada();

            *listaProdutos = removerProduto(*listaProdutos, codigo);
            pausar_tela();
            break;

        case 0:
            break;

        default:
            printf("\nOpcao invalida!\n");
            pausar_tela();
        }

    } while (opcao != 0);
}

/* --- MENU DO CARRINHO --- */
void menu_carrinho(Compra **carrinho) {
    int opcao;
    do {
        printf("\n--- MENU CARRINHO ---");
        printf("\n1. Adicionar Produto ao Carrinho");
        printf("\n2. Listar Carrinho");
        printf("\n3. Remover Produto do Carrinho");
        printf("\n0. Sair e Finalizar");
        printf("\nEscolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();

        switch (opcao) {
            case 1:
                adicionar_carrinho(carrinho);
                break;
            case 2:
                listar_carrinho(*carrinho);
                break;
            case 3:
                remover_carrinho(carrinho);
                break;
            case 0:
                limpar_carrinho(carrinho);
                break;
            default:
                printf("Opcao invalida!\n");
                pausar_tela();
        }
    } while (opcao != 0);
}

/* --- FUNÇÃO PRINCIPAL --- */
int main() {
    Cliente *listaClientes = NULL;
    Produto *listaProdutos = NULL;
    Compra *carrinho = NULL;
    int opcao;

    do {
        printf("\n--- SISTEMA DE GESTAO INTEGRADA ---\n");
        printf("1. Gerenciamento de Clientes\n");
        printf("2. Gerenciamento de Produtos\n");
        printf("3. Sistema de Carrinho de Compras\n");
        printf("0. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();

        switch (opcao) {
            case 1:
                menu_clientes(&listaClientes);
                break;
            case 2:
                menu_produtos(&listaProdutos);
                break;
            case 3:
                menu_carrinho(&carrinho);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                pausar_tela();
        }
    } while (opcao != 0);

    liberar_clientes(listaClientes);
    return 0;
}