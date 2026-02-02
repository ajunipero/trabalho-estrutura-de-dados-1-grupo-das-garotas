# CRUD de Clientes e Produtos em C  
## Estrutura de Dados I — Listas Simplesmente Encadeadas

---

## 🇧🇷 Português

### Visão Geral
Este repositório contém o **Trabalho Prático da disciplina Estrutura de Dados I**, cujo objetivo é desenvolver uma aplicação em **linguagem C**, executada via **terminal**, para o gerenciamento de **clientes, produtos e compras**.

O sistema utiliza **listas simplesmente encadeadas** e **alocação dinâmica de memória**, implementando operações completas de **CRUD**, conforme os requisitos propostos.

---

### Funcionalidades do Sistema

#### Gerenciamento de Clientes
- Cadastro de clientes (CPF, nome, e-mail, telefone, data de nascimento)
- Listagem de todos os clientes
- Busca de cliente pelo CPF
- Edição de dados do cliente
- Remoção de clientes

#### Gerenciamento de Produtos
- Cadastro de produtos (código único, nome, preço, quantidade)
- Listagem de todos os produtos
- Busca de produto pelo código
- Edição de dados do produto
- Remoção de produtos

#### Modo Compra
- Inclusão de produtos no carrinho de um cliente
- Listagem dos produtos do carrinho, com quantidade total e valor final
- Remoção de produtos do carrinho

---

### Requisitos Técnicos Atendidos
- Implementação **exclusivamente em C**
- Uso obrigatório de **listas simplesmente encadeadas**
- **Alocação dinâmica de memória** (`malloc`, `calloc`, `realloc`, `free`)
- Proibição do uso de **variáveis globais**
- Manipulação das listas por **passagem de parâmetros**
- **Menu funcional via terminal**
- Código modularizado em arquivos `.h` e `.c`
- Repositório Git com contribuições distribuídas ao longo do tempo

---

### Estrutura do Projeto
- `main.c` — Função principal e menu do sistema 
- `funcoes.h / funcoes.c` — Define (.h) e implementa (.c) as funções do sistema
- `structs.h` — Definição das estruturas de dados  
- `makefile` — Automação da compilação  

---
## us English
---

# Client and Product CRUD System in C  
## Data Structures I — Singly Linked Lists

---

### Overview
This repository contains the **practical assignment for the Data Structures I course**.  
The project consists of a **terminal-based application written in C** for managing **clients, products, and purchase operations**.

The system is implemented using **singly linked lists** and **dynamic memory allocation**, providing full **CRUD functionality** in accordance with the proposed requirements.

---

### System Features

#### Client Management
- Register clients (CPF, name, email, phone number, date of birth)
- List all clients
- Search clients by CPF
- Edit client data
- Remove clients

#### Product Management
- Register products (unique code, name, price, quantity)
- List all products
- Search products by code
- Edit product data
- Remove products

#### Purchase Mode
- Add products to a client’s shopping cart
- List cart items with total quantity and total cost
- Remove products from the cart

---

### Technical Requirements Met
- Implemented **exclusively in C**
- Mandatory use of **singly linked lists**
- **Dynamic memory allocation** (`malloc`, `calloc`, `realloc`, `free`)
- No use of **global variables**
- List manipulation via **parameter passing**
- Fully functional **terminal-based menu**
- Modular code organization using `.h` and `.c` files
- Git repository with incremental group contributions

---

### Project Structure
- `main.c` — Program entry point and main menu
- `funcoes.h / funcoes.c` — Defines (.h) and implements (.c) the system functions
- `structs.h` — Data structure definitions  
- `makefile` — Build automation  

---






