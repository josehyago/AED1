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

void explorar_mapa(int *mapa, int tamanho, int *paltura, int *ppontuacao)
{
    int *cursor = mapa;
    int i;
    for(i = 0; i < tamanho; i++)
    {
        printf("indice: %d\n endereco: %p\n valor: %d\n", i, (void*)(cursor), *cursor);
       *paltura = *paltura + *cursor;
        *ppontuacao = *ppontuacao + *cursor;
        cursor++;

        //Incremento de ponteiro: cursor ++ o compilador não precisa calcular nada desde o início, ele apenas incrementa no endereço atual.
        //Acesso por índice: *(mapa + i) o compilador precisa calcular o endereço desde o início, somando o tamanho do tipo de dado (int) vezes o índice.
    
    }

}

int main()
{
    int vida, tesouro, pontuacao, dano, tamanho, altura, i;
    int *pvida, *ptesouro, *ppontuacao, *paltura;
    int mapa[5];

    pvida = &vida;
    ptesouro = &tesouro;
    ppontuacao = &pontuacao;
    paltura = &altura;

    *pvida = 100;
    *ptesouro = 0;
    *ppontuacao = 100;
    *paltura = 0;
    tamanho = 5;

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

    explorar_mapa(mapa, tamanho, paltura, ppontuacao);

    printf("Resumo do percurso: vida = %d, tesouro = %d, altura = %d, pontuacao = %d\n", *pvida, *ptesouro, *paltura, *ppontuacao);
    
    return 0;
}