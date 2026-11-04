/*
 Capítulo 7 - Biblioteca modular de lista encadeada
 Atividade Sala de Aula - Realize a Atividade 43

 - Realize a atividade 43. Ao vez de inserir no fim da lista, insira o nó no início.
 Atividade 43 — Exibição e inserção no fim
 
 Contexto: O coordenador precisa visualizar a ordem atual das missões e acrescentar tarefas que serão tratadas depois de todas as já cadastradas.
 Descrição detalhada: Acrescente uma função que percorra a lista do início até NULL e mostre todos os dados. Depois, implemente a inserção no fim, tratando separadamente a lista vazia e a lista que já contém nós.
 Requisitos:
 - usar um ponteiro auxiliar no percurso;
 - não alterar o ponteiro de início durante a exibição;
 - informar quando a lista estiver vazia;
 - fazer o novo nó apontar para NULL;
 - localizar e atualizar o último nó;
 - testar uma sequência que misture inserções no início e no fim.
*/

#include <stdio.h>
#include <stdlib.h>

struct No{
    int valor;
    struct No* prox;
};

struct Lista{
    struct No* inicio;
};

void adicionaInicio(struct Lista *lista, int valor){
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    novo->prox = NULL;
    novo->valor = valor;
    if (lista->inicio == NULL){
        lista->inicio = novo;
    }
    else{
    struct No* pi;
    pi = lista->inicio;
    lista->inicio = novo;
    novo->prox = pi;
    }
}

void mostrar(struct Lista *lista){
    for (struct No *pi = lista->inicio; pi != NULL; pi = pi->prox){
        printf("%d ", pi->valor);
    }
}

int main(){
    struct Lista lista;
    lista.inicio = NULL;
    adicionaInicio(&lista, 10);
    adicionaInicio(&lista, 5);
    adicionaInicio(&lista, 3);
    adicionaInicio(&lista, 2);
    mostrar(&lista);
    return 0;
}