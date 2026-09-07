// Capítulo 3 — Catalágo dinâmico de personagens
// Atividade 15 - Definição e alteração de personagens

// Contexto: Uma pontuação isolada não é suficiente para representar um personagem. O catálogo deve agrupar em um único registro todos os dados que descrevem cada participante do jogo.
// Descrição detalhada: Defina uma estrutura com identificador, nome, vida, pontuação e posição. Crie um personagem de exemplo, mostre seus dados e realize alterações controladas. O objetivo é observar como membros de tipos diferentes formam uma única unidade lógica.
// Requisitos:
// - declarar a struct antes das funções que a utilizam;
// - criar e preencher ao menos um personagem;
// - acessar membros com o operador ponto;
// - alterar vida, pontuação e posição;
// - exibir o estado antes e depois;
// - preservar valores dentro de limites coerentes.

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

int main(){
    int capacidade, capacidade_nova, i;
    capacidade = 5;

    struct Catalogo *personagem = (struct Catalogo *) calloc(capacidade, sizeof(struct Catalogo));

    if(personagem == NULL){
        printf("Nao ha memoria suficiente");
        exit (1);
    }

    personagem[0].id = 1;
    strcpy(personagem[0].nome, "Hyago");
    personagem[0].vida = 80;
    personagem[0].pontuacao = 0;
    personagem[0].posicao_x = 10.5;
    personagem[0].posicao_y = 5.0;

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
            personagem[i].id = 0;
            personagem[i].nome[0] = '\0';
            personagem[i].vida = 0;
            personagem[i].pontuacao = 0;
            personagem[i].posicao_x = 0.0;
            personagem[i].posicao_y = 0.0;
        }
    }

        printf("Capacidade Anterior = %d | Capacidade Nova = %d\n", capacidade, capacidade_nova);

    free(personagem);
    personagem = NULL;

    return 0;
}