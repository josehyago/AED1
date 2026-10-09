/*
 Capítulo 5 - Laboratório de desempenho, busca e recursividade
 Atividade 31 - Múltiplas chamadas e busca binária recursiva

 Contexto: Certos problemas geram mais de um subproblema por chamada, enquanto outros escolhem apenas uma metade. A comparação ajuda a entender por que funções recursivas diferentes podem apresentar custos muito distintos.
 Descrição detalhada: Implemente um exemplo ramificado, como Fibonacci ingênuo com entrada limitada, e uma busca binária recursiva. Conte as chamadas de ambas e explique o papel dos casos-base. Integre todas as experiências em um menu.
 Requisitos:
 - limitar entradas do exemplo ramificado para evitar execução excessiva;
 - possuir casos-base corretos;
 - passar início e fim na busca binária recursiva;
 - retornar posição ou -1;
 - contar e comparar chamadas;
 - manter disponíveis todos os experimentos anteriores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int acesso_direto(int *vetorO1, int tamanho, int indice, int *contadorO1);
int busca_maior(int *vetorOn, int tamanho, int *contadorOn);
int busca_paresSoma(int *vetor, int tamanho, int alvo, int *contadorOn2);
int busca_binaria(int *vetor, int tamanho, int alvo, int *contadorBinario);
int busca_linear(int *vetor, int tamanho, int alvo, int *contadorLinear);
int fatorial_iterativo(int n, int *contadorFatorial_iterativo);
int fatorial_recursivo(int n, int *contadorFatorial_recursivo);
int somavetor_iterativa(int *vetor, int tamanho, int *contadorsomavetor_iterativa);
int somavetor_recursiva(int *vetor, int tamanho, int *contadorsomavetor_recursiva);
int fibonacci(int n, int *contadorFibonacci);
int busca_binaria_recursiva(int *vetor, int inicio, int fim, int alvo, int *contadorBinario_recursivo);
void menu();

int main(){
    int opcao;
    int tam = 30;

    srand(time(NULL));

    int *vetor = (int *) malloc(tam * sizeof(int));
    int *vetor_ordenado = (int *) malloc(tam * sizeof(int));

    if (vetor == NULL || vetor_ordenado == NULL){
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    for (int i = 0; i < tam; i++){ 
        vetor[i] = rand() % 100;
        vetor_ordenado[i] = i;
    }

    do{
        menu();
        scanf("%d", &opcao);

        switch(opcao){
            case 1:{ 
            int contadorO1, contadorOn, contadorOn2;
            int alvo = rand() % tam;

            int v_direto = acesso_direto(vetor, tam, alvo, &contadorO1);
            int v_maior = busca_maior(vetor, tam, &contadorOn);
            int v_paresSoma = busca_paresSoma(vetor, tam, alvo, &contadorOn2);

            printf("\n--- Atividades 26 e 27 [Tempo Constante, Linear e Quadratico] ---\n");
            printf("Tamanho do vetor: %d\n", tam);
            printf("O(1) fez %d operacao | O(n) fez %d comparacoes | O(n2) fez %d comparacoes\n", contadorO1, contadorOn, contadorOn2);
            printf("Acesso direto de %d = indice[%d] | Maior valor = %d | Pares com soma %d = %d\n", alvo, v_direto, v_maior, alvo, v_paresSoma);
            break;
            }

            case 2:{
            int contadorBinario, contadorLinear;
            
            printf("\n--- Atividades 28 e 29 [Busca Binaria e Linear] ---\n");
            printf("\nVetor ordenado:\n");

            printf("\nTeste Inicio (Alvo = 0)\n");   
            printf("Resumo da Busca Binaria:\n");
            int buscabinaria = busca_binaria(vetor_ordenado, tam, vetor_ordenado[0], &contadorBinario);
            int buscalinear = busca_linear(vetor_ordenado, tam, vetor_ordenado[0], &contadorLinear);
            printf("Comparacao das duas:\n");
            printf("INICIO (Alvo: 0)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", contadorLinear, contadorBinario);
        
            printf("\nTeste Meio (Alvo = vetor_ordenado[tam/2] | %d)\n", vetor_ordenado[tam/2]);
            printf("Resumo da Busca Binaria:\n");
            buscabinaria = busca_binaria(vetor_ordenado, tam, vetor_ordenado[tam/2], &contadorBinario);
            buscalinear = busca_linear(vetor_ordenado, tam, vetor_ordenado[tam/2], &contadorLinear);
            printf("Comparacao das duas:\n");
            printf("MEIO (Alvo: %d)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", vetor_ordenado[tam/2], contadorLinear, contadorBinario);

            printf("\nTeste Fim (Alvo = vetor_ordenado[tam-1] | %d)\n", vetor_ordenado[tam-1]);
            printf("Resumo da Busca Binaria:\n");        
            buscabinaria = busca_binaria(vetor_ordenado, tam, vetor_ordenado[tam-1], &contadorBinario);
            buscalinear = busca_linear(vetor_ordenado, tam, vetor_ordenado[tam-1], &contadorLinear);
            printf("Comparacao das duas:\n");
            printf("FIM (Alvo: %d)  | Linear: %d comparacoes. | Binaria: %d comparacoes.\n", vetor_ordenado[tam-1], contadorLinear, contadorBinario);

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
            break;
            }
            case 3:{
                int contadorFatorial_iterativo, contadorFatorial_recursivo = 0, contadorsomavetor_iterativa, contadorsomavetor_recursiva = 0;
                int nfat = 5;

                printf("\n--- Atividade 30 [Fundamentos de Recursividade] ---\n");

                int fatorialiterativo = fatorial_iterativo(nfat, &contadorFatorial_iterativo);
                int fatorialrecursivo = fatorial_recursivo(nfat, &contadorFatorial_recursivo);

                printf("FATORIAL DE %d:\n", nfat);
                printf("  Iterativo: Resultado = %d | Custo (lacos) = %d\n", fatorialiterativo, contadorFatorial_iterativo);
                printf("  Recursivo: Resultado = %d | Custo (pilha) = %d\n", fatorialrecursivo, contadorFatorial_recursivo);

                int somavetoriterativa = somavetor_iterativa(vetor_ordenado, tam, &contadorsomavetor_iterativa);
                int somavetorrecursiva = somavetor_recursiva(vetor_ordenado, tam, &contadorsomavetor_recursiva);

                printf("\nSOMA DO VETOR (Tamanho %d):\n", tam);
                printf("  Iterativa: Soma = %d | Custo (lacos) = %d\n", somavetoriterativa, contadorsomavetor_iterativa);
                printf("  Recursiva: Soma = %d | Custo (pilha) = %d\n", somavetorrecursiva, contadorsomavetor_recursiva);
                break;
            }
            case 4:{
                int nfib, contadorFibonacci = 0;
                int alvoBinario, contadorBinario_recursivo = 0;
                
                printf("\n--- Atividade 31 [Recursao Ramificada e Busca Binaria Recursiva] ---\n");
                
                // Teste do Fibonacci (Ramificado)
                printf("Digite um valor para calcular o Fibonacci (limite sugerido <= 30): ");
                scanf("%d", &nfib);
                
                // Limite de segurança para não travar o PC
                if (nfib > 30){
                    printf("Valor muito alto! Ajustando para 30 por seguranca.\n");
                    nfib = 30;
                }
                
                int v_fibonacci = fibonacci(nfib, &contadorFibonacci);

                printf("\nFibonacci de %d = %d\n", nfib, v_fibonacci);
                printf("- O caso-base impediu que virasse um laco infinito.\n");
                printf("- Total de chamadas recursivas (ramificadas): %d\n", contadorFibonacci);

                // Teste da Busca Binária Recursiva
                printf("\nDigite um valor para buscar no vetor ORDENADO (de 0 a 29): ");
                scanf("%d", &alvoBinario);
                
                int buscabinaria_recursiva = busca_binaria_recursiva(vetor_ordenado, 0, tam - 1, alvoBinario, &contadorBinario_recursivo);
                if (buscabinaria_recursiva != -1){
                    printf("Encontrado no indice %d!\n", buscabinaria_recursiva);
                } else {
                    printf("Valor nao encontrado (-1).\n");
                }
                printf("- O caso-base parou a busca no momento certo.\n");
                printf("- Total de chamadas recursivas (metade descartada): %d\n", contadorBinario_recursivo);
                break;
            }
            case 0:
                printf("\nEncerrando o laboratorio...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    free(vetor);
    free(vetor_ordenado);
    

    return 0;
}

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

// Função do Fibonacci
int fibonacci(int n, int *contadorFibonacci){
    (*contadorFibonacci)++; // Conta cada vez que a função é ativada.

    // Casos-base.
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Progresso ramificado (DUAS chamadas).
    return fibonacci(n - 1, contadorFibonacci) + fibonacci(n - 2, contadorFibonacci);
}

// Função de busca binária recursiva
int busca_binaria_recursiva(int *vetor, int inicio, int fim, int alvo, int *contadorBinario_recursivo){

    (*contadorBinario_recursivo)++;

    // Caso-base 1: Não encontrou (evita loop infinito / acesso indevido).
    if(inicio > fim) return -1; 

    int meio = inicio + (fim - inicio) / 2;

    // Caso-base 2: Encontrou
    if (vetor[meio] == alvo) return meio;

    // Progresso (chama apenas uma vez, descartando a metade inútil).
    if (alvo < vetor[meio]) return busca_binaria_recursiva(vetor, inicio, meio - 1, alvo, contadorBinario_recursivo);
    else return busca_binaria_recursiva(vetor, meio + 1, fim, alvo, contadorBinario_recursivo);
}

// Menu
void menu(){
    printf("\n--- MENU DO LABORATORIO DE DESEMPENHO ---\n");
    printf("1. Atividades 26 e 27 [Tempo Constante, Linear e Quadratico]\n");
    printf("2. Atividades 28 e 29 [Busca Binaria vs Linear]\n");
    printf("3. Atividade 30 [Fundamentos de Recursividade - Soma/Fatorial]\n");
    printf("4. Atividade 31 [Multiplas chamadas e Busca Binaria Recursiva]\n");
    printf("0. Sair\n");
    printf("Escolha um experimento: ");
}