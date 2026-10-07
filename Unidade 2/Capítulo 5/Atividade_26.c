/*
 Capítulo 5 - Laboratório de desempenho, busca e recursividade
 Atividade 26 - Tempo constante e tempo linear

 Contexto: A equipe quer entender como o custo de uma operação muda quando o conjunto de dados cresce. Para isso, o laboratório contabilizará acessos e comparações, em vez de depender apenas do tempo do relógio.
 Descrição detalhada: Crie um vetor e duas funções instrumentadas. A primeira acessará diretamente uma posição válida; a segunda percorrerá todo o vetor para localizar o maior valor. Execute as funções com tamanhos diferentes e compare os contadores produzidos.
 Requisitos:
 - validar o índice do acesso direto;
 - contar a operação constante de forma coerente;
 - percorrer todos os elementos na busca do maior;
 - usar contadores independentes;
 - testar ao menos três tamanhos de entrada;
 - relacionar os resultados a O(1) e O(n).
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

int main(){
    int tamanhos[] = {10, 20, 30};
    int testes = 3;
    int tamanho_anterior = 0;

    srand(time(NULL));
    int *vetor = NULL;

    for (int t = 0; t < testes; t++){
        int tam = tamanhos[t];
        int contadorO1 = 0, contadorOn = 0;

        int *vetortemp = (int *) realloc(vetor, tam * sizeof(int));
        if (vetortemp == NULL) { free(vetor); exit(1); }
        vetor = vetortemp;

        for (int i = tamanho_anterior; i < tam; i++) vetor[i] = rand() % 100;

        int v_direto = acesso_direto(vetor, tam, rand() % tam, &contadorO1);
        int v_maior = busca_maior(vetor, tam, &contadorOn);

        printf("Tamanho: %d | O(1) fez %d operacao | O(n) fez %d comparacoes\n", tam, contadorO1, contadorOn);
        printf("Acesso direto = %d | Busca maior = %d\n\n", v_direto, v_maior);

        tamanho_anterior = tam;
    }

    free(vetor);
    return 0;
}