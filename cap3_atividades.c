// Capítulo 3 — Catalágo dinâmico de personagens
// Atividade 19 — Equipe como vetor dinâmico de estruturas

// Contexto: O catálogo precisa deixar de tratar apenas um personagem e passar a administrar uma equipe inteira, cuja quantidade pode crescer durante a execução.
// Descrição detalhada: Transforme o armazenamento preparado na A…4438 tokens truncated…*Descrição detalhada: Implemente uma função que receba dois vetores ordenados e produza um terceiro também ordenado. Em seguida, crie a estrutura recursiva que divide um intervalo em duas metades, ainda que a ordenação completa seja concluída na próxima atividade.
// Requisitos:
// - manter índices independentes para as duas entradas;
// - copiar os elementos restantes quando uma entrada terminar;
// - produzir saída com todos os valores;
// - calcular corretamente o ponto médio;
// - identificar em comentários as etapas dividir, resolver e combinar;
// - contar comparações da intercalação.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char nome[50];
    int vida;
    int pontuacao;
    float posicao_x;
    float posicao_y;
} Personagem;

Personagem construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y);
void exibir_personagem(Personagem personagem);

void simular_dano(Personagem personagem);

void vida(Personagem *personagem, int quantidade);
void pontuacao(Personagem *personagem, int quantidade);
void posicao(Personagem *personagem, float posx, float posy);

void intercalar(Personagem *vetor, int inicio, int meio, int fim, int *comparacoes);
void merge_sort(Personagem *vetor, int inicio, int fim, int *comparacoes);

int main(){
    int capacidade, capacidade_nova, comparacoes, i;
    capacidade = 5;
    comparacoes = 0;
    char nome_novo[50];

    Personagem exemplo = {0, "Inicializacao posicional ou designada", 100, 0, 0.0, 0.0};
    (void)exemplo;

    Personagem *personagem = (Personagem *) calloc(capacidade, sizeof(Personagem));

    if(personagem == NULL){
        printf("Nao ha memoria suficiente");
        exit (1);
    }

    personagem[0] = construir_personagem(3, "Hyago", 80, 0, 10.5, 5.0);
    personagem[1] = construir_personagem(4, "Margarida", 100, 800, 5.0, 3.0);
    personagem[2] = construir_personagem(2, "Gabriel", 85, 600, 2.0, 4.0);
    personagem[3] = construir_personagem(1, "Ana Paula", 95, 750, 4.0, 1.0);
    personagem[4] = construir_personagem(5, "Samuel", 40, 200, 6.0, 5.0);

    printf("\nEstado Inicial (Externo): \n");
    exibir_personagem(personagem[0]);

    vida(&personagem[0], 50);
    pontuacao(&personagem[0], 300);
    posicao(&personagem[0], 2.0, 0.0);

    printf("Estado apos eventos: \n");
    exibir_personagem(personagem[0]);

    simular_dano(personagem[0]);
    printf("\nEstado Externo apos a funcao:\n");
    exibir_personagem(personagem[0]);

    // Efeito e Custo da Cópia (Passagem por Valor): O efeito positivo é a segurança: a função trabalha com um clone dos dados, garantindo que o registro original no main não seja alterado acidentalmente. 
    // O custo é a performance e memória: a cada chamada da função, o programa precisa alocar espaço e copiar todos os bytes da estrutura (int, char[50], floats). Em estruturas muito grandes ou em chamadas frequentes, isso consome muito processamento, sendo preferível usar ponteiros.

    printf("\nEquipe antes da ordenacao:\n");
    for (int i = 0; i < capacidade; i++) {
        exibir_personagem(personagem[i]);
    }

    merge_sort(personagem, 0, capacidade - 1, &comparacoes);

    printf("\nEquipe apos Merge Sort (Ordenada por ID):\n");
    for (int i = 0; i < capacidade; i++) {
        exibir_personagem(personagem[i]);
    }

    printf("\nTotal de comparacoes realizadas na intercalacao: %d\n", comparacoes);

    printf("\nDigite a nova capacidade: ");
    scanf("%d", &capacidade_nova);
    getchar();

    if(capacidade_nova <= 0){
        printf("Capacidade invalida.");
        free(personagem);
        exit(1);
    }

        Personagem *personagem_temporario = (Personagem *) realloc(personagem, capacidade_nova * sizeof(Personagem));

        if (personagem_temporario == NULL){
        printf("Nao ha memoria suficiente para realocar.\n");
        free(personagem);
        exit(1);
    }
        personagem = personagem_temporario;

        if (capacidade_nova > capacidade) {
        for (i = capacidade; i < capacidade_nova; i++) {
            personagem[i] = construir_personagem(0, "", 0, 0, 0.0, 0.0);
        }
    }

        printf("Capacidade Anterior = %d | Capacidade Nova = %d\n", capacidade, capacidade_nova);
        capacidade = capacidade_nova;

        printf("\nDigite o novo nome para o personagem 1: ");
        fgets(nome_novo, sizeof(nome_novo), stdin);
        nome_novo[strcspn(nome_novo, "\n")] = '\0';

        strncpy(personagem[0].nome, nome_novo, sizeof(personagem[0].nome) - 1);
        personagem[0].nome[sizeof(personagem[0].nome) - 1] = '\0';

        printf("\nRegistro Apos Alteracao: \n");
        exibir_personagem(personagem[0]);

    free(personagem);
    personagem = NULL;

    return 0;
}

Personagem construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y){
    Personagem novo_personagem;
    
    novo_personagem.id = id;

    strncpy(novo_personagem.nome, nome, sizeof(novo_personagem.nome) - 1);
    novo_personagem.nome[sizeof(novo_personagem.nome) - 1] = '\0';

    novo_personagem.vida = vida;
    novo_personagem.pontuacao = pontuacao;
    novo_personagem.posicao_x = posicao_x;
    novo_personagem.posicao_y = posicao_y;

    return novo_personagem;
}

void exibir_personagem(Personagem personagem){
    printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", 
           personagem.id, personagem.nome, personagem.vida, personagem.pontuacao, personagem.posicao_x, personagem.posicao_y);
}

void simular_dano(Personagem personagem){
    printf("\nDentro da funcao simular_dano:\n");
    printf("O personagem sofreu um ataque.\n");
    
    personagem.vida -= 30; 
    
    printf("Estado Interno (Copia): \n");
    exibir_personagem(personagem);
}

void vida(Personagem *personagem, int quantidade){
    if(personagem == NULL) return;
    
    personagem->vida += quantidade;

    if(quantidade < 0) printf("Seu personagem sofreu %d de dano\n", quantidade);
    if(quantidade > 0) printf("Seu personagem ganhou %d de vida\n", quantidade);

    if (personagem->vida > 100) personagem->vida = 100;
    else if (personagem->vida < 0) personagem->vida = 0;
}

void pontuacao(Personagem *personagem, int quantidade){
    if(personagem == NULL) return;
    
    personagem->pontuacao += quantidade;

    if(quantidade > 0) printf("Seu personagem ganhou %d de pontuacao\n", quantidade);
    if(quantidade < 0) printf("Seu personagem perdeu %d de pontuacao\n", quantidade);

    if (personagem->pontuacao < 0) personagem->pontuacao = 0;
}

void posicao(Personagem *personagem, float posx, float posy){
    if(personagem == NULL) return;

    if(posx != 0 || posy != 0){
    (*personagem).posicao_x += posx; //Equivalência com (->)
    personagem->posicao_y += posy;
    }

    if(posx > 0) printf("Seu personagem andou pra frente (+%2.0f no eixo x)\n", posx);
    if(posx < 0) printf("Seu personagem andou pra tras (-%2.0f no eixo x)\n", posx);
    if(posy > 0) printf("Seu personagem pulou pra cima (+%2.0f no eixo y)\n", posy);
    if(posy < 0) printf("Seu personagem pulou pra baixo (-%2.0f no eixo y)\n", posy);
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
void merge_sort(Personagem *personagem, int inicio, int fim, int *comparacoes) {
    if (inicio < fim) {
        // Dividir: Calcula corretamente o ponto médio
        int meio = inicio + (fim - inicio) / 2;

        // Resolver: Chamadas recursivas para as duas metades
        merge_sort(personagem, inicio, meio, comparacoes);
        merge_sort(personagem, meio + 1, fim, comparacoes);

        // Combinar: Intercala as partes ordenadas
        intercalar(personagem, inicio, meio, fim, comparacoes);
    }
}