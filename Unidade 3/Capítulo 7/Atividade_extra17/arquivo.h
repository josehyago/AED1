#ifndef ARQUIVO_H
#define ARQUIVO_H

typedef struct{
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

int salvar_partida(const char *caminho, Partida p_escrita);
int ler_partidas(const char *caminho);

#endif