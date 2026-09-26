/* 
 Capítulo 1 - Sistema de exploração com ponteiros e vetores
 Atividade 2 - Endereços e funções que alteram o estado
 
 Contexto: À medida que o simulador cresce, concentrar todas as alterações na função main dificulta a manutenção. Um motor de jogo normalmente delega dano, cura e bônus a funções especializadas que recebem o estado a ser modificado.
 Descrição detalhada: Continue o código da Atividade 01 e transforme as alterações de estado em funções. Cada função deve receber o endereço da variável original e alterar seu conteúdo. O programa também deverá imprimir endereços de memória para demonstrar que a função e a main trabalham sobre o mesmo dado.
 Requisitos:
 - imprimir endereços com %p, convertendo-os para (void *);
 - implementar aplicar_dano(int *vida, int dano);
 - implementar restaurar_vida(int *vida);
 - criar uma pontuação e aplicar_pontuacao_dupla(int *pontuacao);
 - validar ponteiros antes de acessá-los;
 - demonstrar que as variáveis da main foram realmente atualizadas.
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
    int vida, tesouro, pontuacao, dano;
    int *pvida, *ptesouro, *ppontuacao;
    pvida = &vida;
    ptesouro = &tesouro;
    ppontuacao = &pontuacao;
    *pvida = 100;
    *ptesouro = 0;
    *ppontuacao = 100;
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
    return 0;
}