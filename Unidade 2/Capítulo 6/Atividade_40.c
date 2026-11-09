/*
 Capítulo 6 - Central de Algoritmos de ordenação
 Atividade 40 - Pivô aleatório e Quick Sort de estruturas

 Contexto: Escolher sempre uma posição fixa como pivô pode gerar divisões ruins em certas entradas. A central usará seleção pseudoaleatória e completará o suporte a jogadores.
 Descrição detalhada: Modifique o Quick Sort para escolher um pivô aleatório dentro do intervalo atual, colocando-o na posição esperada pela partição. Depois, adapte o algoritmo para estruturas. Finalize um menu que gere ou carregue dados, execute qualquer ordenação sobre uma cópia e apresente métricas comparáveis.
 Requisitos:
 - inicializar o gerador pseudoaleatório uma única vez;
 - escolher o pivô apenas dentro do subintervalo;
 - adaptar partição e troca para jogadores;
 - aplicar critério e desempate consistentes;
 - executar cada algoritmo sobre a mesma entrada original;
 - produzir um relatório final de comparações, trocas e deslocamentos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MAX 1000
#define LIMITE_IMPRESSAO 15
 
typedef struct{
    int id;
    char nome[50];
    int pontuacao;
} Jogador;
 
typedef struct{
    int comparacoes;
    int trocas;
    int deslocamentos;
    int passagens;
} Metricas;
 
enum { SELECTION, INSERTION, BUBBLE, MERGE, QUICK_ALEATORIO, QUICK_FIXO, TOTAL_ALGORITMOS };

// Utilitários
void limpar_buffer(void);
int ler_inteiro(const char *mensagem);
void menu(void);
const char *nome_algoritmo(int alg);
void trocar_inteiros(int *a, int *b);
void trocar_jogadores(Jogador *a, Jogador *b);
int comparar_jogador(const Jogador *a, const Jogador *b);
 
// Dados
void gerar_dados(Jogador jogadores[], int n);
void extrair_pontuacoes(const Jogador jogadores[], int n, int numeros[]);
 
// Algoritmos de ordenação
void selection_numerico(int v[], int n, Metricas *m);
void selection_jogador(Jogador v[], int n, Metricas *m);
void insertion_numerico(int v[], int n, Metricas *m);
void insertion_jogador(Jogador v[], int n, Metricas *m);
void bubble_numerico(int v[], int n, Metricas *m);
void bubble_jogador(Jogador v[], int n, Metricas *m);
void intercalar_numerico(int v[], int ini, int meio, int fim, Metricas *m);
void intercalar_jogador(Jogador v[], int ini, int meio, int fim, Metricas *m);
void merge_numerico(int v[], int ini, int fim, Metricas *m);
void merge_jogador(Jogador v[], int ini, int fim, Metricas *m);
int particionar_aux(int v[], int ini, int fim, Metricas *m);
int particionar_numerico(int v[], int ini, int fim, int aleatorio, Metricas *m);
int particionar_jogador(Jogador v[], int ini, int fim, int aleatorio, Metricas *m);
void quick_numerico(int v[], int ini, int fim, int aleatorio, Metricas *m);
void quick_jogador(Jogador v[], int ini, int fim, int aleatorio, Metricas *m);
 
// Execução, exibição e relatórios
void rodar_numerico(int alg, int v[], int n, Metricas *m);
void rodar_jogador(int alg, Jogador v[], int n, Metricas *m);
int ordenado_numerico(const int v[], int n);
int ordenado_jogador(const Jogador v[], int n);
void mostrar_numeros(const char *rotulo, const int v[], int n);
void mostrar_jogadores(const char *rotulo, const Jogador v[], int n);
void mostrar_metricas(const Metricas *m);
void demonstrar_algoritmo(int alg, const int numeros[], const Jogador jogadores[], int n);
void demonstrar_particoes(void);
void comparar_pivos(const int numeros[], int n);
void relatorio_final(const int numeros[], const Jogador jogadores[], int n);
 
int main(){
    Jogador jogadores[MAX]; // Entrada original (nunca é ordenada, só copiada).
    int numeros[MAX];       // Pontuações dos jogadores, usadas como vetor numérico.
    int n = 0;
    int opcao;
 
    srand(time(NULL)); // Gerador pseudoaleatório inicializado uma única vez.
 
    do{
        menu();
        opcao = ler_inteiro("Escolha: ");
 
        // Todas as opções, exceto 1, 7 e 0, precisam de dados na memória.
        if (n == 0 && opcao >= 2 && opcao <= 10 && opcao != 7){
            printf("\nGere os dados primeiro (opcao 1).\n");
            continue;
        }
 
        switch(opcao){
            case 1:{
                int qtd = ler_inteiro("Quantidade de jogadores (1 a 1000): ");
                if (qtd < 1 || qtd > MAX){
                    printf("Quantidade invalida.\n");
                    break;
                }
                n = qtd;
                gerar_dados(jogadores, n);
                extrair_pontuacoes(jogadores, n, numeros);
                printf("%d jogadores gerados.\n", n);
                break;
            }
            case 2:
                printf("\n--- Entrada original (%d elementos) ---\n", n);
                mostrar_numeros("Numeros (pontuacoes):", numeros, n);
                mostrar_jogadores("Jogadores:", jogadores, n);
                break;
            case 3: demonstrar_algoritmo(SELECTION, numeros, jogadores, n); break;
            case 4: demonstrar_algoritmo(INSERTION, numeros, jogadores, n); break;
            case 5: demonstrar_algoritmo(BUBBLE, numeros, jogadores, n); break;
            case 6: demonstrar_algoritmo(MERGE, numeros, jogadores, n); break;
            case 7: demonstrar_particoes(); break;
            case 8: demonstrar_algoritmo(QUICK_ALEATORIO, numeros, jogadores, n); break;
            case 9: comparar_pivos(numeros, n); break;
            case 10: relatorio_final(numeros, jogadores, n); break;
            case 0:
                printf("\nEncerrando a central de algoritmos...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
 
    return 0;
}
 
// Utilitários
 
void limpar_buffer(void){
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}
 
int ler_inteiro(const char *mensagem){
    int valor, lido;
    printf("%s", mensagem);
    while ((lido = scanf("%d", &valor)) != 1){
        if (lido == EOF) exit(0);
        limpar_buffer();
        printf("Entrada invalida. %s", mensagem);
    }
    return valor;
}
 
void menu(void){
    printf("\n--- CENTRAL DE ALGORITMOS DE ORDENACAO ---\n");
    printf(" 1. Gerar dados aleatorios\n");
    printf(" 2. Mostrar entrada original\n");
    printf(" 3. Selection Sort\n");
    printf(" 4. Insertion Sort\n");
    printf(" 5. Bubble Sort\n");
    printf(" 6. Merge Sort\n");
    printf(" 7. Particoes isoladas (auxiliar vs in-place)\n");
    printf(" 8. Quick Sort (pivo aleatorio)\n");
    printf(" 9. Quick Sort: pivo fixo vs pivo aleatorio\n");
    printf("10. Relatorio final (todos os algoritmos)\n");
    printf(" 0. Sair\n");
}
 
const char *nome_algoritmo(int alg){
    static const char *nomes[TOTAL_ALGORITMOS] = {
        "Selection Sort", "Insertion Sort", "Bubble Sort", "Merge Sort",
        "Quick Sort (pivo aleatorio)", "Quick Sort (pivo fixo)"
    };
    return nomes[alg];
}
 
void trocar_inteiros(int *a, int *b){ int t = *a; *a = *b; *b = t; }
void trocar_jogadores(Jogador *a, Jogador *b){ Jogador t = *a; *a = *b; *b = t; }
 
// Critério único para todos os algoritmos: maior pontuação primeiro;
// empate -> nome em ordem alfabética; novo empate -> menor ID.
// Retorna negativo se a vem antes de b, positivo se vem depois, 0 se equivalentes.
int comparar_jogador(const Jogador *a, const Jogador *b){
    if (a->pontuacao != b->pontuacao) return b->pontuacao - a->pontuacao;
    int c = strcmp(a->nome, b->nome);
    if (c != 0) return c;
    return a->id - b->id;
}
 
// Dados
 
void gerar_dados(Jogador jogadores[], int n){
    const char *nomes[] = {"Ana", "Bruno", "Carlos", "Daniel", "Beatriz", "Eduarda", "Felipe", "Gabriela"};
    int total_nomes = sizeof(nomes) / sizeof(nomes[0]);
 
    for (int i = 0; i < n; i++){
        jogadores[i].id = 101 + i;
        strcpy(jogadores[i].nome, nomes[rand() % total_nomes]);
        jogadores[i].pontuacao = rand() % 101; // Faixa curta -> gera valores repetidos.
    }
}
 
void extrair_pontuacoes(const Jogador jogadores[], int n, int numeros[]){
    for (int i = 0; i < n; i++) numeros[i] = jogadores[i].pontuacao;
}
 
// Selection Sort
 
void selection_numerico(int v[], int n, Metricas *m){
    for (int i = 0; i < n - 1; i++){
        int menor = i;
        for (int j = i + 1; j < n; j++){
            m->comparacoes++;
            if (v[j] < v[menor]) menor = j;
        }
        if (menor != i){ // Só troca se necessário.
            trocar_inteiros(&v[i], &v[menor]);
            m->trocas++;
        }
    }
}
 
void selection_jogador(Jogador v[], int n, Metricas *m){
    for (int i = 0; i < n - 1; i++){
        int primeiro = i;
        for (int j = i + 1; j < n; j++){
            m->comparacoes++;
            if (comparar_jogador(&v[j], &v[primeiro]) < 0) primeiro = j;
        }
        if (primeiro != i){
            trocar_jogadores(&v[i], &v[primeiro]);
            m->trocas++;
        }
    }
}
 
// Insertion Sort
 
void insertion_numerico(int v[], int n, Metricas *m){
    for (int i = 1; i < n; i++){
        int chave = v[i];
        int j = i - 1;
        while (j >= 0){
            m->comparacoes++;
            if (v[j] > chave){ // Desloca para a direita em vez de trocar.
                v[j + 1] = v[j];
                m->deslocamentos++;
                j--;
            } else break;      // Achou a posição: para sem varrer o resto.
        }
        v[j + 1] = chave;
    }
}
 
void insertion_jogador(Jogador v[], int n, Metricas *m){
    for (int i = 1; i < n; i++){
        Jogador chave = v[i];
        int j = i - 1;
        while (j >= 0){
            m->comparacoes++;
            if (comparar_jogador(&v[j], &chave) > 0){
                v[j + 1] = v[j];
                m->deslocamentos++;
                j--;
            } else break;
        }
        v[j + 1] = chave;
    }
}
 
// Bubble Sort
 
void bubble_numerico(int v[], int n, Metricas *m){
    for (int i = 0; i < n - 1; i++){
        int houve_troca = 0;
        m->passagens++;
        for (int j = 0; j < n - i - 1; j++){ // Os maiores já estão no fim: reduz o percurso.
            m->comparacoes++;
            if (v[j] > v[j + 1]){
                trocar_inteiros(&v[j], &v[j + 1]);
                m->trocas++;
                houve_troca = 1;
            }
        }
        if (!houve_troca) break; // Nenhuma troca: já está ordenado.
    }
}
 
void bubble_jogador(Jogador v[], int n, Metricas *m){
    for (int i = 0; i < n - 1; i++){
        int houve_troca = 0;
        m->passagens++;
        for (int j = 0; j < n - i - 1; j++){
            m->comparacoes++;
            if (comparar_jogador(&v[j], &v[j + 1]) > 0){
                trocar_jogadores(&v[j], &v[j + 1]);
                m->trocas++;
                houve_troca = 1;
            }
        }
        if (!houve_troca) break;
    }
}
 
// Merge Sort

// Deslocamentos no Merge = elementos gravados de volta no vetor após cada intercalação.
 
void intercalar_numerico(int v[], int ini, int meio, int fim, Metricas *m){
    int tamanho = fim - ini + 1;
    int aux[tamanho];
    int i = ini, j = meio + 1, k = 0;
 
    while (i <= meio && j <= fim){
        m->comparacoes++;
        if (v[i] <= v[j]) aux[k++] = v[i++];
        else aux[k++] = v[j++];
    }
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim) aux[k++] = v[j++];
 
    for (k = 0; k < tamanho; k++) v[ini + k] = aux[k];
    m->deslocamentos += tamanho;
}
 
void intercalar_jogador(Jogador v[], int ini, int meio, int fim, Metricas *m){
    int tamanho = fim - ini + 1;
    Jogador aux[tamanho];
    int i = ini, j = meio + 1, k = 0;
 
    while (i <= meio && j <= fim){
        m->comparacoes++;
        if (comparar_jogador(&v[i], &v[j]) <= 0) aux[k++] = v[i++];
        else aux[k++] = v[j++];
    }
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim) aux[k++] = v[j++];
 
    for (k = 0; k < tamanho; k++) v[ini + k] = aux[k];
    m->deslocamentos += tamanho;
}
 
void merge_numerico(int v[], int ini, int fim, Metricas *m){
    if (ini < fim){
        int meio = ini + (fim - ini) / 2;
        merge_numerico(v, ini, meio, m);
        merge_numerico(v, meio + 1, fim, m);
        intercalar_numerico(v, ini, meio, fim, m);
    }
}
 
void merge_jogador(Jogador v[], int ini, int fim, Metricas *m){
    if (ini < fim){
        int meio = ini + (fim - ini) / 2;
        merge_jogador(v, ini, meio, m);
        merge_jogador(v, meio + 1, fim, m);
        intercalar_jogador(v, ini, meio, fim, m);
    }
}
 
// Quick Sort
 
// Partição com memória auxiliar: pivô = último; menores/iguais vão para o início do auxiliar, maiores para o fim, e o pivô fica na lacuna entre os dois grupos.
int particionar_aux(int v[], int ini, int fim, Metricas *m){
    int tamanho = fim - ini + 1;
    int aux[tamanho];
    int pivo = v[fim];
    int esq = 0, dir = tamanho - 1;
 
    for (int i = ini; i < fim; i++){
        m->comparacoes++;
        if (v[i] <= pivo) aux[esq++] = v[i];
        else aux[dir--] = v[i];
    }
    aux[esq] = pivo; // Neste ponto esq == dir: é a posição final do pivô.
 
    for (int i = 0; i < tamanho; i++) v[ini + i] = aux[i];
    m->deslocamentos += tamanho;
    return ini + esq;
}
 
// Partição in-place (Lomuto). Se aleatorio == 1, sorteia o pivô DENTRO de [ini, fim] e o leva para o fim, que é a posição esperada pela partição.
int particionar_numerico(int v[], int ini, int fim, int aleatorio, Metricas *m){
    if (aleatorio){
        int p = ini + rand() % (fim - ini + 1);
        if (p != fim){
            trocar_inteiros(&v[p], &v[fim]);
            m->trocas++;
        }
    }
 
    int pivo = v[fim];
    int i = ini - 1; // Último índice da região "menores ou iguais ao pivô".
 
    for (int j = ini; j < fim; j++){
        m->comparacoes++;
        if (v[j] <= pivo){
            i++;
            if (i != j){
                trocar_inteiros(&v[i], &v[j]);
                m->trocas++;
            }
        }
    }
    if (i + 1 != fim){
        trocar_inteiros(&v[i + 1], &v[fim]); // Pivô na posição definitiva.
        m->trocas++;
    }
    return i + 1;
}
 
int particionar_jogador(Jogador v[], int ini, int fim, int aleatorio, Metricas *m){
    if (aleatorio){
        int p = ini + rand() % (fim - ini + 1);
        if (p != fim){
            trocar_jogadores(&v[p], &v[fim]);
            m->trocas++;
        }
    }
 
    Jogador pivo = v[fim];
    int i = ini - 1;
 
    for (int j = ini; j < fim; j++){
        m->comparacoes++;
        if (comparar_jogador(&v[j], &pivo) <= 0){
            i++;
            if (i != j){
                trocar_jogadores(&v[i], &v[j]);
                m->trocas++;
            }
        }
    }
    if (i + 1 != fim){
        trocar_jogadores(&v[i + 1], &v[fim]);
        m->trocas++;
    }
    return i + 1;
}
 
void quick_numerico(int v[], int ini, int fim, int aleatorio, Metricas *m){
    if (ini < fim){ // Só desce nos subintervalos que ainda têm 2+ elementos.
        int p = particionar_numerico(v, ini, fim, aleatorio, m);
        quick_numerico(v, ini, p - 1, aleatorio, m);
        quick_numerico(v, p + 1, fim, aleatorio, m);
    }
}
 
void quick_jogador(Jogador v[], int ini, int fim, int aleatorio, Metricas *m){
    if (ini < fim){
        int p = particionar_jogador(v, ini, fim, aleatorio, m);
        quick_jogador(v, ini, p - 1, aleatorio, m);
        quick_jogador(v, p + 1, fim, aleatorio, m);
    }
}
 
// Execução, exibição e relatórios
 
void rodar_numerico(int alg, int v[], int n, Metricas *m){
    switch(alg){
        case SELECTION:       selection_numerico(v, n, m); break;
        case INSERTION:       insertion_numerico(v, n, m); break;
        case BUBBLE:          bubble_numerico(v, n, m); break;
        case MERGE:           merge_numerico(v, 0, n - 1, m); break;
        case QUICK_ALEATORIO: quick_numerico(v, 0, n - 1, 1, m); break;
        case QUICK_FIXO:      quick_numerico(v, 0, n - 1, 0, m); break;
    }
}
 
void rodar_jogador(int alg, Jogador v[], int n, Metricas *m){
    switch(alg){
        case SELECTION:       selection_jogador(v, n, m); break;
        case INSERTION:       insertion_jogador(v, n, m); break;
        case BUBBLE:          bubble_jogador(v, n, m); break;
        case MERGE:           merge_jogador(v, 0, n - 1, m); break;
        case QUICK_ALEATORIO: quick_jogador(v, 0, n - 1, 1, m); break;
        case QUICK_FIXO:      quick_jogador(v, 0, n - 1, 0, m); break;
    }
}
 
int ordenado_numerico(const int v[], int n){
    for (int i = 1; i < n; i++) if (v[i - 1] > v[i]) return 0;
    return 1;
}
 
int ordenado_jogador(const Jogador v[], int n){
    for (int i = 1; i < n; i++) if (comparar_jogador(&v[i - 1], &v[i]) > 0) return 0;
    return 1;
}
 
void mostrar_numeros(const char *rotulo, const int v[], int n){
    printf("%-24s", rotulo);
    for (int i = 0; i < n && i < LIMITE_IMPRESSAO; i++) printf("[%d] ", v[i]);
    if (n > LIMITE_IMPRESSAO) printf("... (+%d)", n - LIMITE_IMPRESSAO);
    printf("\n");
}
 
void mostrar_jogadores(const char *rotulo, const Jogador v[], int n){
    printf("%s\n", rotulo);
    for (int i = 0; i < n && i < LIMITE_IMPRESSAO; i++)
        printf("  ID: %d | Nome: %-10s | Pontuacao: %d\n", v[i].id, v[i].nome, v[i].pontuacao);
    if (n > LIMITE_IMPRESSAO) printf("  ... (+%d jogadores)\n", n - LIMITE_IMPRESSAO);
}
 
void mostrar_metricas(const Metricas *m){
    printf("Metricas -> Comparacoes: %d | Trocas: %d | Deslocamentos: %d", m->comparacoes, m->trocas, m->deslocamentos);
    if (m->passagens > 0) printf(" | Passagens: %d", m->passagens);
    printf("\n");
}
 
// Ordena CÓPIAS dos dois conjuntos (números e jogadores) com o algoritmo escolhido.
void demonstrar_algoritmo(int alg, const int numeros[], const Jogador jogadores[], int n){
    int vn[MAX];
    Jogador vj[MAX];
    Metricas mn = {0}, mj = {0};
 
    memcpy(vn, numeros, n * sizeof(int));
    memcpy(vj, jogadores, n * sizeof(Jogador));
 
    printf("\n=== %s ===\n", nome_algoritmo(alg));
 
    printf("\n-- Numeros (crescente) --\n");
    mostrar_numeros("Original:", numeros, n);
    rodar_numerico(alg, vn, n, &mn);
    mostrar_numeros("Ordenado:", vn, n);
    mostrar_metricas(&mn);
    printf("Ordenacao correta: %s\n", ordenado_numerico(vn, n) ? "sim" : "NAO");
 
    printf("\n-- Jogadores (maior pontuacao; desempate por nome e depois ID) --\n");
    mostrar_jogadores("Original:", jogadores, n);
    rodar_jogador(alg, vj, n, &mj);
    mostrar_jogadores("Ordenado:", vj, n);
    mostrar_metricas(&mj);
    printf("Ordenacao correta: %s\n", ordenado_jogador(vj, n) ? "sim" : "NAO");
}
 
// Mostra as duas formas de partição isoladamente, com valores repetidos.
void demonstrar_particoes(void){
    int base[10] = {42, 15, 8, 42, 23, 4, 16, 99, 15, 42};
    int a[10], b[10], c[10];
    int n = 10;
    Metricas ma = {0}, mb = {0}, mc = {0};
 
    memcpy(a, base, sizeof(base));
    memcpy(b, base, sizeof(base));
    memcpy(c, base, sizeof(base));
 
    printf("\n=== Particoes isoladas (esquerda <= pivo < direita) ===\n");
    mostrar_numeros("Original:", base, n);
 
    int pa = particionar_aux(a, 0, n - 1, &ma);
    printf("\n1) Com memoria auxiliar (pivo = ultimo)\n");
    mostrar_numeros("Resultado:", a, n);
    printf("Pivo %d ficou na posicao %d\n", a[pa], pa);
    mostrar_metricas(&ma);
 
    int pb = particionar_numerico(b, 0, n - 1, 0, &mb);
    printf("\n2) In-place (pivo = ultimo)\n");
    mostrar_numeros("Resultado:", b, n);
    printf("Pivo %d ficou na posicao %d\n", b[pb], pb);
    mostrar_metricas(&mb);
 
    int pc = particionar_numerico(c, 0, n - 1, 1, &mc);
    printf("\n3) In-place (pivo ALEATORIO dentro do intervalo)\n");
    mostrar_numeros("Resultado:", c, n);
    printf("Pivo %d ficou na posicao %d\n", c[pc], pc);
    mostrar_metricas(&mc);
}
 
// Compara pivô fixo e aleatório na entrada original e numa entrada já ordenada.
void comparar_pivos(const int numeros[], int n){
    int ordenado[MAX];
    Metricas ms = {0};
 
    memcpy(ordenado, numeros, n * sizeof(int));
    merge_numerico(ordenado, 0, n - 1, &ms); // Prepara a entrada já ordenada.
 
    const int *entradas[2] = {numeros, ordenado};
    const char *rotulos[2] = {"Entrada original", "Entrada ja ordenada"};
 
    printf("\n=== Quick Sort: pivo fixo (ultimo) vs pivo aleatorio (n = %d) ===\n", n);
    for (int e = 0; e < 2; e++){
        int c1[MAX], c2[MAX];
        Metricas mf = {0}, ma = {0};
 
        memcpy(c1, entradas[e], n * sizeof(int));
        memcpy(c2, entradas[e], n * sizeof(int));
        quick_numerico(c1, 0, n - 1, 0, &mf);
        quick_numerico(c2, 0, n - 1, 1, &ma);
 
        printf("%-20s | Fixo: %7d comp %7d trocas | Aleatorio: %7d comp %7d trocas\n",
               rotulos[e], mf.comparacoes, mf.trocas, ma.comparacoes, ma.trocas);
    }
    printf("Na entrada ja ordenada o pivo fixo degenera (~n^2/2 comparacoes).\n");
}
 
// Todos os algoritmos recebem uma cópia da MESMA entrada original.
void relatorio_final(const int numeros[], const Jogador jogadores[], int n){
    printf("\n=== RELATORIO FINAL (n = %d; todos partem da mesma entrada original) ===\n", n);
 
    printf("\nNumeros (crescente):\n");
    printf("%-28s %12s %8s %14s %9s\n", "Algoritmo", "Comparacoes", "Trocas", "Deslocamentos", "Ordenado");
    for (int alg = 0; alg < TOTAL_ALGORITMOS; alg++){
        int v[MAX];
        Metricas m = {0};
        memcpy(v, numeros, n * sizeof(int));
        rodar_numerico(alg, v, n, &m);
        printf("%-28s %12d %8d %14d %9s\n", nome_algoritmo(alg), m.comparacoes, m.trocas, m.deslocamentos,
               ordenado_numerico(v, n) ? "sim" : "NAO");
    }
 
    printf("\nJogadores (pontuacao desc, nome, ID):\n");
    printf("%-28s %12s %8s %14s %9s\n", "Algoritmo", "Comparacoes", "Trocas", "Deslocamentos", "Ordenado");
    for (int alg = 0; alg < TOTAL_ALGORITMOS; alg++){
        Jogador v[MAX];
        Metricas m = {0};
        memcpy(v, jogadores, n * sizeof(Jogador));
        rodar_jogador(alg, v, n, &m);
        printf("%-28s %12d %8d %14d %9s\n", nome_algoritmo(alg), m.comparacoes, m.trocas, m.deslocamentos,
               ordenado_jogador(v, n) ? "sim" : "NAO");
    }
 
    printf("\nObs.: Selection/Bubble/Quick contam trocas; Insertion conta deslocamentos;\n");
    printf("Merge conta elementos regravados na intercalacao; o pivo aleatorio muda a cada execucao.\n");
}