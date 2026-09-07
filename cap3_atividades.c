// Capítulo 3 — Catalágo dinâmico de personagens
// Atividade 14 - Alocação inicial e redimensionamento do catálogo

// Contexto: O catálogo ainda não possui um tipo completo para os personagens, mas precisa preparar um armazenamento que possa crescer à medida que novos registros forem incluídos.
// Descrição detalhada: Crie a base do programa usando calloc para reservar um vetor inicialmente zerado. Permita aumentar ou reduzir sua capacidade com realloc, sempre preservando o bloco original em caso de erro. Mostre ao usuário a capacidade anterior e a nova.
// Requisitos:
// - reservar a capacidade inicial com calloc;
// - demonstrar que as posições começam zeradas;
// - validar a nova capacidade;
// - usar um ponteiro temporário ao chamar realloc;
// - inicializar as posições acrescentadas;
// - liberar o vetor antes de encerrar.

#include <stdio.h>
#include <stdlib.h>

int main(){
    int capacidade, i, capacidade_nova;
    capacidade = 5;
    int *catalogo = (int *) calloc(capacidade, sizeof(int));

    if(catalogo == NULL){
        printf("Nao ha memoria suficiente");
        exit (1);
    }
    printf("Posicoes zeradas: \n");
    for(i = 0; i < capacidade; i++){
        printf("[%d] ", catalogo[i]);
    }
    printf("\n");

    printf("Digite a nova capacidade: ");
    scanf("%d", &capacidade_nova);
    if(capacidade_nova <= 0){
        printf("Capacidade invalida.");
        exit(1);
    }else{
        int *catalogo_temporario = (int *) realloc(catalogo, capacidade_nova * sizeof(int));
        if(catalogo_temporario == NULL){
            printf("Nao ha memoria suficiente");
            exit (1);
        }else{
            catalogo = catalogo_temporario;
            if(capacidade_nova > capacidade){
                for(i = capacidade; i < capacidade_nova; i++){
                    catalogo[i] = 0;
                }
            }
            printf("Capacidade Anterior = %d | Capacidade Nova = %d\n", capacidade, capacidade_nova);
            for(i = 0; i < capacidade_nova; i++){
            printf("[%d] ", catalogo[i]);
            }
        }
    }
    free(catalogo);
    catalogo = NULL;

    return 0;
}