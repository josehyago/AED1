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