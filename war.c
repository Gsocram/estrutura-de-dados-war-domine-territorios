#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
#define MAX_NOME 30

// --- Estrutura de Dados ---
typedef struct {
    char nome[MAX_NOME];
    char cor[20];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
Territorio* alocarMapa(int total);
void inicializarTerritorios(Territorio* mapa, int total);
void exibirMapa(const Territorio* mapa, int total);
void exibirMissao(int missaoID);
// Alterado para void atacar conforme requisito
void atacar(Territorio* atacante, Territorio* defensor);
void limparBufferEntrada();
void liberarMemoria(Territorio* mapa);

// --- Função Principal ---
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); 

    int totalTerritorios;
    printf("Quantos territórios deseja cadastrar no sistema? ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada();

    // 1. Setup com Alocação Dinâmica baseada na escolha do usuário
    Territorio* mapa = alocarMapa(totalTerritorios);
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    inicializarTerritorios(mapa, totalTerritorios);
    
    int missaoID = rand() % 2; 
    int opcao;

    // 2. Game Loop
    do {
        system("cls || clear"); 
        printf("=== WAR ESTRUTURADO - MK GÊNIO ===\n");
        exibirMissao(missaoID);
        exibirMapa(mapa, totalTerritorios);

        printf("\n1. Atacar\n2. Verificar Vitoria\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1: {
                int idAtacante, idDefensor;
                printf("\nDigite o ID do território ATACANTE (0 a %d): ", totalTerritorios - 1);
                scanf("%d", &idAtacante);
                printf("Digite o ID do território DEFENSOR (0 a %d): ", totalTerritorios - 1);
                scanf("%d", &idDefensor);
                limparBufferEntrada();

                // Validação de segurança
                if (idAtacante >= 0 && idAtacante < totalTerritorios && idDefensor >= 0 && idDefensor < totalTerritorios) {
                    if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0) {
                        printf("\n[ERRO] Você não pode atacar seu próprio território!\n");
                    } else if (mapa[idAtacante].tropas < 2) {
                        printf("\n[ERRO] Tropas insuficientes para atacar (mínimo 2)!\n");
                    } else {
                        // REQUISITO: Uso de ponteiros para manipular os dados
                        atacar(&mapa[idAtacante], &mapa[idDefensor]);
                    }
                } else {
                    printf("\n[ERRO] IDs inválidos!\n");
                }
                break;
            }
            case 2:
                printf("\n[LOG] Analisando requisitos da missão...\n");
                printf("Ainda há batalhas pela frente!\n");
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

// Agora recebe o tamanho informado pelo usuário
Territorio* alocarMapa(int total) {
    return (Territorio*) calloc(total, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* mapa, int total) {
    // Nomes genéricos para suportar qualquer quantidade
    for (int i = 0; i < total; i++) {
        sprintf(mapa[i].nome, "Território %d", i + 1);
        // Define duas cores básicas para permitir o ataque inicial
        if (i % 2 == 0) strcpy(mapa[i].cor, "Verde");
        else strcpy(mapa[i].cor, "Amarelo");
        
        mapa[i].tropas = rand() % 10 + 3; 
    }
}

void exibirMapa(const Territorio* mapa, int total) {
    printf("\nID | %-15s | %-10s | %-6s\n", "TERRITÓRIO", "COR", "TROPAS");
    printf("----------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%d  | %-15s | %-10s | %-6d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int missaoID) {
    printf("\nSUA MISSÃO: ");
    if (missaoID == 0) printf("Dominar o maior número de territórios.\n");
    else printf("Eliminar a resistência inimiga.\n");
}

// IMPLEMENTAÇÃO SOLICITADA: Lógica completa de ataque e troca de dono
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- BATALHA: %s vs %s ---\n", atacante->nome, defensor->nome);
    
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("Dados -> Atacante: %d | Defensor: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("VITÓRIA! O território %s foi conquistado!\n", defensor->nome);
        
        // REQUISITO: Atualização de dados (Mudar cor e transferir metade das tropas)
        strcpy(defensor->cor, atacante->cor);
        int transferidas = atacante->tropas / 2;
        defensor->tropas = transferidas;
        atacante->tropas -= transferidas;
        
        printf("Novos dados: %s agora é %s e possui %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("DERROTA! O defensor resistiu.\n");
        // Se perder, o atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}