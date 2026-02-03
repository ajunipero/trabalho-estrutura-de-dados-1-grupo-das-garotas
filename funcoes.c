#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

/*  FUNÇÕES UTILITÁRIAS */

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
    printf("Pressione ENTER para continuar...");
    limpar_buffer_entrada();
    getchar();
}

/* Função para verificar se o CPF possui exatamente 11 dígitos numéricos */
int validar_cpf(const char *cpf) {
    int cont = 0;
    while (cpf[cont] != '\0') {
        if (!isdigit(cpf[cont])) {
            return 0; // Contém caracteres não numéricos
        }
        cont++;
    }
    return (cont == 11); // Retorna 1 se tiver exatamente 11 dígitos
}

/* FUNÇÕES DE CLIENTES */

Cliente* buscar_cliente(Cliente *listaClientes, const char *cpf) {
    Cliente *atual = listaClientes;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

/* -------- CADASTRAR CLIENTE -------- */

Cliente* cadastrar_cliente(Cliente *listaClientes) {
    Cliente *novoCliente = malloc(sizeof(Cliente));
    if (novoCliente == NULL) {
        printf("Erro ao alocar memoria.\n");
        pausar_tela();
        return listaClientes;
    }

    printf("\n--- CADASTRAR CLIENTE ---\n");

    do {
        printf("CPF (exatamente 11 digitos): ");
        ler_string(novoCliente->cpf, sizeof(novoCliente->cpf));
        
        if (!validar_cpf(novoCliente->cpf)) {
            printf("CPF invalido! Digite apenas os 11 numeros.\n");
        }
    } while (!validar_cpf(novoCliente->cpf));
    
    // Removido limpar_buffer_entrada() extra que estava causando problemas de sincronia
    printf("Nome: ");
    ler_string(novoCliente->nome, sizeof(novoCliente->nome));

    printf("Email: ");
    ler_string(novoCliente->email, sizeof(novoCliente->email));

    printf("Telefone: ");
    ler_string(novoCliente->telefone, sizeof(novoCliente->telefone));

    printf("Data de Nascimento (DD/MM/AAAA): ");
    ler_string(novoCliente->dataNascimento, sizeof(novoCliente->dataNascimento));

    novoCliente->proximo = listaClientes;
    listaClientes = novoCliente;

    printf("Cliente cadastrado com sucesso!\n");
    pausar_tela();

    return listaClientes;
}

/* -------- LISTAR CLIENTES -------- */

void listar_clientes(Cliente *listaClientes) {
    if (listaClientes == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        pausar_tela();
        return;
    }

    printf("\n--- LISTA DE CLIENTES ---\n");
    Cliente *atual = listaClientes;

    while (atual != NULL) {
        printf("CPF: %s\n", atual->cpf);
        printf("Nome: %s\n", atual->nome);
        printf("Email: %s\n", atual->email);
        printf("Telefone: %s\n", atual->telefone);
        printf("Data de Nascimento: %s\n", atual->dataNascimento);
        printf("---------------------------\n");
        atual = atual->proximo;
    }

    pausar_tela();
}

/* -------- EDITAR CLIENTE -------- */

void editar_cliente(Cliente *listaClientes) {
    char cpfBusca[15]; // Alterado de 12 para 15 conforme solicitado

    printf("\n--- EDITAR CLIENTE ---\n");
    printf("Digite o CPF: ");
    ler_string(cpfBusca, sizeof(cpfBusca));

    Cliente *clienteParaEditar = buscar_cliente(listaClientes, cpfBusca);

    if (clienteParaEditar == NULL) {
        printf("Cliente nao encontrado.\n");
        pausar_tela();
        return;
    }

    printf("Novo Nome: ");
    ler_string(clienteParaEditar->nome, sizeof(clienteParaEditar->nome));

    printf("Novo Email: ");
    ler_string(clienteParaEditar->email, sizeof(clienteParaEditar->email));

    printf("Novo Telefone: ");
    ler_string(clienteParaEditar->telefone, sizeof(clienteParaEditar->telefone));

    printf("Nova Data de Nascimento: ");
    ler_string(clienteParaEditar->dataNascimento,
               sizeof(clienteParaEditar->dataNascimento));

    printf("Cliente editado com sucesso!\n");
    pausar_tela();
}

/* -------- REMOVER CLIENTE -------- */

Cliente* remover_cliente(Cliente *listaClientes) {
    char cpfBusca[15]; // Alterado de 12 para 15 conforme solicitado

    printf("\n--- REMOVER CLIENTE ---\n");
    printf("Digite o CPF: ");
    ler_string(cpfBusca, sizeof(cpfBusca));

    Cliente *atual = listaClientes;
    Cliente *anterior = NULL;

    while (atual != NULL && strcmp(atual->cpf, cpfBusca) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Cliente nao encontrado.\n");
        pausar_tela();
        return listaClientes;
    }

    if (anterior == NULL) {
        listaClientes = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Cliente removido com sucesso!\n");
    pausar_tela();

    return listaClientes;
}

/* -------- LIBERAR MEMÓRIA -------- */

void liberar_clientes(Cliente *listaClientes) {
    Cliente *atual = listaClientes;
    while (atual != NULL) {
        Cliente *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}