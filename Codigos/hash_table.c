#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Função de hash simples
unsigned int funcao_hash(int chave) {
    return chave % TAMANHO_TABELA;
}

// ======================= Encadeamento Fechado =======================
No** criar_tabela_fechada() {
    No** tabela = (No**)calloc(TAMANHO_TABELA, sizeof(No*)); // Inicializa com NULL
    return tabela;
}

void inserir_fechado(No** tabela, Cliente cliente) {
    unsigned int indice = funcao_hash(cliente.id);
    
    // Verifica se já há um elemento na posição
    if (tabela[indice] != NULL) {
        printf("Colisão detectada! Índice: %u\n", indice);
    }
    
    No* novo = (No*)malloc(sizeof(No));
    novo->cliente = cliente;
    novo->proximo = tabela[indice]; // Adiciona na frente da lista encadeada
    tabela[indice] = novo;

    printf("Cliente armazenado no índice: %u\n", indice);
}


Cliente* buscar_fechado(No** tabela, int id) {
    unsigned int indice = funcao_hash(id);
    No* atual = tabela[indice];
    while (atual) {
        if (atual->cliente.id == id) {
            return &atual->cliente;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void remover_fechado(No** tabela, int id) {
    unsigned int indice = funcao_hash(id);
    No* atual = tabela[indice];
    No* anterior = NULL;

    while (atual && atual->cliente.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual) {
        if (anterior) {
            anterior->proximo = atual->proximo;
        } else {
            tabela[indice] = atual->proximo;
        }
        free(atual);
    }
}

void liberar_tabela_fechada(No** tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela[i];
        while (atual) {
            No* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(tabela);
}

// ======================= Encadeamento Aberto =======================
TabelaAberta* criar_tabela_aberta() {
    TabelaAberta* tabela = (TabelaAberta*)malloc(sizeof(TabelaAberta));
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->entradas[i].ocupado = 0;
    }
    return tabela;
}

void inserir_aberto(TabelaAberta* tabela, Cliente cliente) {
    unsigned int indice = funcao_hash(cliente.id);
    unsigned int inicial = indice;

    // Verifica colisões usando sondagem linear
    int colisao = 0;
    while (tabela->entradas[indice].ocupado) {
        colisao = 1; // Marca colisão
        indice = (indice + 1) % TAMANHO_TABELA;
        if (indice == inicial) {
            printf("Erro: Tabela cheia. Não foi possível inserir o cliente.\n");
            return;
        }
    }

    if (colisao) {
        printf("Colisão detectada! Realizada sondagem linear.\n");
    }

    tabela->entradas[indice].cliente = cliente;
    tabela->entradas[indice].ocupado = 1;

    printf("Cliente armazenado no índice: %u\n", indice);
}


Cliente* buscar_aberto(TabelaAberta* tabela, int id) {
    unsigned int indice = funcao_hash(id);
    unsigned int inicial = indice;
    do {
        if (tabela->entradas[indice].ocupado && tabela->entradas[indice].cliente.id == id) {
            return &tabela->entradas[indice].cliente;
        }
        indice = (indice + 1) % TAMANHO_TABELA;
    } while (indice != inicial);
    return NULL;
}

void remover_aberto(TabelaAberta* tabela, int id) {
    unsigned int indice = funcao_hash(id);
    unsigned int inicial = indice;
    do {
        if (tabela->entradas[indice].ocupado && tabela->entradas[indice].cliente.id == id) {
            tabela->entradas[indice].ocupado = 0;
            return;
        }
        indice = (indice + 1) % TAMANHO_TABELA;
    } while (indice != inicial);
}

void liberar_tabela_aberta(TabelaAberta* tabela) {
    free(tabela);
}

// ======================= Funções de Teste =======================
void inserir_fechado_teste(void* clientes) {
    No** tabela = criar_tabela_fechada();
    Cliente* dados = (Cliente*)clientes;
    for (int i = 0; i < 100; i++) {
        inserir_fechado(tabela, dados[i]);
    }
    liberar_tabela_fechada(tabela);
}

void buscar_fechado_teste(void* clientes) {
    No** tabela = criar_tabela_fechada();
    Cliente* dados = (Cliente*)clientes;
    for (int i = 0; i < 100; i++) {
        inserir_fechado(tabela, dados[i]);
    }
    for (int i = 0; i < 100; i++) {
        buscar_fechado(tabela, dados[i].id);
    }
    liberar_tabela_fechada(tabela);
}

void remover_fechado_teste(void* clientes) {
    No** tabela = criar_tabela_fechada();
    Cliente* dados = (Cliente*)clientes;
    for (int i = 0; i < 100; i++) {
        inserir_fechado(tabela, dados[i]);
    }
    for (int i = 0; i < 100; i++) {
        remover_fechado(tabela, dados[i].id);
    }
    liberar_tabela_fechada(tabela);
}

void inserir_aberto_teste(void* clientes) {
    TabelaAberta* tabela = criar_tabela_aberta();
    Cliente* dados = (Cliente*)clientes;
    for (int i = 0; i < 100; i++) {
        inserir_aberto(tabela, dados[i]);
    }
    liberar_tabela_aberta(tabela);
}

void buscar_aberto_teste(void* clientes) {
    TabelaAberta* tabela = criar_tabela_aberta();
    Cliente* dados = (Cliente*)clientes;
    for (int i = 0; i < 100; i++) {
        inserir_aberto(tabela, dados[i]);
    }
    for (int i = 0; i < 100; i++) {
        buscar_aberto(tabela, dados[i].id);
    }
    liberar_tabela_aberta(tabela);
}

void remover_aberto_teste(void* clientes) {
    TabelaAberta* tabela = criar_tabela_aberta();
    Cliente* dados = (Cliente*)clientes;
    for (int i = 0; i < 100; i++) {
        inserir_aberto(tabela, dados[i]);
    }
    for (int i = 0; i < 100; i++) {
        remover_aberto(tabela, dados[i].id);
    }
    liberar_tabela_aberta(tabela);
}
