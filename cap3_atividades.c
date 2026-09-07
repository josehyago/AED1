// Capítulo 3 — Catalágo dinâmico de personagens
// Atividade 16 - Inicialização e atualização de membros textuais

// Contexto: A criação manual de cada registro aumenta a chance de deixar campos sem valor. Além disso, o nome do personagem pode mudar durante o jogo, mas deve permanecer dentro do espaço reservado.
// Descrição detalhada: Padronize a inicialização dos registros na declaração e por meio de uma função que devolva um personagem completamente preenchido. Implemente também uma operação segura para trocar o nome, cuidando da entrada e do limite do vetor de caracteres.
// Requisitos:
// - demonstrar inicialização posicional ou designada;
// - criar uma função construtora de Personagem;
// - inicializar todos os membros;
// - ler o novo nome com segurança;
// - validar ou limitar a cópia do texto;
// - exibir o registro completo após a alteração.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Catalogo{
    int id;
    char nome[50];
    int vida;
    int pontuacao;
    float posicao_x;
    float posicao_y;
};

struct Catalogo construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y){
    struct Catalogo novo_personagem;
    
    novo_personagem.id = id;

    strncpy(novo_personagem.nome, nome, sizeof(novo_personagem.nome) - 1);
    novo_personagem.nome[sizeof(novo_personagem.nome) - 1] = '\0';

    novo_personagem.vida = vida;
    novo_personagem.pontuacao = pontuacao;
    novo_personagem.posicao_x = posicao_x;
    novo_personagem.posicao_y = posicao_y;

    return novo_personagem;
}

int main(){
    int capacidade, capacidade_nova, i;
    capacidade = 5;
    char nome_novo[50];

    struct Catalogo exemplo = {0, "Inicializacao posicional ou designada", 100, 0, 0.0, 0.0};
    (void)exemplo;

    struct Catalogo *personagem = (struct Catalogo *) calloc(capacidade, sizeof(struct Catalogo));

    if(personagem == NULL){
        printf("Nao ha memoria suficiente");
        exit (1);
    }

    personagem[0] = construir_personagem(1, "Hyago", 80, 0, 10.5, 5.0);

    printf("\nEstado Inicial: \n");
    printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", personagem[0].id, personagem[0].nome, personagem[0].vida, personagem[0].pontuacao, personagem[0].posicao_x, personagem[0].posicao_y);

    printf("Aplicando item de cura (+50 de vida)\n");
    personagem[0].vida += 50; 
    
    printf("Aplicando pontuacao (+300 pontos)\n");
    personagem[0].pontuacao += 300;

    printf("Personagem andou para frente (+2 no eixo x)\n");
    personagem[0].posicao_x += 2.0;

    if (personagem[0].vida > 100){
        personagem[0].vida = 100;
    }
    if (personagem[0].pontuacao < 0){
        personagem[0].pontuacao = 0;
    }

    printf("Estado apos eventos: \n");
    printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", personagem[0].id, personagem[0].nome, personagem[0].vida, personagem[0].pontuacao, personagem[0].posicao_x, personagem[0].posicao_y);

    printf("Digite a nova capacidade: ");
    scanf("%d", &capacidade_nova);
    getchar();

    if(capacidade_nova <= 0){
        printf("Capacidade invalida.");
        free(personagem);
        exit(1);
    }

        struct Catalogo *personagem_temporario = (struct Catalogo *) realloc(personagem, capacidade_nova * sizeof(struct Catalogo));

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

        printf("\nDigite o novo nome para o personagem 1: ");
        fgets(nome_novo, sizeof(nome_novo), stdin);
        nome_novo[strcspn(nome_novo, "\n")] = '\0';

        strncpy(personagem[0].nome, nome_novo, sizeof(personagem[0].nome) - 1);
        personagem[0].nome[sizeof(personagem[0].nome) - 1] = '\0';

        printf("\nRegistro Apos Alteracao: \n");
        printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", personagem[0].id, personagem[0].nome, personagem[0].vida, personagem[0].pontuacao, personagem[0].posicao_x, personagem[0].posicao_y);

    free(personagem);
    personagem = NULL;

    return 0;
}