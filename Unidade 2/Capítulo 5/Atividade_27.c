/*
 Capítulo 5 - Laboratório de desempenho, busca e recursividade
 Atividade 27 - Tempo quadrático

 Contexto: O laboratório precisa analisar combinações entre pares de elementos. Essa tarefa cresce mais rapidamente porque, para cada posição, várias outras posições precisam ser examinadas.
 Descrição detalhada: Adicione uma função com dois laços aninhados, como encontrar pares cuja soma seja igual a um alvo. Instrumente as comparações e evite apresentar o mesmo par duas vezes. Compare a evolução do contador com as operações da atividade anterior.
 Requisitos:
 - receber vetor, tamanho e valor-alvo;
 - examinar os pares válidos sem acessar limites indevidos;
 - evitar pares duplicados e a combinação de uma posição consigo mesma;
 - contar comparações do núcleo do algoritmo;
 - testar entradas crescentes;
 - identificar o comportamento aproximado O(n²).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função acesso direto O(1)
int acesso_direto(int *vetorO1, int tamanho, int indice, int *contadorO1){
    
    (*contadorO1)++;

    if (indice >= 0 && indice < tamanho ){
        return vetorO1[indice];
    }

    return -1;
}

// Função busca do maior O(n)
int busca_maior(int *vetorOn, int tamanho, int *contadorOn){

    if (tamanho <= 0) return -1;

    int maior = vetorOn[0];

    for(int i = 0; i < tamanho; i++){
        (*contadorOn)++;
        if(vetorOn[i] > maior) maior = vetorOn[i];
    }

    return maior;
}

int busca_paresSoma(int *vetor, int tamanho, int alvo, int *contadorOn2){
    int pares_encontrados = 0;

    for(int i = 0; i < tamanho - 1; i++){
        for(int j = i + 1; j < tamanho; j++){
            (*contadorOn2)++;
            if(vetor[i] + vetor[j] == alvo){
                pares_encontrados++;
            }
        }
    }
    return pares_encontrados;
}

int main(){
    int tamanhos[] = {10, 20, 30};
    int testes = 3;
    int tamanho_anterior = 0;
    int alvo = 50;

    srand(time(NULL));
    int *vetor = NULL;

    for (int t = 0; t < testes; t++){
        int tam = tamanhos[t];
        int contadorO1 = 0, contadorOn = 0, contadorOn2 = 0;

        int *vetortemp = (int *) realloc(vetor, tam * sizeof(int));
        if (vetortemp == NULL) { free(vetor); exit(1); }
        vetor = vetortemp;

        for (int i = tamanho_anterior; i < tam; i++) vetor[i] = rand() % 100;

        int v_direto = acesso_direto(vetor, tam, rand() % tam, &contadorO1);
        int v_maior = busca_maior(vetor, tam, &contadorOn);
        int v_paresSoma = busca_paresSoma(vetor, tam, alvo, &contadorOn2);

        printf("Tamanho: %d | O(1) fez %d operacao | O(n) fez %d comparacoes | O(n2) fez %d comparacoes\n", tam, contadorO1, contadorOn, contadorOn2);
        printf("Acesso direto = %d | Busca maior = %d | Pares com soma = %d\n\n", v_direto, v_maior, v_paresSoma);

        tamanho_anterior = tam;
    }

    free(vetor);
    return 0;
}