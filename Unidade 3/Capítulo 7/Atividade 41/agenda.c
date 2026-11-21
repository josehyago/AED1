#include <stdio.h>
#include <string.h>
#include "agenda.h"

Missao criar_missao(int id, const char *titulo, int prioridade){
    Missao m;

    m.id = id;
    m.prioridade = prioridade;

    if (titulo == NULL) m.titulo[0] = '\0';
        else { 
            strncpy(m.titulo, titulo, TAM_TITULO - 1);
            m.titulo[TAM_TITULO - 1] = '\0';
    }
    return m;
}

void exibir_missao(const Missao *m){
    if (m == NULL) return;
    printf("\nID: %d | Titulo: %s | Prioridade: %d\n", m->id, m->titulo, m->prioridade);
}