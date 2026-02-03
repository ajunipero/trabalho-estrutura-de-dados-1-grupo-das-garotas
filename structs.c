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

typedef struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
    struct Produto *prox;
} Produto;

#endif
