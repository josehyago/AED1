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

    return 1;
}

int inserir_fim(Lista *l, Missao m){
    if (l == NULL) return 0;

    No *novo = (No *) malloc(sizeof(*novo));
    if (novo == NULL) return 0;

    novo->dado = m;
    novo->prox = NULL;

    if (l->inicio == NULL){
        l->inicio = novo;
        return 1;
    }

    No *ultimo = l->inicio;
    while (ultimo->prox != NULL){
        ultimo = ultimo->prox;
    }
    ultimo->prox = novo;
    return 1;
}

void exibir_lista(const Lista *l){
    if (l == NULL) return;
    if (l->inicio == NULL){ 
        printf("Lista vazia!\n"); 
        return;
    }

    for (No *pi = l->inicio; pi != NULL; pi = pi->prox){
        exibir_missao(&pi->dado);
    }
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

void exibir_missao(const Missao *m){
    if (m == NULL) return;
    printf("ID: %d | Titulo: %s | Prioridade: %d\n", m->id, m->titulo, m->prioridade);
}