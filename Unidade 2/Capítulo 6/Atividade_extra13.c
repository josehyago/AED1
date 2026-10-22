/*
 Capítulo 6 - Central de Algoritmos de ordenação
 Atividade Bônus - Sala de aula - Intercalação de vetores

 - Realize a Atividade 37 sobre Intercalação de vetores
 Atividade 37 — Intercalação e divisão e conquista
 
 Contexto: Em vez de organizar todos os dados de uma vez, uma estratégia pode dividir o conjunto em partes menores, resolvê-las e combinar os resultados. A intercalação é a operação central dessa combinação.
 Descrição detalhada: Implemente uma função que receba dois vetores ordenados e produza um terceiro também ordenado. Em seguida, crie a estrutura recursiva que divide um intervalo em duas metades, ainda que a ordenação completa seja concluída na próxima atividade.
 Requisitos:
 - manter índices independentes para as duas entradas;
 - copiar os elementos restantes quando uma entrada terminar;
 - produzir saída com todos os valores;
 - calcular corretamente o ponto médio;
 - identificar em comentários as etapas dividir, resolver e combinar;
 - contar comparações da intercalação.
*/

#include <stdio.h>

void merge(int v1[], int v2[], int r[], int n1, int n2){
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < n1 && j < n2){
        if (v1[i] < v2[j]){
            r[k] = v1[i];
            i++;
        }
        else {
            r[k] = v2[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        r[k] = v1[i];
        i++;
        k++;
    }
    while (j < n2){
        r[k] = v2[j];
        j++;
        k++;
    }
}

int main(){
    int v1[5] = {1, 5, 7, 11, 15};
    int v2[4] = {2, 4, 6, 8};
    int r[9];

    printf("Vetores Originais:\n");
    
    printf("Vetor 1: ");
    for (int i = 0; i < 5; i++) printf("[%d] ", v1[i]);
    printf("\n");
    
    printf("Vetor 2: ");
    for (int j = 0; j < 4; j++) printf("[%d] ", v2[j]);
    printf("\n");

    merge(v1, v2, r, 5, 4);

    printf("Vetor Ordenado:\n");
    printf("Resultado: ");
    for (int k = 0; k < 9; k++) printf("[%d] ", r[k]);

    return 0;
}