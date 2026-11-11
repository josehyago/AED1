/*
 Capítulo 7 - Biblioteca modular de lista encadeada
 Atividade Extra - Pilha

 - Realize a atividade 52.
 Atividade 52 — Operações fundamentais da pilha
 
 Contexto: Um atendente precisa manter um histórico das ações recentes. A ação executada por último deve ser a primeira disponível para consulta ou remoção, seguindo a regra LIFO.
 Descrição detalhada: Crie do zero uma pilha encadeada de ações. Implemente inicialização, inserção no topo, exibição do topo até a base e remoção do topo. Defina um retorno que permita ao chamador saber quando não havia elemento para remover.
 Requisitos:
 - definir dados da ação, nó e pilha;
 - iniciar o topo com NULL;
 - alocar e encadear no push;
 - percorrer sem alterar a pilha na exibição;
 - atualizar o topo e liberar o nó no pop;
 - testar pilha vazia, um elemento e vários elementos.
*/

#include <stdio.h>
#include <stdlib.h>

struct No{
    int dado;
    struct No* prox;
};

struct Pilha{
    struct No* topo;
};

void inicializa(struct Pilha* pilha){
    pilha->topo = NULL;
}

void adiciona(struct Pilha* pilha, int dado){
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    if (novo == NULL){
        printf("Erro de alocacao de memoria\n");
        return;
    }
    novo->dado = dado;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int remover(struct Pilha* pilha){
    if (pilha->topo == NULL){
        printf("Pilha vazia\n");
        return 0;
    }
    struct No* temp = pilha->topo;
    pilha->topo = temp->prox;
    free(temp);
    return 1;
}

void mostrar(struct Pilha* pilha){
    struct No* pi;
    for (pi = pilha->topo; pi != NULL; pi = pi->prox){
        printf("[%d] ", pi->dado);
    }
    printf("\n");
}

int main(){
    struct Pilha pilha;
    inicializa(&pilha);
    adiciona(&pilha, 10);
    adiciona(&pilha, 5);
    mostrar(&pilha);
    remover(&pilha);
    mostrar(&pilha);
    remover(&pilha);
    remover(&pilha);
    return 0;
}