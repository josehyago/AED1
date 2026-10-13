/*
 Capítulo 6 - Central de Algoritmos de ordenação
 Atividade 34 — Insertion Sort de estruturas
 
 Contexto: O catálogo de jogadores também precisa ser exibido em ordem alfabética. Como cada registro contém vários campos, toda a estrutura deve acompanhar o nome durante os deslocamentos.
 Descrição detalhada: Adapte o Insertion Sort para ordenar estruturas por nome com strcmp. Teste registros com nomes repetidos e defina um desempate consistente. Confira que identificador e pontuação continuam associados ao jogador correto após a ordenação.
 Requisitos:
 - usar uma estrutura temporária completa;
 - comparar nomes com strcmp;
 - definir critério secundário para nomes iguais;
 - mover todos os campos juntos;
 - exibir os registros antes e depois;
 - incluir a nova opção na central.
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

// Funções de Insertion Sort:

void insertionsort_numerico(int vetor[], int n, int *comparacoes, int *deslocamentos){
    *comparacoes = 0;
    *deslocamentos = 0;

    // Começamos do segundo elemento (índice 1), assumindo que o índice 0 já é um prefixo ordenado.
    for(int i = 1; i < n; i++){
        int temp = vetor[i];
        int j = i - 1;

        // Move os elementos da parte ordenada que são maiores que temp para a direita.
        while(j >= 0){ // Respeita o limite inferior (j >= 0).
            (*comparacoes)++;

            if (vetor[j] > temp){
                vetor[j + 1] = vetor[j]; // Desloca o elemento para a frente.
                (*deslocamentos)++;
                j--;
            } else break; // Encontrou a posição correta, interrompe a busca.
        }
        // Insere temp na posição correta encontrada
        vetor[j + 1] = temp;
    }
}

void insertionsort_jogador(Jogador vetor[], int n, int *comparacoes, int *deslocamentos){
    *comparacoes = 0;
    *deslocamentos = 0;

    for(int i = 1; i < n; i++){
        Jogador temp = vetor[i];
        int j = i - 1;

        while(j >= 0){
            (*comparacoes)++;

            int comparacao_nomes = strcmp(vetor[j].nome, temp.nome);

            // Critério Principal: Nome maior (vem depois no alfabeto) é deslocado.
            if (comparacao_nomes > 0){
                vetor[j + 1] = vetor[j];
                (*deslocamentos)++;
                j--;
            }

            // Critério de Desempate: Se os nomes forem iguais, desempata por ID (ex: menor ID).
            else if (comparacao_nomes == 0){
                if (vetor[j].id > temp.id){
                    vetor[j + 1] = vetor[j];
                    (*deslocamentos)++;
                    j--;
                } else { break; }
            } else { break; }
        }
        vetor[j + 1] = temp;
    }
}

int main(){
    // Selection Sort Númerico:
    int ssorigem_numero[] = {42, 15, 8, 42, 23, 4, 16, 99, 15};
    int ssn_numero = sizeof(ssorigem_numero) / sizeof(ssorigem_numero[0]);
    int ssdestino_numero[ssn_numero];
    int sscomparacoes_numero, sstrocas_numero;

    // Preserva a entrada original.
    copia_vetornumerico(ssorigem_numero, ssdestino_numero, ssn_numero);

    printf("\n--- Selection Sort Numerico ---\n");
    printf("Vetor Original: ");
    for (int i = 0; i < ssn_numero; i++) printf("[%d] ", ssorigem_numero[i]);
    printf("\n");

    // Ordena os Números.
    selectionsort_numerico(ssdestino_numero, ssn_numero, &sscomparacoes_numero, &sstrocas_numero);

    printf("Vetor Ordenado: ");
    for (int i = 0; i < ssn_numero; i++) printf("[%d] ", ssdestino_numero[i]);
    printf("\n");
    printf("Metricas -> Comparacoes: %d | Trocas: %d\n\n", sscomparacoes_numero, sstrocas_numero);

    // Selection Sort Struct:
    Jogador ssorigem_jogador[] = {
        {101, "Carlos", 85},
        {102, "Ana", 92},
        {103, "Bruno", 85},
        {104, "Beatriz", 78},
        {105, "Daniel", 92}
    };
    int ssn_jogador = sizeof(ssorigem_jogador) / sizeof(ssorigem_jogador[0]);
    Jogador ssdestino_jogador[ssn_jogador];
    int sscomparacoes_jogador, sstrocas_jogador;

    // Preserva a entrada original.
    copia_vetorstruct(ssorigem_jogador, ssdestino_jogador, ssn_jogador);

    printf("--- Selection Sort de Jogadores (Pontuacao + Desempate por Nome) ---\n");
    printf("Lista Original:\n");
    for (int i = 0; i < ssn_jogador; i++) printf("  ID: %d | Nome: %s | Pontuacao: %d\n", ssorigem_jogador[i].id, ssorigem_jogador[i].nome, ssorigem_jogador[i].pontuacao);

    // Ordena a Struct.
    selectionsort_jogador(ssdestino_jogador, ssn_jogador, &sscomparacoes_jogador, &sstrocas_jogador);

    printf("\nLista Ordenada:\n");
    for (int i = 0; i < ssn_jogador; i++) printf("  ID: %d | Nome: %s | Pontuacao: %d\n", ssdestino_jogador[i].id, ssdestino_jogador[i].nome, ssdestino_jogador[i].pontuacao);
    printf("Metricas -> Comparacoes: %d | Trocas: %d\n", sscomparacoes_jogador, sstrocas_jogador);

    // Insertion Sort Numérico:
    int isorigem_numero[] = {42, 15, 8, 42, 23, 4, 16, 99, 15};
    int isn_numero = sizeof(isorigem_numero) / sizeof(isorigem_numero[0]);
    int isdestino_numero[isn_numero];
    int iscomparacoes_numero, isdeslocamentos_numero;

    copia_vetornumerico(isorigem_numero, isdestino_numero, isn_numero);

    printf("\n--- Insertion Sort Numerico ---\n");
    printf("Vetor Original: ");
    for (int i = 0; i < isn_numero; i++) printf("[%d] ", isorigem_numero[i]);
    printf("\n");

    insertionsort_numerico(isdestino_numero, isn_numero, &iscomparacoes_numero, &isdeslocamentos_numero);

    printf("Vetor Ordenado: ");
    for (int i = 0; i < isn_numero; i++) printf("[%d] ", isdestino_numero[i]);
    printf("\n");
    printf("Metricas -> Comparacoes: %d | Deslocamentos: %d\n\n", iscomparacoes_numero, isdeslocamentos_numero);

    // Insertion Sort Struct:
    Jogador isorigem_jogador[] = {
        {101, "Carlos", 85},
        {102, "Ana", 92},
        {103, "Bruno", 85},
        {104, "Beatriz", 78},
        {105, "Daniel", 92},
        {106, "Ana", 100}
    };
    int isn_jogador = sizeof(isorigem_jogador) / sizeof(isorigem_jogador[0]);
    Jogador isdestino_jogador[isn_jogador];
    int iscomparacoes_jogador, isdeslocamentos_jogador;

    copia_vetorstruct(isorigem_jogador, isdestino_jogador, isn_jogador);

    printf("--- Insertion Sort de Jogadores por Nome (Desempate por ID) ---\n");
    printf("Lista Original:\n");
    for (int i = 0; i < isn_jogador; i++) printf("  ID: %d | Nome: %-10s | Pontuacao: %d\n", isorigem_jogador[i].id, isorigem_jogador[i].nome, isorigem_jogador[i].pontuacao);

    insertionsort_jogador(isdestino_jogador, isn_jogador, &iscomparacoes_jogador, &isdeslocamentos_jogador);

    printf("\nLista Ordenada:\n");
    for (int i = 0; i < isn_jogador; i++) printf("  ID: %d | Nome: %-10s | Pontuacao: %d\n", isdestino_jogador[i].id, isdestino_jogador[i].nome, isdestino_jogador[i].pontuacao);
    printf("Metricas -> Comparacoes: %d | Deslocamentos: %d\n", iscomparacoes_jogador, isdeslocamentos_jogador);

    return 0;
}