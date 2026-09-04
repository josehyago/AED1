//Capítulo 3 — Catalágo dinâmico de personagens
//Atividade 15 - Definição e alteração de personagens
#include <stdio.h>
#include <string.h>

struct jogador {
    int id;
    char nome[20];
    int vida;
    int pontuacao;
    int posicao;
};

void exibirEstado(struct jogador j)
{
    printf("ID: %d | Nome: %s | Vida: %d | Pontuacao: %d | Posicao: %d\n", j.id, j.nome, j.vida, j.pontuacao, j.posicao);
}

void ganho_vida(int *vida)
{
    *vida = *vida + 5;
    if(*vida > 100){
        *vida = 100;
    }
}

void altera_pontuacao_posicao(int *pontuacao, int *posicao)
{
    *pontuacao = *pontuacao + 50;
    *posicao = *posicao + 1;
}

int main(){
    struct jogador j;

    printf("Digite o ID do jogador: ");
    scanf("%d", &j.id);
    getchar();
    
    printf("Digite o nome do jogador: ");
    fgets(j.nome, sizeof(j.nome), stdin);
    j.nome[strcspn(j.nome, "\n")] = '\0';
    
    printf("Digite a vida, pontuacao e posicao: ");
    scanf("%d %d %d", &j.vida, &j.pontuacao, &j.posicao);

    printf("\nEstado anterior:\n");
    exibirEstado(j);

    printf("\nAplicando alteracoes.");
    ganho_vida(&j.vida);
    altera_pontuacao_posicao(&j.pontuacao, &j.posicao);

    printf("\nEstado Atual\n");
    exibirEstado(j);

    return 0;
}