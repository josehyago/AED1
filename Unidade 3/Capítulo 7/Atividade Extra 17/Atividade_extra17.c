/*
 Capítulo 7 - Biblioteca modular de lista encadeada
 Atividade de Sala de Aula

 - Utilize um código que você tenha implementado e separe em módulos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

int main(){
    Partida p;

    printf("Digite as informacoes da partida (ID, Nome, Pontuacao): ");
    if (scanf("%d %49s %d", &p.id, p.jogador, &p.pontuacao) != 3){
        printf("Entrada invalida.\n");
        return 1;
    }

    const char *arquivo = "./partidas.txt";

    if (salvar_partida(arquivo, p)){
        printf("\nPartida salva com sucesso em '%s'.\n", arquivo);
    }

    ler_partidas(arquivo);

    return 0;
}