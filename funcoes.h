#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/* ========= UTILITÁRIOS ========= */
void limpar_buffer_entrada(void);
void ler_string(char *buffer, int tamanho);
int validar_cpf(const char *cpf);
void pausar_tela(void);

/* ========= CLIENTES ========= */
Cliente* cadastrar_cliente(Cliente *listaClientes);
void listar_clientes(Cliente *listaClientes);
Cliente* buscar_cliente(Cliente *listaClientes, const char *cpf);
void editar_cliente(Cliente *listaClientes);
Cliente* remover_cliente(Cliente *listaClientes);
void liberar_clientes(Cliente *listaClientes);

/* ========= PRODUTOS ========= */
Produto* cadastrarProduto(Produto *lista);
void imprimirProdutos(Produto *lista);
Produto* buscarProduto(Produto *lista, int codigo);
int codigoExiste(Produto *lista, int codigo);
Produto* removerProduto(Produto *lista, int codigo);

/* ========= CARRINHO ========= */
void adicionar_carrinho(Compra **topo);
void listar_carrinho(Compra *topo);
void remover_carrinho(Compra **topo);
void limpar_carrinho(Compra **topo);

/* ========= MENUS ========= */
void menu_clientes(Cliente **listaClientes);
void menu_produtos(Produto **listaProdutos);
void menu_carrinho(Compra **carrinho);

#endif
