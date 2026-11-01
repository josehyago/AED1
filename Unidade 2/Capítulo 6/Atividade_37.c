/*
 Capítulo 6 - Central de Algoritmos de ordenação
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

// Funções de Bubble Sort:

void bubblesort_numerico(int vetor[], int n, int *comparacoes, int *trocas, int *passagens){
    *comparacoes = 0;
    *trocas = 0;
    *passagens = 0;
    
    int houve_troca;

    for(int i = 0; i < n - 1; i++){
        houve_troca = 0;
        (*passagens)++; // Conta a passagem atual.

        // Reduz a parte útil (- i), pois os maiores já estão no final.
        for(int j = 0; j < n - i - 1; j++){
            (*comparacoes)++;

            if (vetor[j] > vetor[j + 1]){
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;

                (*trocas)++;
                houve_troca = 1; // Registrou que houve troca nesta passagem.
            }
        }
        // Se nenhuma troca ocorreu, o vetor já está ordenado.
        if(!houve_troca)
            break;
    }
}

// Retorna 1 se precisar trocar, 0 caso contrário
int devetrocar_jogador(Jogador a, Jogador b, int criterio, int direcao){
    int valor_a, valor_b;

    // Define qual campo será comparado (1 para ID, 2 para Pontuação)
    if (criterio == 1){ 
        valor_a = a.id; 
        valor_b = b.id; 
    } else { 
        valor_a = a.pontuacao;
        valor_b = b.pontuacao;
    }

    // Verifica direção: Crescente (direcao == 1) ou Decrescente (direcao == -1)
    if (direcao == 1){
        return (valor_a > valor_b); // Se o anterior for maior que o próximo, troca
    } else {
        return (valor_a < valor_b); // Se o anterior for menor que o próximo, troca (decrescente)
    }
}

void bubblesort_jogador(Jogador vetor[], int n, int criterio, int direcao, int *comparacoes, int *trocas, int *passagens){
    *comparacoes = *trocas = *passagens = 0;
    int houve_troca = 1;

    for (int i = 0; i < n - 1 && houve_troca; i++) {
        houve_troca = 0;
        (*passagens)++;

        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;

            // Usa a função separada para decidir a troca
            if (devetrocar_jogador(vetor[j], vetor[j + 1], criterio, direcao)) {
                Jogador temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;

                (*trocas)++;
                houve_troca = 1;
            }
        }
    }
}

// Função para intercalar duas metades ordenadas
void intercalar(int vetor[], int inicio, int meio, int fim, int *comparacoes){
    int i = inicio;       // Início da primeira metade
    int j = meio + 1;     // Início da segunda metade
    int k = 0;            // Índice do vetor temporário
    int tamanho = fim - inicio + 1;
    int temp[tamanho];    // Vetor auxiliar temporário

    // Compara os elementos das duas metades e coloca o menor no temporário
    while (i <= meio && j <= fim){
        (*comparacoes)++;
        if (vetor[i] <= vetor[j]){
            temp[k++] = vetor[i++];
        } else {
            temp[k++] = vetor[j++];
        }
    }

    // Copia os elementos restantes da primeira metade, se houver
    while (i <= meio){
        temp[k++] = vetor[i++];
    }

    // Copia os elementos restantes da segunda metade, se houver
    while (j <= fim){
        temp[k++] = vetor[j++];
    }

    // Devolve os valores ordenados do vetor temporário para o vetor original
    for (int l = 0; l < tamanho; l++){
        vetor[inicio + l] = temp[l];
    }
}

// Estrutura recursiva de Divisão e Conquista
void mergesort_numerico(int vetor[], int inicio, int fim, int *comparacoes) {
    if (inicio < fim) {
        // DIVIDIR: Encontra o ponto médio do intervalo
        int meio = inicio + (fim - inicio) / 2;

        // RESOLVER: Chamadas recursivas para ordenar as duas metades
        mergesort_numerico(vetor, inicio, meio, comparacoes);
        mergesort_numerico(vetor, meio + 1, fim, comparacoes);

        // COMBINAR: Intercala as metades ordenadas
        intercalar(vetor, inicio, meio, fim, comparacoes);
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

    // Bubble Sort Númerico:
    int bsorigem_numero_ordenado[] = {2, 4, 8, 15, 16, 23, 42, 99};
    int bsorigem_numero_inverso[] = {99, 42, 23, 16, 15, 8, 4, 2};
    int bsorigem_numero_aleatorio[] = {42, 15, 8, 99, 23, 4, 16, 2};
    int bsn_numero_ordenado = sizeof(bsorigem_numero_ordenado) / sizeof(bsorigem_numero_ordenado[0]);
    int bsn_numero_inverso = sizeof(bsorigem_numero_inverso) / sizeof(bsorigem_numero_inverso[0]);
    int bsn_numero_aleatorio = sizeof(bsorigem_numero_aleatorio) / sizeof(bsorigem_numero_aleatorio[0]);
    int bsdestino_numero_ordenado[bsn_numero_ordenado], bsdestino_numero_inverso[bsn_numero_inverso], bsdestino_numero_aleatorio[bsn_numero_aleatorio];
    int bscomparacoes_numero, bstrocas_numero, bspassagens_numero;

    copia_vetornumerico(bsorigem_numero_ordenado, bsdestino_numero_ordenado, bsn_numero_ordenado);
    copia_vetornumerico(bsorigem_numero_inverso, bsdestino_numero_inverso, bsn_numero_inverso);
    copia_vetornumerico(bsorigem_numero_aleatorio, bsdestino_numero_aleatorio, bsn_numero_aleatorio);

    printf("\n--- Bubble Sort Numerico ---\n");
    printf("Vetores Originais:\n");

    printf("\nVetor Ordenado: ");
    for (int i = 0; i < bsn_numero_ordenado; i++) printf("[%d] ", bsorigem_numero_ordenado[i]);
    printf("\n");

    printf("Vetor Inverso: ");
    for (int i = 0; i < bsn_numero_inverso; i++) printf("[%d] ", bsorigem_numero_inverso[i]);
    printf("\n");

    printf("Vetor Aleatorio: ");
    for (int i = 0; i < bsn_numero_aleatorio; i++) printf("[%d] ", bsorigem_numero_aleatorio[i]);
    printf("\n");

    bubblesort_numerico(bsdestino_numero_ordenado, bsn_numero_ordenado, &bscomparacoes_numero, &bstrocas_numero, &bspassagens_numero);

    printf("\nVetores Ordenados:\n");

    printf("\nVetor Ordenado: ");
    for (int i = 0; i < bsn_numero_ordenado; i++) printf("[%d] ", bsdestino_numero_ordenado[i]);
    printf("\n");
    printf("Metricas -> Comparacoes: %d | Trocas: %d | Passagens: %d\n", bscomparacoes_numero, bstrocas_numero, bspassagens_numero);

    bubblesort_numerico(bsdestino_numero_inverso, bsn_numero_inverso, &bscomparacoes_numero, &bstrocas_numero, &bspassagens_numero);

    printf("\nVetor Inverso: ");
    for (int i = 0; i < bsn_numero_inverso; i++) printf("[%d] ", bsdestino_numero_inverso[i]);
    printf("\n");
    printf("Metricas -> Comparacoes: %d | Trocas: %d | Passagens: %d\n", bscomparacoes_numero, bstrocas_numero, bspassagens_numero);

    bubblesort_numerico(bsdestino_numero_aleatorio, bsn_numero_aleatorio, &bscomparacoes_numero, &bstrocas_numero, &bspassagens_numero);

    printf("\nVetor Aleatorio: ");
    for (int i = 0; i < bsn_numero_aleatorio; i++) printf("[%d] ", bsdestino_numero_aleatorio[i]);
    printf("\n");
    printf("Metricas -> Comparacoes: %d | Trocas: %d | Passagens: %d\n\n", bscomparacoes_numero, bstrocas_numero, bspassagens_numero);

    // Bubble Sort Struct:

    Jogador bsorigem_jogador[] = {
        {103, "Bruno", 85},
        {101, "Carlos", 92},
        {105, "Ana", 78},
        {102, "Daniel", 95},
        {104, "Beatriz", 88}
    };
    int bsn_jogador = sizeof(bsorigem_jogador) / sizeof(bsorigem_jogador[0]);
    Jogador bsdestino_jogador[bsn_jogador];
    int bscomparacoes_jogador, bstrocas_jogador, bspassagens_jogador;

    // Teste 1: Ordenar por ID em ordem Crescente (criterio = 1, direcao = 1)
    copia_vetorstruct(bsorigem_jogador, bsdestino_jogador, bsn_jogador);
    printf("--- Bubble Sort de Jogadores (Campo: ID | Direcao: Crescente) ---\n");
    printf("Lista Original:\n");
    for (int i = 0; i < bsn_jogador; i++)
        printf("  ID: %d | Nome: %-10s | Pontuacao: %d\n", bsorigem_jogador[i].id, bsorigem_jogador[i].nome, bsorigem_jogador[i].pontuacao);

    bubblesort_jogador(bsdestino_jogador, bsn_jogador, 1, 1, &bscomparacoes_jogador, &bstrocas_jogador, &bspassagens_jogador);

    printf("\nLista Ordenada:\n");
    for (int i = 0; i < bsn_jogador; i++)
        printf("  ID: %d | Nome: %-10s | Pontuacao: %d\n", bsdestino_jogador[i].id, bsdestino_jogador[i].nome, bsdestino_jogador[i].pontuacao);
    
    printf("Metricas -> Comparacoes: %d | Trocas: %d | Passagens: %d\n\n", bscomparacoes_jogador, bstrocas_jogador, bspassagens_jogador);

    // Teste 2: Ordenar por Pontuação em ordem Decrescente (criterio = 2, direcao = -1)
    copia_vetorstruct(bsorigem_jogador, bsdestino_jogador, bsn_jogador);
    printf("--- Bubble Sort de Jogadores (Campo: Pontuacao | Direcao: Decrescente) ---\n");
    
    bubblesort_jogador(bsdestino_jogador, bsn_jogador, 2, -1, &bscomparacoes_jogador, &bstrocas_jogador, &bspassagens_jogador);

    printf("Lista Ordenada:\n");
    for (int i = 0; i < bsn_jogador; i++)
        printf("  ID: %d | Nome: %-10s | Pontuacao: %d\n", bsdestino_jogador[i].id, bsdestino_jogador[i].nome, bsdestino_jogador[i].pontuacao);

    printf("Metricas -> Comparacoes: %d | Trocas: %d | Passagens: %d\n", bscomparacoes_jogador, bstrocas_jogador, bspassagens_jogador);

    // Merge Sort / Intercalação Numérica:
    int ms_origem_numero[] = {38, 27, 43, 3, 9, 82, 10};
    int ms_n_numero = sizeof(ms_origem_numero) / sizeof(ms_origem_numero[0]);
    int ms_destino_numero[ms_n_numero];
    int ms_comparacoes_numero = 0;

    // Preserva a entrada original
    copia_vetornumerico(ms_origem_numero, ms_destino_numero, ms_n_numero);

    printf("\n--- Merge Sort (Divisao e Conquista / Intercalacao) ---\n");
    printf("Vetor Original: ");
    for (int i = 0; i < ms_n_numero; i++) printf("[%d] ", ms_origem_numero[i]);
    printf("\n");

    // Executa a ordenação por divisão e conquista
    mergesort_numerico(ms_destino_numero, 0, ms_n_numero - 1, &ms_comparacoes_numero);

    printf("Vetor Ordenado: ");
    for (int i = 0; i < ms_n_numero; i++) printf("[%d] ", ms_destino_numero[i]);
    printf("\n");
    printf("Metricas -> Comparacoes de Intercalacao: %d\n", ms_comparacoes_numero);

    return 0;
}