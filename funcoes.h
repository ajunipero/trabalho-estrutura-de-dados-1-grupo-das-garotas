// funcoes.h — Menu de Clientes e Produtos

#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"

/* ========= FUNÇÕES UTILITÁRIAS ========= */
void limpar_buffer_entrada(void);
void ler_string(char *buffer, int tamanho);
int validar_cpf(const char *cpf);
void pausar_tela(void);

/* ========= CRUD DE CLIENTES ========= */
Cliente* cadastrar_cliente(Cliente *listaClientes);
void listar_clientes(Cliente *listaClientes);
Cliente* buscar_cliente(Cliente *listaClientes, const char *cpf);
void editar_cliente(Cliente *listaClientes);
Cliente* remover_cliente(Cliente *listaClientes);
void liberar_clientes(Cliente *listaClientes);

/* ========= FUNÇÕES DE PRODUTO / CARRINHO ========= */
void adicionar(Produto **topo);
void listar(Produto *topo);
void remover(Produto **topo);
void limparCarrinho(Produto **topo);

#endif 
