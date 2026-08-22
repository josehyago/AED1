#include <stdio.h>

void aplicar_dano(int *pvida)
{
    int dano;
    if(pvida != NULL)
    {
    printf("Selecione o dano a ser aplicado: \n");
    scanf("%d", &dano);
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

void encontrar_tesouro(int *ptesouro)
{
    if(ptesouro != NULL)
    {
        *ptesouro = *ptesouro + 1;
        printf("Endereco do tesouro na funcao tesouro: %p\n", (void*)ptesouro);
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

void indice_inventario(int *inventario[3])
{
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("Quantidade do item %d no inventario: %d\n", i + 1, *(inventario[i]));
    }

}

void ponteiro_inventario(int *inventario[3])
{
    int opcao_item, opcao_acao, quantidade;
    
    printf("Voce quer adicionar ou usar um item do inventario?\n");
    printf("Digite 1 para adicionar ou 2 para usar um item do inventario:\n");
    scanf("%d", &opcao_acao);

    printf("Escolha o item (1, 2 ou 3): ");
    scanf("%d", &opcao_item);

    if(opcao_item < 1 || opcao_item > 3) {
        printf("Item invalido.\n");
        return;
    }

    int indice = opcao_item - 1;

    if(opcao_acao == 1) 
    {
        printf("Quanto voce quer adicionar?\n");
        scanf("%d", &quantidade);

        **(inventario + indice) = **(inventario + indice) + quantidade;
        printf("Item adicionado.\n");
    }
    else if(opcao_acao == 2) 
    {
        printf("Quanto voce quer usar?\n");
        scanf("%d", &quantidade);
        
        if(quantidade > **(inventario + indice)) {
            printf("Voce nao tem quantidade suficiente, voce tem %d\n", **(inventario + indice));
        } else {

            **(inventario + indice) = **(inventario + indice) - quantidade;
            printf("Item usado.\n");
            }
    }
    else 
    {
        printf("Acao invalida.\n");
    }
}

int main()
{
    int vida, tesouro, pontuacao, dano, tamanho, altura, item1, item2, item3, opcao;
    int *pvida, *ptesouro, *ppontuacao, *paltura, *inventario[3];
    int mapa[5];

    pvida = &vida;
    ptesouro = &tesouro;
    ppontuacao = &pontuacao;
    paltura = &altura;
    inventario[0] = &item1;
    inventario[1] = &item2;
    inventario[2] = &item3;

    *pvida = 100;
    *ptesouro = 0;
    *ppontuacao = 100;
    *paltura = 0;
    tamanho = 5;
    item1 = 2;
    item2 = 15;
    item3 = 1;
    
    do{

        printf("Menu do jogo: \n");
        printf("1 - Aplicar dano\n");
        printf("2 - Restaurar vida\n");
        printf("3 - Aplicar pontuacao dupla\n");
        printf("4 - Encontrar tesouro\n");
        printf("5 - Adicionar mapa\n");
        printf("6 - Consultar inventario\n");
        printf("7 - Adicionar ou usar item do inventario\n");
        printf("8 - Estado atual\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                aplicar_dano(pvida);
                printf("Apos perder vida, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
                printf("Endereco da vida no main: %p\n", (void*)pvida);
                break;
            case 2:
                restaurar_vida(pvida);
                printf("Apos se curar, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
                printf("Endereco da vida no main: %p\n", (void*)pvida);
                break;
            case 3:
                aplicar_pontuacao_dupla(ppontuacao);
                printf("Apos pontuacao dupla, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
                printf("Endereco da pontuacao no main: %p\n", (void*)ppontuacao);
                break;
                case 4:
                encontrar_tesouro(ptesouro);
                printf("Apos encontrar tesouro, seu estado e: vida = %d, tesouro = %d e pontuacao = %d\n", *pvida, *ptesouro, *ppontuacao);
                printf("Endereco do tesouro no main: %p\n", (void*)ptesouro);
                break;
            case 5:
                ler_mapa(mapa, tamanho);
                mostrar_mapa(mapa, tamanho);
                explorar_mapa(mapa, tamanho, paltura, ppontuacao);
                break;
            case 6:
                indice_inventario(inventario);
                break;
            case 7:
                ponteiro_inventario(inventario);
                break;
            case 8:
                printf("Estado atual:\n");
                printf("Vida: %d\n", *pvida);
                printf("Tesouro: %d\n", *ptesouro);
                printf("Pontuacao: %d\n", *ppontuacao);
                printf("Altura: %d\n", *paltura);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    }while(opcao != 0 && *pvida > 0);

    printf("Fim do jogo! Seu estado final e: vida = %d, tesouro = %d, altura = %d, pontuacao = %d\n", *pvida, *ptesouro, *paltura, *ppontuacao);

    return 0;
}