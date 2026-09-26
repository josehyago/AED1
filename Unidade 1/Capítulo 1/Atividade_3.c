/*
 Capítulo 1 - Sistema de exploração com ponteiros e vetores
 Atividade 3 - Percorrendo o mapa com aritmética de ponteiros

 Contexto: O mundo do jogo passa a ser representado por uma sequência de plataformas. Cada posição fornece um impulso ou uma quantidade de pontos, e o programa precisa percorrer toda a sequência para calcular o resultado da exploração.
 Descrição detalhada: Acrescente ao simulador um vetor com valores associados às plataformas. Percorra-o usando aritmética de ponteiros, mostre o endereço de cada elemento e acumule os resultados obtidos pelo jogador. Nesta atividade, o cálculo principal não deverá usar a notação de colchetes.
 Requisitos:
 - criar um vetor com pelo menos cinco valores;
 - acessar os elementos com *(vetor + i);
 - calcular pontuação e altura total do percurso;
 - mostrar índice, endereço e conteúdo de cada posição;
 - explicar em um comentário por que o deslocamento respeita o tipo do ponteiro;
 - preservar as funcionalidades das atividades anteriores.
*/

#include <stdio.h>

void aplicar_dano(int *pvida, int dano)
{
    if(pvida != NULL)
    {
    *pvida = *pvida - dano;
    printf("Endereco da vida na funcao aplicar_dano: %p\n", (void*)pvida);
    }
}

void restaurar_vida(int *pvida)
{
    int cura = 0;
    if(pvida != NULL)
    {
    if (*pvida < 100){
        cura = 100 - *pvida;
        *pvida = *pvida + cura;
    }
    printf("Endereco da vida na funcao restaurar_vida: %p\n", (void*)pvida);
    }
}

void aplicar_pontuacao_dupla(int *ppontuacao)
{
    if(ppontuacao != NULL)
    {
        *ppontuacao = *ppontuacao * 2;
        printf("Endereco da pontuacao na funcao aplicar_pontuacao_dupla: %p\n", (void*)ppontuacao);
    }
}

int main()
{
    int vida, tesouro, pontuacao, dano, altura, i;
    int *pvida, *ptesouro, *ppontuacao;
    int plataformas[5] = {10, 20, 15, 30, 25};

    pvida = &vida;
    ptesouro = &tesouro;
    ppontuacao = &pontuacao;

    *pvida = 100;
    *ptesouro = 0;
    *ppontuacao = 100;
    altura = 0;
    i = 0;

    printf("Seu estado inicial e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);

    aplicar_dano(pvida, 50);

    printf("Apos perder vida, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
    printf("Endereco da vida no main: %p\n", (void*)pvida);

    restaurar_vida(pvida);

    printf("Apos se curar, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
    printf("Endereco da vida no main: %p\n", (void*)pvida);

    *ptesouro = 1;

    printf("Apos encontrar tesouro, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);

    aplicar_pontuacao_dupla(ppontuacao);

    printf("Apos pontuacao dupla, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
    printf("Endereco da pontuacao no main: %p\n", (void*)ppontuacao);

    for(i = 0; i < 5; i++) //O deslocamento respeita o tipo de ponteiro porque o compilador sabe que um vetor tipo int ocupa 4 bytes na memória, então quando colocamos a instrução *(plataformas + i), o compilador entende que é pra pular 4 bytes * i, indo para o próximo elemento do vetor.
    {
        printf("indice: %d\n endereco: %p\n valor: %d\n", i, (void*)(plataformas + i), *(plataformas + i));
        altura = altura + *(plataformas + i);
        *ppontuacao = *ppontuacao + *(plataformas + i);
    }

    printf("Altura total: %d\n", altura);
    printf("Pontuacao final: %d\n", *ppontuacao);

    return 0;
}
