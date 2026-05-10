#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_VETOR 10

// --- Estruturas (Requisito 1) ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// --- Protótipos: Vetor ---
void inserirVetor(Item v[], int *n);
void listarVetor(Item v[], int n);
void ordenarVetor(Item v[], int n);
int buscaBinaria(Item v[], int n, char *alvo, int *comps);

// --- Protótipos: Lista Encadeada ---
No* inserirLista(No* inicio);
void listarLista(No* inicio);
No* removerLista(No* inicio, char *nome);
void buscaSequencialLista(No* inicio, char *alvo);

// --- Auxiliares ---
void limparBuffer();

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    // Dados para o Vetor
    Item mochilaVetor[MAX_VETOR];
    int totalVetor = 0;

    // Dados para a Lista
    No* mochilaLista = NULL;

    int opcao, comps = 0;
    char busca[30];

    do {
        printf("\n=== DESAFIO DE PERFORMANCE: MK GÊNIO ===");
        printf("\n1. [Vetor] Inserir Item");
        printf("\n2. [Vetor] Ordenar e Busca Binária");
        printf("\n3. [Lista] Inserir Item");
        printf("\n4. [Lista] Buscar (Sequencial)");
        printf("\n5. Listar Ambas");
        printf("\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                inserirVetor(mochilaVetor, &totalVetor);
                break;
            case 2:
                if(totalVetor > 0) {
                    ordenarVetor(mochilaVetor, totalVetor);
                    printf("Busca Binária - Nome: ");
                    fgets(busca, 30, stdin); busca[strcspn(busca, "\n")] = 0;
                    comps = 0;
                    int res = buscaBinaria(mochilaVetor, totalVetor, busca, &comps);
                    if(res != -1) printf("Achado na pos %d! Comparações: %d\n", res, comps);
                    else printf("Não encontrado. Comparações: %d\n", comps);
                }
                break;
            case 3:
                mochilaLista = inserirLista(mochilaLista);
                break;
            case 4:
                printf("Busca na Lista - Nome: ");
                fgets(busca, 30, stdin); busca[strcspn(busca, "\n")] = 0;
                buscaSequencialLista(mochilaLista, busca);
                break;
            case 5:
                printf("\n--- MODO VETOR ---"); listarVetor(mochilaVetor, totalVetor);
                printf("\n--- MODO LISTA ---"); listarLista(mochilaLista);
                break;
        }
    } while(opcao != 0);

    return 0;
}

// --- LOGICA DE VETOR (ESTÁTICO) ---

void inserirVetor(Item v[], int *n) {
    if (*n < MAX_VETOR) {
        printf("Nome do item: "); fgets(v[*n].nome, 30, stdin);
        v[*n].nome[strcspn(v[*n].nome, "\n")] = 0;
        printf("Qtd: "); scanf("%d", &v[*n].quantidade); limparBuffer();
        (*n)++;
    } else printf("Mochila cheia!\n");
}

void ordenarVetor(Item v[], int n) { // Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Item temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    printf("Vetor Ordenado com Sucesso!\n");
}

int buscaBinaria(Item v[], int n, char *alvo, int *comps) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        (*comps)++;
        int meio = (ini + fim) / 2;
        int res = strcmp(v[meio].nome, alvo);
        if (res == 0) return meio;
        if (res < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// --- LOGICA DE LISTA (DINÂMICO) ---

No* inserirLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));
    printf("Nome do item: "); fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;
    printf("Qtd: "); scanf("%d", &novo->dados.quantidade); limparBuffer();
    novo->proximo = inicio; // Insere no início (mais rápido)
    return novo;
}

void buscaSequencialLista(No* inicio, char *alvo) {
    int comps = 0;
    No* atual = inicio;
    while (atual != NULL) {
        comps++;
        if (strcmp(atual->dados.nome, alvo) == 0) {
            printf("Encontrado! Qtd: %d | Comparações: %d\n", atual->dados.quantidade, comps);
            return;
        }
        atual = atual->proximo;
    }
    printf("Não encontrado. Comparações: %d\n", comps);
}

void listarVetor(Item v[], int n) {
    for(int i=0; i<n; i++) printf("\n[%d] %s (x%d)", i, v[i].nome, v[i].quantidade);
}

void listarLista(No* inicio) {
    No* temp = inicio;
    while(temp) {
        printf("\n-> %s (x%d)", temp->dados.nome, temp->dados.quantidade);
        temp = temp->proximo;
    }
}

void limparBuffer() { while (getchar() != '\n'); }