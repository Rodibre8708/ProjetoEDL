#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash_table.h"

// Função para medir tempo de execução
double medir_tempo(void (*func)(void*), void* argumento) {
    clock_t inicio, fim;
    inicio = clock();
    func(argumento);
    fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0; // Tempo em ms
}

// Função para exibir o menu
void exibir_menu() {
    printf("\n==== SISTEMA DE CADASTRO DE CLIENTES ====\n");
    printf("1. Inserir cliente (Encadeamento Fechado)\n");
    printf("2. Buscar cliente (Encadeamento Fechado)\n");
    printf("3. Remover cliente (Encadeamento Fechado)\n");
    printf("4. Inserir cliente (Encadeamento Aberto)\n");
    printf("5. Buscar cliente (Encadeamento Aberto)\n");
    printf("6. Remover cliente (Encadeamento Aberto)\n");
    printf("7. Comparar desempenho\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// Função para testar o desempenho de ambas as tabelas
void comparar_desempenho() {
    No** tabelaFechada = criar_tabela_fechada();
    TabelaAberta* tabelaAberta = criar_tabela_aberta();

    // Gerar dados fictícios para testes
    const int n = 1000; // Número de registros
    Cliente clientes[n];
    for (int i = 0; i < n; i++) {
        clientes[i].id = i + 1;
        sprintf(clientes[i].nome, "Cliente %d", i + 1);
    }

    printf("\n==== COMPARAÇÃO DE DESEMPENHO ====\n");

    // Testar inserção
    printf("\n--- Inserção ---\n");
    double tempo_fechado = medir_tempo((void (*)(void*))inserir_fechado_teste, (void*)clientes);
    printf("Encadeamento Fechado: %.3f ms\n", tempo_fechado);

    double tempo_aberto = medir_tempo((void (*)(void*))inserir_aberto_teste, (void*)clientes);
    printf("Encadeamento Aberto: %.3f ms\n", tempo_aberto);

    // Testar busca
    printf("\n--- Busca ---\n");
    tempo_fechado = medir_tempo((void (*)(void*))buscar_fechado_teste, (void*)clientes);
    printf("Encadeamento Fechado: %.3f ms\n", tempo_fechado);

    tempo_aberto = medir_tempo((void (*)(void*))buscar_aberto_teste, (void*)clientes);
    printf("Encadeamento Aberto: %.3f ms\n", tempo_aberto);

    // Testar remoção
    printf("\n--- Remoção ---\n");
    tempo_fechado = medir_tempo((void (*)(void*))remover_fechado_teste, (void*)clientes);
    printf("Encadeamento Fechado: %.3f ms\n", tempo_fechado);

    tempo_aberto = medir_tempo((void (*)(void*))remover_aberto_teste, (void*)clientes);
    printf("Encadeamento Aberto: %.3f ms\n", tempo_aberto);

    liberar_tabela_fechada(tabelaFechada);
    liberar_tabela_aberta(tabelaAberta);
}

// Função principal para executar operações
void executar_operacoes() {
    No** tabelaFechada = criar_tabela_fechada();
    TabelaAberta* tabelaAberta = criar_tabela_aberta();
    int opcao, cpf;
    Cliente cliente;
    Cliente* encontrado;

    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Inserir (Encadeamento Fechado)
                printf("Digite o CPF (apenas números): ");
                scanf("%d", &cliente.id);
                printf("Digite o nome do cliente: ");
                scanf(" %[^\n]s", cliente.nome);
                inserir_fechado(tabelaFechada, cliente);
                printf("Cliente inserido com sucesso (Fechado)!\n");
                break;

            case 2: // Buscar (Encadeamento Fechado)
                printf("Digite o CPF para buscar: ");
                scanf("%d", &cpf);
                encontrado = buscar_fechado(tabelaFechada, cpf);
                if (encontrado) {
                    printf("Cliente encontrado: CPF: %d, Nome: %s\n", encontrado->id, encontrado->nome);
                } else {
                    printf("Cliente não encontrado (Fechado).\n");
                }
                break;

            case 3: // Remover (Encadeamento Fechado)
                printf("Digite o CPF para remover: ");
                scanf("%d", &cpf);
                remover_fechado(tabelaFechada, cpf);
                printf("Cliente removido (Fechado).\n");
                break;

            case 4: // Inserir (Encadeamento Aberto)
                printf("Digite o CPF (apenas números): ");
                scanf("%d", &cliente.id);
                printf("Digite o nome do cliente: ");
                scanf(" %[^\n]s", cliente.nome);
                inserir_aberto(tabelaAberta, cliente);
                printf("Cliente inserido com sucesso (Aberto)!\n");
                break;

            case 5: // Buscar (Encadeamento Aberto)
                printf("Digite o CPF para buscar: ");
                scanf("%d", &cpf);
                encontrado = buscar_aberto(tabelaAberta, cpf);
                if (encontrado) {
                    printf("Cliente encontrado: CPF: %d, Nome: %s\n", encontrado->id, encontrado->nome);
                } else {
                    printf("Cliente não encontrado (Aberto).\n");
                }
                break;

            case 6: // Remover (Encadeamento Aberto)
                printf("Digite o CPF para remover: ");
                scanf("%d", &cpf);
                remover_aberto(tabelaAberta, cpf);
                printf("Cliente removido (Aberto).\n");
                break;

            case 7: // Comparar desempenho
                comparar_desempenho();
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberar_tabela_fechada(tabelaFechada);
    liberar_tabela_aberta(tabelaAberta);
}

int main() {
    executar_operacoes();
    return 0;
}
