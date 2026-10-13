/*
 Capítulo 6 - Central de Algoritmos de ordenação
 Atividade 32 — Selection Sort de números e estruturas
 
 Contexto: Um organizador de campeonato precisa ordenar pontuações e registros de jogadores. A primeira estratégia localizará o menor elemento da parte ainda não organizada e o colocará na posição correta.
 Descrição detalhada: Crie a base da central com vetores originais e cópias de trabalho. Implemente primeiro uma função que encontre o menor valor a partir de uma posição e use-a no Selection Sort. Depois, adapte o algoritmo para estruturas de jogadores com desempate.
 Requisitos:
 - preservar a entrada original para comparações futuras;
 - ordenar um vetor numérico;
 - ordenar jogadores por pontuação;
 - aplicar desempate por nome ou identificador;
 - trocar a estrutura inteira;
 - contar comparações e trocas.
*/

#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char nome[100];
    int pontuacao;
} Jogador;

// Funções para preservar a entrada original:

void copia_vetornumerico(int origem[], int destino[], int n){ for (int i = 0; i < n; i++) destino[i] = origem[i]; }
void copia_vetorstruct(Jogador origem[], Jogador destino[], int n){ for(int i = 0; i < n; i++) destino[i] = origem [i]; }

//Funções de Selection Sort:

void selectionsort_numerico(int vetor[], int n, int *comparacoes, int *trocas){
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < n - 1; i++){
        int imenor = i;
        for(int j = i + 1; j < n; j++){
            (*comparacoes)++;
            if(vetor[j] < vetor[imenor]) imenor = j;
        }
        // Faz a troca apenas se necessário.
        if (imenor != i){
            int temp = vetor[i];
            vetor[i] = vetor[imenor];
            vetor[imenor] = temp;
            (*trocas)++;
        }
    }
}

void selectionsort_jogador(Jogador vetor[], int n, int *comparacoes, int *trocas){
    *comparacoes = 0;
    *trocas = 0;

    for(int i = 0; i < n - 1; i++){
        int imenor = i;
        for(int j = i + 1; j < n; j++){
            (*comparacoes)++;
            // Critério principal: maior pontuação.
            if(vetor[j].pontuacao > vetor[imenor].pontuacao) imenor = j;
            else if(vetor[j].pontuacao == vetor[imenor].pontuacao){
                // Critério de desempate por nome (ordem alfabética)
                if(strcmp(vetor[j].nome, vetor[imenor].nome) < 0) imenor = j;
            }
        }
        if (imenor != i){
            Jogador temp = vetor[i];
            vetor[i] = vetor[imenor];
            vetor[imenor] = temp;
            (*trocas)++;
        }
    }
}

int main(){
    // Selection Sort Númerico:
    int origem_numero[] = {42, 15, 8, 42, 23, 4, 16, 99, 15};
    int n_numero = sizeof(origem_numero) / sizeof(origem_numero[0]);
    int destino_numero[n_numero];
    int comparacoes_numero, trocas_numero;

    // Preserva a entrada original.
    copia_vetornumerico(origem_numero, destino_numero, n_numero);

    printf("\n--- Selection Sort Numerico ---\n");
    printf("Vetor Original: ");
    for (int i = 0; i < n_numero; i++) printf("[%d] ", origem_numero[i]);
    printf("\n");

    // Ordena os Números.
    selectionsort_numerico(destino_numero, n_numero, &comparacoes_numero, &trocas_numero);

    printf("Vetor Ordenado: ");
    for (int i = 0; i < n_numero; i++) printf("[%d] ", destino_numero[i]);
    printf("\n");
    printf("Metricas -> Comparacoes: %d | Trocas: %d\n\n", comparacoes_numero, trocas_numero);

    // Selection Sort Struct:
    Jogador origem_jogador[] = {
        {101, "Carlos", 85},
        {102, "Ana", 92},
        {103, "Bruno", 85},
        {104, "Beatriz", 78},
        {105, "Daniel", 92}
    };
    int n_jogador = sizeof(origem_jogador) / sizeof(origem_jogador[0]);
    Jogador destino_jogador[n_jogador];
    int comparacoes_jogador, trocas_jogador;

    // Preserva a entrada original.
    copia_vetorstruct(origem_jogador, destino_jogador, n_jogador);

    printf("--- Selection Sort de Jogadores (Pontuacao + Desempate por Nome) ---\n");
    printf("Lista Original:\n");
    for (int i = 0; i < n_jogador; i++) printf("  ID: %d | Nome: %s | Pontuacao: %d\n", origem_jogador[i].id, origem_jogador[i].nome, origem_jogador[i].pontuacao);

    // Ordena a Struct.
    selectionsort_jogador(destino_jogador, n_jogador, &comparacoes_jogador, &trocas_jogador);

    printf("\nLista Ordenada:\n");
    for (int i = 0; i < n_jogador; i++) printf("  ID: %d | Nome: %s | Pontuacao: %d\n", destino_jogador[i].id, destino_jogador[i].nome, destino_jogador[i].pontuacao);
    printf("Metricas -> Comparacoes: %d | Trocas: %d\n", comparacoes_jogador, trocas_jogador);

    return 0;
}