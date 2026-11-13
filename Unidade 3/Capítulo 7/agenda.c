#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agenda.h"

struct no{
    Missao dado;
    struct no *prox;
};

void inicializar_lista(Lista *l){
    if (l == NULL) return;
    l->inicio = NULL;
}

int inserir_inicio(Lista *l, Missao m){
    if (l == NULL) return 0;

    No *novo = (No *) malloc(sizeof(*novo));
    if (novo == NULL) return 0;

    novo->dado = m;
    novo->prox = l->inicio;
    l->inicio = novo;

    printf("inicio agora: %s\n", l->inicio->dado.titulo); // Teste para verificar se o início da lista foi atualizado corretamente
    return 1;
}

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

/* void exibir_missao(const Missao *m){
    if (m == NULL) return;
    printf("\nID: %d | Titulo: %s | Prioridade: %d\n", m->id, m->titulo, m->prioridade);
} */