#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
#define TOTAL_TERRITORIOS 5
#define MAX_NOME 30

// --- Estrutura de Dados ---
typedef struct {
    char nome[MAX_NOME];
    char cor[20];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
Territorio* alocarMapa();
void inicializarTerritorios(Territorio* mapa);
void exibirMapa(const Territorio* mapa);
void exibirMissao(int missaoID);
void simularAtaque(Territorio* origem, Territorio* destino);
void limparBufferEntrada();
void liberarMemoria(Territorio* mapa);

// --- Função Principal ---
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Semente para números aleatórios

    // 1. Setup
    Territorio* mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    inicializarTerritorios(mapa);
    
    int missaoID = rand() % 2; // Sorteia missão 0 ou 1
    int opcao;

    // 2. Game Loop
    do {
        system("cls || clear"); // Limpa a tela conforme o SO
        printf("=== WAR ESTRUTURADO ===\n");
        exibirMissao(missaoID);
        exibirMapa(mapa);

        printf("\n1. Atacar\n2. Verificar Vitoria\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                // Exemplo simples de ataque entre território 0 e 1 para demonstração
                simularAtaque(&mapa[0], &mapa[1]);
                break;
            case 2:
                printf("\n[LOG] Analisando requisitos da missao...\n");
                printf("Ainda ha batalhas pela frente!\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar();

    } while (opcao != 0);

    // 3. Limpeza
    liberarMemoria(mapa);
    return 0;
}

// --- Implementação das Funções ---

// DOCUMENTAÇÃO: Aloca memória dinamicamente (Requisito Técnico)
Territorio* alocarMapa() {
    return (Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
}

// DOCUMENTAÇÃO: Inicializa os dados (Passagem por referência)
void inicializarTerritorios(Territorio* mapa) {
    char nomes[5][MAX_NOME] = {"Brasil", "Egito", "Russia", "China", "EUA"};
    char cores[5][20] = {"Verde", "Amarelo", "Vermelho", "Azul", "Branco"};

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = rand() % 10 + 2; // Começa com 2 a 11 tropas
    }
}

// DOCUMENTAÇÃO: Uso de 'const' para apenas leitura
void exibirMapa(const Territorio* mapa) {
    printf("\n%-15s | %-10s | %-6s\n", "TERRITORIO", "COR", "TROPAS");
    printf("------------------------------------------\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%-15s | %-10s | %-6d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int missaoID) {
    printf("\nSUA MISSAO: ");
    if (missaoID == 0) printf("Dominar 3 territorios inimigos.\n");
    else printf("Eliminar o exercito Vermelho.\n");
}

// DOCUMENTAÇÃO: Lógica de ataque modificando dados via ponteiros
void simularAtaque(Territorio* origem, Territorio* destino) {
    printf("\nAtaque: %s (%s) vs %s (%s)\n", origem->nome, origem->cor, destino->nome, destino->cor);
    
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("Dados -> Ataque: %d | Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("Vitoria do atacante! %s perdeu 1 tropa.\n", destino->nome);
        destino->tropas--;
    } else {
        printf("Defesa segurou! %s perdeu 1 tropa.\n", origem->nome);
        origem->tropas--;
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}
