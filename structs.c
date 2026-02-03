// structs.c
typedef struct Produto {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    struct Produto *proximo;
} Produto;