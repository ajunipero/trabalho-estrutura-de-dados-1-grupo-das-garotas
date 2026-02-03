// structs.c menu de clientes

typedef struct Cliente {
    char cpf[15];
    char nome[100];
    char email[100];
    char telefone[15];
    char dataNascimento[11];
    struct Cliente *proximo;
} Cliente;

// structs.c
typedef struct Produto {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    struct Produto *proximo;

} Produto;

//structs.c gerenciamento de produto

#ifndef STRUCTS_H
#define STRUCTS_H

// structs.c
typedef struct Produto {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    struct Produto *proximo;
} Produto;
