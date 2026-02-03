#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h" 

// Menu de gerenciamento de clientes
void menu_clientes(Cliente **listaClientes) {
    int opcao;
    do {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente por CPF\n");
        printf("4. Editar Cliente\n");
        printf("5. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer_entrada();

        switch (opcao) {
            case 1:
                *listaClientes = cadastrar_cliente(*listaClientes);
                break;
            case 2:
                listar_clientes(*listaClientes);
                break;
            case 3: {
                char cpfBusca[12];
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
                break;
        }
    } while (opcao != 0);
}

int main() {
    Cliente *listaClientes = NULL; 
    int opcao;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Gerenciamento de Clientes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer_entrada();

        switch (opcao) {
            case 1:
                menu_clientes(&listaClientes);
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                pausar_tela();
                break;
        }
    } while (opcao != 0);

    liberar_clientes(listaClientes);

    return 0;
}