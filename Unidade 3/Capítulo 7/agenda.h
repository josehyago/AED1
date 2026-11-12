#ifndef AGENDA_H
#define AGENDA_H

#define TAM_TITULO 100

typedef struct{
    int id;
    char titulo[TAM_TITULO];
    int prioridade;
} Missao;

Missao criar_missao(int id, const char *titulo, int prioridades);
void exibir_missao(const Missao *m);

#endif