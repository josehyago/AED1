#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

int salvar_partida(const char *caminho, Partida p_escrita){
    FILE *file = fopen(caminho, "w");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 0; // Falha
    }

    fprintf(file, "ID: %d | Nome: %s | Pontuacao: %d\n", p_escrita.id, p_escrita.jogador, p_escrita.pontuacao);

    fclose(file);
    return 1; // Sucesso
}

int ler_partidas(const char *caminho){
    FILE *file = fopen(caminho, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return 0; // Falha
    }

    Partida p_leitura;
    printf("\nDados Recuperados do Arquivo:\n");

    while (fscanf(file, "ID: %d | Nome: %49s | Pontuacao: %d", &p_leitura.id, p_leitura.jogador, &p_leitura.pontuacao) == 3) {
        printf("ID: %d | Jogador: %s | Pontuacao: %d\n", p_leitura.id, p_leitura.jogador, p_leitura.pontuacao);
    }

    fclose(file);
    return 1; // Sucesso
}