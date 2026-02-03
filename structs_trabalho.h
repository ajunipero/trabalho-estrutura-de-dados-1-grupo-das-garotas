#ifndef STRUCTS_TRABALHO_H
#define STRUCTS_TRABALHO_H

// Definição da struct Cliente
typedef struct Cliente {
    char cpf[15];
    char nome[100];
    char email[100];
    char telefone[15];
    char dataNascimento[11];
    struct Cliente *proximo; 
} Cliente;

#endif // STRUCTS_TRABALHO_H