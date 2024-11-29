#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// tamanho tabela e tamanho string para o nome
#define TAMANHO_TABELA 100 
#define TAMANHO_STRING 50

// struct para receber dados do cliente
typedef struct {
    int id; // o id é o CPF
    char nome[TAMANHO_STRING];
} Cliente;

// Estrutura para encadeamento fechado
typedef struct No {
    Cliente cliente;
    struct No* proximo;
} No;

// Estrutura para encadeamento aberto
typedef struct {
    Cliente cliente;
    int ocupado; // Indica se a posição está ocupada
} Entrada;

typedef struct {
    Entrada entradas[TAMANHO_TABELA];
} TabelaAberta;

// Funções gerais
unsigned int funcao_hash(int chave);

// Encadeamento Fechado
No** criar_tabela_fechada();
void inserir_fechado(No** tabela, Cliente cliente);
Cliente* buscar_fechado(No** tabela, int id);
void remover_fechado(No** tabela, int id);
void liberar_tabela_fechada(No** tabela);

// Encadeamento Aberto
TabelaAberta* criar_tabela_aberta();
void inserir_aberto(TabelaAberta* tabela, Cliente cliente);
Cliente* buscar_aberto(TabelaAberta* tabela, int id);
void remover_aberto(TabelaAberta* tabela, int id);
void liberar_tabela_aberta(TabelaAberta* tabela);

// Funções para teste de desempenho
void inserir_fechado_teste(void* clientes);
void buscar_fechado_teste(void* clientes);
void remover_fechado_teste(void* clientes);

void inserir_aberto_teste(void* clientes);
void buscar_aberto_teste(void* clientes);
void remover_aberto_teste(void* clientes);

#endif
