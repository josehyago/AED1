#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct no{
    int dado;
    struct no* prox;
};

struct pilha{
    No* topo;
};

Pilha *criarPilha(){
    Pilha* pilha = (Pilha *) malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void adicionar(Pilha* pilha, int dado){
    No* novo = (No *) malloc(sizeof(No));
    novo->dado = dado;
    novo->prox = NULL;
    if(pilha->topo == NULL){
        pilha->topo = novo;
    } else {
        novo->prox = pilha->topo;
        pilha->topo = novo;
    } 
}

void remover(Pilha* pilha){
    if(pilha->topo == NULL){
        printf("Pilha vazia!\n");
    } else {
        No* temp = pilha->topo;
        pilha->topo = temp->prox;
        free(temp);
    }
}

void mostrar(Pilha* pilha){
    No* atual = pilha->topo;
    while(atual != NULL){
        printf("%d\n", atual->dado);
        atual = atual->prox;
    }
}