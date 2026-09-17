// Capítulo 3 — Catalágo dinâmico de personagens
// Atividade 20 — Estruturas aninhadas e enumerações

// Contexto: O modelo do catálogo precisa expressar melhor os conceitos do domínio. Coordenadas formam uma posição, personagens pertencem a equipes e estados como classe ou nível devem usar valores nomeados em vez de números soltos.
// Descrição detalhada: Finalize o capítulo reorganizando os tipos. Crie Posicao, incorpore-a em Personagem, defina Equipe e represente uma classificação com enum. Atualize as funções anteriores para trabalhar com o novo modelo sem perder recursos já implementados.
// Requisitos:
// - aninhar Posicao em Personagem;
// - criar uma estrutura que represente a equipe e seu catálogo;
// - definir um enum para classe, estado ou nível;
// - converter os valores enumerados em textos legíveis;
// - atualizar cadastro, busca, alteração e listagem;
// - disponibilizar todas as operações em um menu integrado.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INICIANTE = 0,
    INTERMEDIARIO,
    AVANCADO,
    MESTRE
} Nivel;

typedef struct {
    float x;
    float y;
} Posicao;

typedef struct{
    int id;
    char nome[50];
    int vida;
    int pontuacao;
    Posicao pos;
    Nivel nivel;
} Personagem;

typedef struct {
    Personagem *membros;
    int capacidade;
    int tamanho_atual;
} Equipe;

char* obter_nome_nivel(Nivel nivel);

Personagem construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y, Nivel nivel);
void cadastrar_personagem(Equipe *equipe);
void inicializar_equipe(Equipe *equipe, int capacidade_inicial);
void exibir_equipe(Equipe *equipe);
void alterar_personagem(Equipe *equipe);

int buscar_personagem_por_id(Equipe *equipe, int id);

void intercalar(Personagem *vetor, int inicio, int meio, int fim, int *comparacoes);
void merge_sort(Personagem *vetor, int inicio, int fim, int *comparacoes);

void ordenar_equipe(Equipe *equipe);
void liberar_equipe(Equipe *equipe);

int main(){
    Equipe equipe;
    inicializar_equipe(&equipe, 5);

    equipe.membros[0] = construir_personagem(3, "Hyago", 80, 0, 10.5, 5.0, INTERMEDIARIO);
    equipe.membros[1] = construir_personagem(4, "Margarida", 100, 800, 5.0, 3.0, MESTRE);
    equipe.membros[2] = construir_personagem(2, "Gabriel", 85, 600, 2.0, 4.0, AVANCADO);
    equipe.membros[3] = construir_personagem(1, "Ana Paula", 95, 750, 4.0, 1.0, INICIANTE);
    equipe.membros[4] = construir_personagem(5, "Samuel", 40, 200, 6.0, 5.0, AVANCADO);
    equipe.tamanho_atual = 5;

    int opcao = -1;
    do{
        printf("CATALOGO DINAMICO DE PERSONAGENS\n");
        printf("\n");
        printf("1. Cadastrar Personagem\n");
        printf("2. Exibir Equipe\n");
        printf("3. Buscar Personagem por ID\n");
        printf("4. Alterar Dados de um Personagem\n");
        printf("5. Ordenar Equipe por ID (Merge Sort)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1){
            while (getchar() != '\n');
            printf("Opcao invalida!\n");
            continue;
        }
        getchar();

        switch (opcao){
            case 1:
                cadastrar_personagem(&equipe);
                break;
            case 2:
                exibir_equipe(&equipe);
                break;
            case 3:{
                int id;
                printf("\nDigite o ID para busca: ");
                scanf("%d", &id);
                getchar();
                int idx = buscar_personagem_por_id(&equipe, id);
                if (idx != -1){
                    Personagem personagem = equipe.membros[idx];
                    printf("\nPersonagem encontrado:\n");
                    printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Pos: (%.2f, %.2f) | Nivel: %s\n",
                           personagem.id, personagem.nome, personagem.vida, personagem.pontuacao, personagem.pos.x, personagem.pos.y, obter_nome_nivel(personagem.nivel));
                }else{
                    printf("Personagem com ID %d nao encontrado.\n", id);
                }
                break;
            }
            case 4:
                alterar_personagem(&equipe);
                break;
            case 5:
                ordenar_equipe(&equipe);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }while (opcao != 0);

    liberar_equipe(&equipe);


    return 0;
}

char* obter_nome_nivel(Nivel nivel){
    switch (nivel){
        case INICIANTE:     return "Iniciante";
        case INTERMEDIARIO: return "Intermediario";
        case AVANCADO:      return "Avancado";
        case MESTRE:        return "Mestre";
        default:            return "Desconhecido";
    }
}

Personagem construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y, Nivel nivel){
    Personagem novo_personagem;
    
    novo_personagem.id = id;

    strncpy(novo_personagem.nome, nome, sizeof(novo_personagem.nome) - 1);
    novo_personagem.nome[sizeof(novo_personagem.nome) - 1] = '\0';

    novo_personagem.vida = (vida > 100) ? 100 : ((vida < 0) ? 0 : vida);
    novo_personagem.pontuacao = (pontuacao < 0) ? 0 : pontuacao;
    novo_personagem.pos.x = posicao_x;
    novo_personagem.pos.y = posicao_y;
    novo_personagem.nivel = nivel;

    return novo_personagem;
}

void inicializar_equipe(Equipe *equipe, int capacidade_inicial){
    equipe->capacidade = capacidade_inicial;
    equipe->tamanho_atual = 0;
    equipe->membros = (Personagem *) calloc(equipe->capacidade, sizeof(Personagem));
    if (equipe->membros == NULL){
        printf("Erro: Falha na alocacao de memoria inicial.\n");
        exit(1);
    }
}

void cadastrar_personagem(Equipe *equipe){
    if (equipe->tamanho_atual >= equipe->capacidade){
        int nova_capacidade = equipe->capacidade * 2;
        
        Personagem *temp = (Personagem *) realloc(equipe->membros, nova_capacidade * sizeof(Personagem));
        
        if (temp == NULL){
            printf("Erro: Nao foi possivel expandir a capacidade.\n");
            return;
        }
        
        equipe->membros = temp;
        
        for (int i = equipe->capacidade; i < nova_capacidade; i++){
            equipe->membros[i] = construir_personagem(0, "", 0, 0, 0.0, 0.0, INICIANTE);
        }
        printf("\nCapacidade expandida de %d para %d.\n", equipe->capacidade, nova_capacidade);
        equipe->capacidade = nova_capacidade;
    }

    int id, vida, pontuacao, opcao_nivel;
    char nome[50];
    float x, y;

    printf("\nNovo Cadastro: \n");
    printf("ID: ");
    scanf("%d", &id);
    getchar();

    if (buscar_personagem_por_id(equipe, id) != -1){
        printf("Erro: Ja existe um personagem com o ID %d\n", id);
        return;
    }

    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Vida (0 a 100): ");
    scanf("%d", &vida);
    printf("Pontuacao: ");
    scanf("%d", &pontuacao);
    printf("Posicao X: ");
    scanf("%f", &x);
    printf("Posicao Y: ");
    scanf("%f", &y);

    printf("Nivel (0-Iniciante, 1-Intermediario, 2-Avancado, 3-Mestre): ");
    scanf("%d", &opcao_nivel);
    getchar();

    if (opcao_nivel < 0 || opcao_nivel > 3) opcao_nivel = 0;

    equipe->membros[equipe->tamanho_atual] = construir_personagem(id, nome, vida, pontuacao, x, y, (Nivel)opcao_nivel);
    equipe->tamanho_atual++;

    printf("Personagem cadastrado com sucesso!\n");
}

void exibir_equipe(Equipe *equipe){
    printf("\nLista da Equipe (%d/%d Membros)\n", equipe->tamanho_atual, equipe->capacidade);
    
    if (equipe->tamanho_atual == 0){
        printf("Nenhum personagem cadastrado.\n");
        return;
    }

    for (int i = 0; i < equipe->tamanho_atual; i++){
        Personagem personagem = equipe->membros[i];
        printf("ID: %-2d | Nome: %-12s | Vida: %3d | Pontos: %4d | Pos: (%.1f, %.1f) | Nivel: %s\n",
               personagem.id, personagem.nome, personagem.vida, personagem.pontuacao, personagem.pos.x, personagem.pos.y, obter_nome_nivel(personagem.nivel));
    }
}

int buscar_personagem_por_id(Equipe *equipe, int id){
    for (int i = 0; i < equipe->tamanho_atual; i++){
        if (equipe->membros[i].id == id){
            return i;
        }
    }
    return -1;
}

void alterar_personagem(Equipe *equipe){
    int id;
    printf("\nDigite o ID do personagem para alterar: ");
    scanf("%d", &id);
    getchar();

    int idx = buscar_personagem_por_id(equipe, id);
    if (idx == -1){
        printf("Personagem com ID %d nao encontrado.\n", id);
        return;
    }

    printf("Alterando dados do personagem: '%s' (ID %d)\n", equipe->membros[idx].nome, id);
    
    printf("Nova Vida: ");
    scanf("%d", &equipe->membros[idx].vida);
    if (equipe->membros[idx].vida > 100) equipe->membros[idx].vida = 100;
    if (equipe->membros[idx].vida < 0) equipe->membros[idx].vida = 0;

    printf("Nova Pontuacao: ");
    scanf("%d", &equipe->membros[idx].pontuacao);
    if (equipe->membros[idx].pontuacao < 0) equipe->membros[idx].pontuacao = 0;

    printf("Nova Posicao X: ");
    scanf("%f", &equipe->membros[idx].pos.x);
    printf("Nova Posicao Y: ");
    scanf("%f", &equipe->membros[idx].pos.y);

    int opcao_nivel;
    printf("Novo Nivel (0-Iniciante, 1-Intermediario, 2-Avancado, 3-Mestre): ");
    scanf("%d", &opcao_nivel);
    getchar();
    if (opcao_nivel >= 0 && opcao_nivel <= 3) {
        equipe->membros[idx].nivel = (Nivel)opcao_nivel;
    }

    printf("Dados alterados com sucesso.\n");
}

// Função de Intercalação (Combinação):
void intercalar(Personagem *personagem, int inicio, int meio, int fim, int *comparacoes){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Vetores temporários para as duas metades
    Personagem *esquerda = (Personagem *) malloc(n1 * sizeof(Personagem));
    Personagem *direita = (Personagem *) malloc(n2 * sizeof(Personagem));

    if (esquerda == NULL || direita == NULL){
        printf("Erro ao alocar memoria durante a intercalacao.\n");
        free(esquerda);
        free(direita);
        exit(1);
    }

    // Copiando dados para os vetores temporários
    for (int x = 0; x < n1; x++) esquerda[x] = personagem[inicio + x];
    for (int y = 0; y < n2; y++) direita[y] = personagem[meio + 1 + y];

    // Índices independentes para as entradas e para a saída
    int i = 0; // Índice da esquerda
    int j = 0; // Índice da direita
    int k = inicio; // Índice do vetor principal

    // Intercala comparando os elementos
    while (i < n1 && j < n2){
        (*comparacoes)++; // Conta as comparações
        if (esquerda[i].id <= direita[j].id){
            personagem[k] = esquerda[i];
            i++;
        }else{
            personagem[k] = direita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes da esquerda
    while (i < n1){
        personagem[k] = esquerda[i];
        i++;
        k++;
    }

    // Copia os elementos restantes da direita
    while (j < n2){
        personagem[k] = direita[j];
        j++;
        k++;
    }

    free(esquerda);
    free(direita);
}

// Estrutura Recursiva do Merge Sort
void merge_sort(Personagem *personagem, int inicio, int fim, int *comparacoes){
    if (inicio < fim){
        // Dividir: Calcula corretamente o ponto médio
        int meio = inicio + (fim - inicio) / 2;

        // Resolver: Chamadas recursivas para as duas metades
        merge_sort(personagem, inicio, meio, comparacoes);
        merge_sort(personagem, meio + 1, fim, comparacoes);

        // Combinar: Intercala as partes ordenadas
        intercalar(personagem, inicio, meio, fim, comparacoes);
    }
}

void ordenar_equipe(Equipe *equipe){
    if (equipe->tamanho_atual <= 1){
        printf("\nEquipe possui elementos insuficientes para ordenacao.\n");
        return;
    }
    int comparacoes = 0;
    merge_sort(equipe->membros, 0, equipe->tamanho_atual - 1, &comparacoes);
    printf("\nEquipe ordenada por ID com sucesso! (Comparacoes: %d)\n", comparacoes);
}

void liberar_equipe(Equipe *equipe){
    if (equipe->membros != NULL){
        free(equipe->membros);
        equipe->membros = NULL;
    }
    equipe->capacidade = 0;
    equipe->tamanho_atual = 0;
}