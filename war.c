#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// --- Constantes ---
#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// --- Estrutura de Dados (Requisito: Criação da struct) ---
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// --- Protótipos das Funções ---
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void limparBuffer();

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    Item mochila[MAX_ITENS]; // Vetor de structs (Capacidade 10)
    int totalItens = 0;      // Contador de itens atuais
    int opcao;

    do {
        printf("\n--- MENU DE INVENTÁRIO---");
        printf("\n1. Cadastrar Item");
        printf("\n2. Remover Item");
        printf("\n3. Buscar Item");
        printf("\n4. Listar Mochila");
        printf("\n0. Sair");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                buscarItem(mochila, totalItens);
                break;
            case 4:
                listarItens(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema de loot...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Requisito: Cadastro de itens (até 10)
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia! Remova algo para abrir espaço.\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(mochila[*total].nome, TAM_NOME, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = 0; // Remove o \n

    printf("Tipo (arma/municao/cura): ");
    fgets(mochila[*total].tipo, TAM_TIPO, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBuffer();

    (*total)++;
    printf("\n[SUCESSO] Item adicionado ao inventário!\n");
}

// Requisito: Listagem dos itens
void listarItens(Item mochila[], int total) {
    printf("\n--- CONTEÚDO DA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    if (total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("%-20s | %-15s | %-10s\n", "NOME", "TIPO", "QTD");
    for (int i = 0; i < total; i++) {
        printf("%-20s | %-15s | %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Requisito: Busca sequencial por nome
void buscarItem(Item mochila[], int total) {
    char termo[TAM_NOME];
    printf("\nDigite o nome do item para buscar: ");
    fgets(termo, TAM_NOME, stdin);
    termo[strcspn(termo, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcasecmp(mochila[i].nome, termo) == 0) {
            printf("\n[ITEM ENCONTRADO]");
            printf("\nNome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("\n[AVISO] Item '%s' não encontrado na mochila.\n", termo);
}

// Requisito: Remoção de itens (por nome)
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n[ERRO] Nada para remover.\n");
        return;
    }

    char termo[TAM_NOME];
    printf("\nDigite o nome do item a ser excluído: ");
    fgets(termo, TAM_NOME, stdin);
    termo[strcspn(termo, "\n")] = 0;

    for (int i = 0; i < *total; i++) {
        if (strcasecmp(mochila[i].nome, termo) == 0) {
            // Reorganiza o vetor (traz o último para a vaga do excluído ou desloca)
            for (int j = i; j < (*total) - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n[SUCESSO] Item removido.\n");
            return;
        }
    }
    printf("\n[ERRO] Item não localizado.\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}