/*
 Capítulo 6 - Central de Algoritmos de ordenação
 Atividade - Pontos Extras

 - Realize a Atividade 39 sobre QuickSort
 Atividade 39 — Partição e Quick Sort
 
 Contexto: Outra estratégia de divisão organiza elementos em torno de um pivô. Para compreender o processo, a central deverá implementar primeiro uma versão com memória auxiliar e depois uma versão no próprio vetor.
 Descrição detalhada: Crie duas funções de partição e demonstre seus resultados isoladamente. Use a partição in-place para implementar o Quick Sort recursivo. Mostre a posição final do pivô e teste casos com valores repetidos.
 Requisitos:
 - separar valores segundo uma regra clara em relação ao pivô;
 - preservar todos os elementos na partição auxiliar;
 - manter índices válidos na versão in-place;
 - devolver a posição final do pivô;
 - aplicar Quick Sort somente aos subintervalos necessários;
 - contar comparações e trocas.
*/

#include <stdio.h>

// Função Auxiliar para imprimir o vetor
void imprimirVetor(int v[], int tamanho) {
    printf("[ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", v[i]);
    }
    printf("]\n");
}

// Partição com memória auxiliar
int particaoComMemoriaAuxiliar(int v[], int left, int right, int *compara, int *trocas) {
    int pivo = v[right];
    int aux[right - left + 1];
    int idx = 0;

    // Copia elementos menores que o pivô para o vetor auxiliar
    for (int i = left; i <= right; i++) {
        if (i != right) {
            (*compara)++;
            if (v[i] < pivo) {
                aux[idx++] = v[i];
            }
        }
    }

    int pos_pivo = left + idx;
    aux[idx++] = pivo; // Insere o pivô na posição correta

    // Copia elementos maiores ou iguais ao pivô para o vetor auxiliar
    for (int i = left; i <= right; i++) {
        if (i != right) {
            (*compara)++;
            if (v[i] >= pivo) {
                aux[idx++] = v[i];
            }
        }
    }

    // Copia de volta para o vetor original
    for (int i = 0; i <= right - left; i++) {
        v[left + i] = aux[i];
        (*trocas)++; // Conta a movimentação de retorno
    }

    return pos_pivo;
}

// Partição in-place (no próprio vetor)
int particaoInPlace(int v[], int left, int right, int *compara, int *trocas) {
    int pivo = v[right];
    int j = left;
    
    for (int i = left; i < right; i++) {
        (*compara)++;
        if (v[i] < pivo) {
            (*trocas)++;
            int temp = v[j];
            v[j] = v[i];
            v[i] = temp;
            j++;
        }
    }
    
    (*trocas)++;
    int temp = v[j];
    v[j] = v[right];
    v[right] = temp;
    
    return j;
}

// QuickSort recursivo utilizando a partição in-place
void quickSort(int v[], int left, int right, int *compara, int *trocas) {
    if (left < right) {
        int index = particaoInPlace(v, left, right, compara, trocas);
        quickSort(v, left, index - 1, compara, trocas);
        quickSort(v, index + 1, right, compara, trocas);
    }
}

int main() {
    // Teste 1: Partição com memória auxiliar isolada
    int v1[] = {5, 3, 9, 67, 10, 4};
    int comp_aux = 0, trocas_aux = 0;
    
    printf("--- Teste 1: Particao com Memoria Auxiliar ---\n");
    printf("Vetor original: ");
    imprimirVetor(v1, 6);
    
    int pos_pivo_aux = particaoComMemoriaAuxiliar(v1, 0, 5, &comp_aux, &trocas_aux);
    
    printf("Vetor apos particao: ");
    imprimirVetor(v1, 6);
    printf("Posicao final do pivo: %d (Valor: %d)\n", pos_pivo_aux, v1[pos_pivo_aux]);
    printf("Comparacoes: %d | Trocas/Movimentacoes: %d\n\n", comp_aux, trocas_aux);

    // Teste 2: QuickSort completo com valores repetidos (In-Place)
    int v2[] = {8, 3, 5, 3, 9, 1, 5, 3, 67, 10, 4};
    int tam2 = sizeof(v2) / sizeof(v2[0]);
    int comp_ip = 0, trocas_ip = 0;
    
    printf("--- Teste 2: QuickSort In-Place com Valores Repetidos ---\n");
    printf("Vetor original: ");
    imprimirVetor(v2, tam2);
    
    quickSort(v2, 0, tam2 - 1, &comp_ip, &trocas_ip);
    
    printf("Vetor ordenado: ");
    imprimirVetor(v2, tam2);
    printf("Total de comparacoes: %d\n", comp_ip);
    printf("Total de trocas: %d\n", trocas_ip);

    return 0;
}