/*
 Capítulo 5 - Laboratório de desempenho, busca e recursividade
 Atividade 28 - Tempo logarítmico e busca binária

 Contexto: Quando os dados estão ordenados, a procura pode descartar metade do espaço restante a cada tentativa. O laboratório deverá tornar essa redução visível.
 Descrição detalhada: Implemente busca binária iterativa em um vetor ordenado. Em cada passagem, apresente ou registre início, meio e fim, conte comparações e devolva a posição encontrada ou -1. Teste valores presentes e ausentes.
 Requisitos:
 - garantir ou verificar que o vetor usado está ordenado;
 - calcular o meio sem acessar posição inválida;
 - reduzir corretamente o intervalo;
 - terminar quando o intervalo ficar vazio;
 - contabilizar comparações;
 - relacionar a redução à complexidade O(log n).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função acesso direto - O(1)
int acesso_direto(int *vetorO1, int tamanho, int indice, int *contadorO1){
    *contadorO1 = 0;
    (*contadorO1)++;

    if (indice >= 0 && indice < tamanho ){
        return vetorO1[indice];
    }

    return -1;
}

// Função busca do maior - O(n)
int busca_maior(int *vetorOn, int tamanho, int *contadorOn){

    if (tamanho <= 0) return -1;

    int maior = vetorOn[0];
    *contadorOn = 0;

    for(int i = 0; i < tamanho; i++){
        (*contadorOn)++;
        if(vetorOn[i] > maior) maior = vetorOn[i];
    }

    return maior;
}

// Função que busca pares com soma igual ao alvo - O(n²)
int busca_paresSoma(int *vetor, int tamanho, int alvo, int *contadorOn2){
    
    int pares_encontrados = 0;
    *contadorOn2 = 0;

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

// Função de busca binária iterativa - O(log n)
int busca_binaria(int *vetor, int tamanho, int alvo, int *contadorBinario){
    
    int inicio = 0;
    int fim = tamanho - 1;
    *contadorBinario = 0;

    while(inicio <= fim){
        (*contadorBinario)++;

        int meio = inicio + (fim - inicio) / 2;
        
        printf("Tentativa %d | Inicio: %d | Meio: %d (Valor: %d) | Fim: %d\n", *contadorBinario, inicio, meio, vetor[meio], fim);

        if (vetor[meio] == alvo) return meio;

        if (alvo > vetor[meio]) inicio = meio + 1; else fim = meio - 1;
    }
    return -1;
}

int main(){

    int tamanhos[] = {10, 20, 30};
    int testes = 3;
    int tamanho_anterior = 0;
    int alvo = 50;
    int contadorO1, contadorOn, contadorOn2, contadorBinario, contadorBinarioIncorreto;

    srand(time(NULL));
    int *vetor = NULL;
    int *vetor_ordenado = NULL;


    for (int t = 0; t < testes; t++){
        int tam = tamanhos[t];

        int *vetortemp = (int *) realloc(vetor, tam * sizeof(int));
        if (vetortemp == NULL) { free(vetor); exit(1); }
        vetor = vetortemp;

        int *vetor_ordenadotemp = (int *) realloc(vetor_ordenado, tam * sizeof(int));
        if (vetor_ordenadotemp == NULL) { free(vetor_ordenado); exit(1); }
        vetor_ordenado = vetor_ordenadotemp;

        for (int i = tamanho_anterior; i < tam; i++) vetor[i] = rand() % 100;
        for (int j = 0; j < tam; j++) vetor_ordenado[j] = j * 2;
    
        int v_direto = acesso_direto(vetor, tam, rand() % tam, &contadorO1);
        int v_maior = busca_maior(vetor, tam, &contadorOn);
        int v_paresSoma = busca_paresSoma(vetor, tam, alvo, &contadorOn2);

        printf("\nResumo Tamanho: %d\n", tam);
        printf("\nBuscando o valor 16 (Presente)\n");
        int v_buscabinaria = busca_binaria(vetor_ordenado, tam, 16, &contadorBinario);
        printf("\nBuscando o valor 1 (Ausente)\n");
        int v_buscabinariaincorreta = busca_binaria(vetor_ordenado, tam, 1, &contadorBinarioIncorreto);
    
        printf("\nO(1) fez %d operacao | O(n) fez %d comparacoes | O(n2) fez %d comparacoes | O(log n) correto fez %d comparacoes, incorreto fez %d comparacoes\n", contadorO1, contadorOn, contadorOn2, contadorBinario, contadorBinarioIncorreto);
        printf("Acesso direto = %d | Busca maior = %d | Pares com soma = %d | Busca binaria = %d | Busca binaria incorreta = %d\n", v_direto, v_maior, v_paresSoma, v_buscabinaria, v_buscabinariaincorreta);
    
        tamanho_anterior = tam;
    }

    free(vetor);
    free(vetor_ordenado);
    return 0;
}