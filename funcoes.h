// funcoes.h
#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c" // Incluindo a definição da struct

// Protótipos das funções
void adicionar(Produto **topo);
void listar(Produto *topo);
void remover(Produto **topo);
void limparCarrinho(Produto **topo);

#endif