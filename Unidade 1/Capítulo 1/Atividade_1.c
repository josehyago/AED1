/* 
 Capítulo 1 - Sistema de exploração com ponteiros e vetores
 Atividade 1 - Estado do jogador e acesso indireto

 Contexto: Em um jogo de exploração, a vida e os tesouros do jogador fazem parte de um estado compartilhado. Diferentes partes do programa precisam modificar esses valores diretamente, sem trabalhar apenas com cópias temporárias.
 Descrição detalhada: Crie do zero a primeira versão do simulador. O programa deverá manter a vida do jogador e indicar se um tesouro está ativo. Depois de exibir o estado inicial, ele deve simular dano, restauração e ativação do tesouro por meio de ponteiros. O objetivo é tornar visível a relação entre a variável, seu endereço e o conteúdo acessado indiretamente.
 Requisitos:
 - declarar vida, quantidade ou estado de tesouros e ponteiros compatíveis;
 - inicializar a vida com 100 e o tesouro como inativo;
 - associar cada ponteiro ao endereço da variável correspondente;
 - aplicar dano e restaurar a vida usando *ponteiro;
 - ativar o tesouro sem alterar diretamente sua variável na operação principal;
 - mostrar os valores antes e depois de cada mudança. 
*/

#include <stdio.h>

int main()
{
    int vida, tesouro;
    int *pvida, *ptesouro;
    pvida = &vida;
    ptesouro = &tesouro;
    *pvida = 100;
    *ptesouro = 0;
    printf("Seu estado inicial e: vida = %d e tesouro = %d\n", *pvida, *ptesouro);
    *pvida = *pvida - 50;
    printf("Apos perder vida, seu estado e: vida = %d e tesouro = %d\n", *pvida, *ptesouro);
    *pvida = *pvida + 50;
    printf("Apos se curar, seu estado e: vida = %d e tesouro = %d\n", *pvida, *ptesouro);
    *ptesouro = 1;
    printf("Apos encontrar tesouro, seu estado e: vida = %d e tesouro = %d\n", *pvida, *ptesouro);
    return 0;
}