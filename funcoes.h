#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs_trabalho.h"

//Funções utilitárias
void limpar_buffer_entrada();
void ler_string(char *buffer, int tamanho);
int validar_cpf(const char *cpf);
void pausar_tela();

//Funções do CRU de Cliente
Cliente* cadastrar_cliente(Cliente *listaClientes);
void listar_clientes(Cliente *listaClientes);
Cliente* buscar_cliente(Cliente *listaClientes, const char *cpf);
void editar_cliente(Cliente *listaClientes);
Cliente* remover_cliente(Cliente *listaClientes);
void liberar_clientes(Cliente *listaClientes);


#endif // FUNCOES_H