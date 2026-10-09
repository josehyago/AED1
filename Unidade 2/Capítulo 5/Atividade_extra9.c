/*
 Capítulo 5 - Laboratório de desempenho, busca e recursividade
 Atividade - Pontos Extras

 - Realizar Atividade 30 - Recursividade
 Atividade 30 - Fundamentos de recursividade

 Contexto: Algumas soluções podem ser expressas como uma versão menor do mesmo problema. Antes de usar recursão em buscas e ordenação, o laboratório precisa demonstrar claramente caso-base, progresso e retorno das chamadas.
 Descrição detalhada: Acrescente uma função recursiva numérica simples e outra que percorra o vetor, como soma ou busca. Registre a profundidade ou quantidade de chamadas e compare o resultado com uma solução iterativa equivalente.
 Requisitos:
 - definir caso-base alcançável;
 - reduzir o problema a cada chamada;
 - evitar índices negativos ou além do vetor;
 - somar ou processar todos os elementos esperados;
 - contar chamadas recursivas;
 - comparar resultado e custo com a versão iterativa.
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

// Função de busca linear - O(n)
int busca_linear(int *vetor, int tamanho, int alvo, int *contadorLinear){
    
    *contadorLinear = 0;

    for(int i = 0; i < tamanho; i++){
        (*contadorLinear)++;

        if(vetor[i] == alvo) return i;
    }
    return -1;
}

// Fatorial Iterativo (Comum) 
int fatorial_iterativo(int n, int *contadorFatorial_iterativo){
    
    *contadorFatorial_iterativo = 0;
    int resultado = 1;
    for(int i = n; i >= 1; i--){
        (*contadorFatorial_iterativo)++;
        resultado *= i;
    }
    return resultado;
}

// Fatorial Recursivo
int fatorial_recursivo(int n, int *contadorFatorial_recursivo){

    (*contadorFatorial_recursivo)++; // Conta a profundidade da chamada.

    // Caso-base: Se n for 1 ou menor, paramos a recursão.
    if(n <= 1) return 1;

    // Progresso: Chama a si mesma, mas com (n - 1).
    return n * fatorial_recursivo(n - 1, contadorFatorial_recursivo);
}

// Soma Vetor Iterativa (Comum)
int somavetor_iterativa(int *vetor, int tamanho, int *contadorsomavetor_iterativa){

    *contadorsomavetor_iterativa = 0;
    int soma = 0;
    for(int i = 0; i < tamanho; i++){
        (*contadorsomavetor_iterativa)++;
        soma += vetor[i];
    }
    return soma;
}

// Soma Vetor Recursiva
int somavetor_recursiva(int *vetor, int tamanho, int *contadorsomavetor_recursiva){

    (*contadorsomavetor_recursiva)++; // Conta a profundidade.

    // Caso-base: O tamanho reduziu até 0. Retornamos 0 (não há mais o que somar).
    // Isso também evita acessar o índice -1 e dar erro de memória.
    if(tamanho <= 0) return 0;

    // Progresso: Pega o elemento atual (vetor[tamanho - 1]) e soma com o restante.
    return vetor[tamanho - 1] + somavetor_recursiva(vetor, tamanho - 1, contadorsomavetor_recursiva);
}

int main(){

    int tamanhos[] = {10, 20, 30};
    int testes = 3;
    int tamanho_anterior = 0;
    int alvo = 50;
    int nfat = 2;
    int contadorO1, contadorOn, contadorOn2, contadorBinario, contadorLinear, contadorFatorial_iterativo, contadorFatorial_recursivo, contadorsomavetor_iterativa, contadorsomavetor_recursiva;

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

        printf("\n--- Atividades 26 e 27 [Tempo Constante, Linear e Quadratico]: ---\n");
        printf("\nO(1) fez %d operacao | O(n) fez %d comparacoes | O(n2) fez %d comparacoes\n", contadorO1, contadorOn, contadorOn2);
        printf("Acesso direto = %d | Busca maior = %d | Pares com soma = %d\n", v_direto, v_maior, v_paresSoma);
        printf("\n===========================================================================\n");

        printf("\n--- Atividades 28 e 29 [Tempo Logaritmico, Busca Binaria e Linear]: ---\n");
        printf("\nComparacao Busca binaria e Busca linear\n");
        printf("\nVetor ordenado:\n");

        printf("\nTeste Inicio (Alvo = vetor_ordenado[0])\n");   
        printf("Resumo da Busca Binaria:\n");       
        int buscabinaria = busca_binaria(vetor_ordenado, tam, vetor_ordenado[0], &contadorBinario);
        int buscalinear = busca_linear(vetor_ordenado, tam, vetor_ordenado[0], &contadorLinear);
        printf("Comparacao das duas:\n");
        printf("INICIO (Alvo: 0)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", contadorLinear, contadorBinario);
        
        printf("\nTeste Meio (Alvo = vetor_ordenado[tam/2])\n");
        printf("Resumo da Busca Binaria:\n");        
        buscabinaria = busca_binaria(vetor_ordenado, tam, vetor_ordenado[tam/2], &contadorBinario);
        buscalinear = busca_linear(vetor_ordenado, tam, vetor_ordenado[tam/2], &contadorLinear);
        printf("Comparacao das duas:\n");
        printf("MEIO (Alvo: tam/2)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", contadorLinear, contadorBinario);

        printf("\nTeste Fim (Alvo = vetor_ordenado[tam-1])\n");
        printf("Resumo da Busca Binaria:\n");        
        buscabinaria = busca_binaria(vetor_ordenado, tam, vetor_ordenado[tam-1], &contadorBinario);
        buscalinear = busca_linear(vetor_ordenado, tam, vetor_ordenado[tam-1], &contadorLinear);
        printf("Comparacao das duas:\n");
        printf("FIM (Alvo: tam-1)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", contadorLinear, contadorBinario);

        printf("\nTeste Ausente (Alvo = 1)\n");
        printf("Resumo da Busca Binaria:\n");        
        buscabinaria = busca_binaria(vetor_ordenado, tam, 1, &contadorBinario);
        buscalinear = busca_linear(vetor_ordenado, tam, 1, &contadorLinear);
        printf("Comparacao das duas:\n");
        printf("AUSENTE (Alvo: 1)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", contadorLinear, contadorBinario);

        printf("\nVetor desordenado:\n");
        printf("\nPre-condicoes:\n");
        printf("- Busca Binaria: Exige vetor ordenado.\n");
        printf("- Busca Linear: Nao exige ordenacao.\n");
 
        buscalinear = busca_linear(vetor, tam, vetor[tam-1], &contadorLinear);

        printf("Buscando %d no vetor baguncado:\n", vetor[tam-1]);
        printf("Linear encontrou no indice %d com %d comparacoes.\n", buscalinear, contadorLinear);
        printf("A Busca Binaria nao pode ser aplicada aqui porque o resultado nao seria confiavel.\n");

        /*printf("\nBuscando o valor 16 (Presente)\n");
        int v_buscabinaria = busca_binaria(vetor_ordenado, tam, 16, &contadorBinario);
        printf("\nBuscando o valor 1 (Ausente)\n");
        int v_buscabinariaincorreta = busca_binaria(vetor_ordenado, tam, 1, &contadorBinarioIncorreto);*/
    
        printf("\n--- Atividade 30 [Fundamentos de Recursividade]: ---\n");

        contadorFatorial_recursivo = 0;

        int fatorialiterativo = fatorial_iterativo(nfat, &contadorFatorial_iterativo);
        int fatorialrecursivo = fatorial_recursivo(nfat, &contadorFatorial_recursivo);

        printf("\n- FATORIAL DE %d:\n", nfat);
        printf("  Iterativo: Resultado = %d | Custo (lacos) = %d\n", fatorialiterativo, contadorFatorial_iterativo);
        printf("  Recursivo: Resultado = %d | Custo (pilha) = %d\n", fatorialrecursivo, contadorFatorial_recursivo);

        nfat++;

        contadorsomavetor_recursiva = 0;

        int somavetoriterativa = somavetor_iterativa(vetor_ordenado, tam, &contadorsomavetor_iterativa);
        int somavetorrecursiva = somavetor_recursiva(vetor_ordenado, tam, &contadorsomavetor_recursiva);

        printf("\n- SOMA DO VETOR (Tamanho %d):\n", tam);
        printf("  Iterativa: Soma = %d | Custo (lacos) = %d\n", somavetoriterativa, contadorsomavetor_iterativa);
        printf("  Recursiva: Soma = %d | Custo (pilha) = %d\n", somavetorrecursiva, contadorsomavetor_recursiva);
    
        tamanho_anterior = tam;
    }

    free(vetor);
    free(vetor_ordenado);
    return 0;
}