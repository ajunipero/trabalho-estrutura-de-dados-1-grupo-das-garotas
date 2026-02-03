#ifndef STRUCTS_H
#define STRUCTS_H

/* ===== CLIENTE ===== */
typedef struct Cliente {
    char cpf[15];
    char nome[100];
    char email[100];
    char telefone[20];
    char dataNascimento[15];
    struct Cliente *proximo;
} Cliente;

/* ===== PRODUTO ===== */
typedef struct Produto {
    int codigo;
    char nome[100];
    float preco;
    int quantidade;
    struct Produto *proximo;
} Produto;

/* ===== COMPRA (CARRINHO) ===== */
typedef struct Compra {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    struct Compra *proximo;
} Compra;

#endif
