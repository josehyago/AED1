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

void ler_mapa(int *mapa, int tamanho)
{
    int i;
    for(i = 0; i < tamanho; i++)
    {
        printf("Digite o valor do mapa na posicao %d: \n", i);
        scanf("%d", (mapa + i));
        if(*(mapa + i) < 0)
        {
            printf("Valor invalido, digite um valor positivo.\n");
            i--;
        }
    }


}

void mostrar_mapa(const int *mapa, int tamanho)
{
    int i;
    for(i = 0; i < tamanho; i++)
    {
        printf("Valor do mapa na posicao %d: %d\n", i, *(mapa + i));
    }
}

int main()
{
    int vida, tesouro, pontuacao, dano, tamanho, altura, i;
    int *pvida, *ptesouro, *ppontuacao;
    int mapa[5];

    pvida = &vida;
    ptesouro = &tesouro;
    ppontuacao = &pontuacao;

    *pvida = 100;
    *ptesouro = 0;
    *ppontuacao = 100;
    tamanho = 5;
    altura = 0;
    i = 0;

    ler_mapa(mapa, tamanho);
    mostrar_mapa(mapa, tamanho);

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

    for(i = 0; i < tamanho; i++) //O deslocamento respeita o tipo de ponteiro porque o compilador sabe que um vetor tipo int ocupa 4 bytes na memória, então quando colocamos a instrução *(mapa + i), o compilador entende que é pra pular 4 bytes * i, indo para o próximo elemento do vetor.
    {
        printf("indice: %d\n endereco: %p\n valor: %d\n", i, (void*)(mapa + i), *(mapa + i));
        altura = altura + *(mapa + i);
        *ppontuacao = *ppontuacao + *(mapa + i);
    }

    printf("Altura total: %d\n", altura);
    printf("Pontuacao final: %d\n", *ppontuacao);

    return 0;
}