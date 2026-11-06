/*
 Capítulo 7 - Biblioteca modular de lista encadeada
 Atividade Sala de Aula - Realize a Atividade 55

 - Realize a atividade 55 - Fila.
 Atividade 55 — Operações fundamentais da fila
 
 Contexto: Jogadores aguardando suporte devem ser atendidos na ordem de chegada. Diferentemente da pilha, a fila insere no fim e remove no início, seguindo a regra FIFO.
 Descrição detalhada: Acrescente ao mesmo programa uma fila encadeada com ponteiros de início e fim. Implemente inserção, exibição e remoção, tratando cuidadosamente a transição entre fila vazia, fila com um elemento e fila com vários elementos.
 Requisitos:
 - definir jogador, nó e fila;
 - inicializar inicio e fim com NULL;
 - inserir sempre no fim;
 - percorrer do início ao fim sem alterar a fila;
 - remover e liberar o nó inicial;
 - atribuir NULL também ao fim quando o último elemento for removido.
*/

#include <stdio.h>
#include <stdlib.h>

struct Jogador{
    int id;
};

struct No{
    struct Jogador jogador;
    struct No* prox;
};

struct Fila{
    struct No* inicio;
    struct No* fim;
};

void adicionaFim(struct Fila *fila, int id){
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    if (novo == NULL){
        printf("Erro de alocação de memória!\n");
        return;
    }
    novo->prox = NULL;
    novo->jogador.id = id;
    if (fila->inicio == NULL){
        fila->inicio = novo;
        fila->fim = novo;   
    }
    else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

void remover(struct Fila *fila){
    if (fila->inicio == NULL){
        printf("Fila vazia, Nao ha o que ser removido\n");
    }
    else{
        struct No* pi = fila->inicio;
        fila->inicio = pi->prox;

        if (fila->inicio == NULL){
            fila->fim = NULL;
        }
        free(pi);
    }
}

void mostrar(struct Fila *fila){
    if (fila->inicio == NULL){
        printf("Fila vazia!\n");
        return;
    }
    for (struct No *pi = fila->inicio; pi != NULL; pi = pi->prox){
        printf("%d ", pi->jogador.id);
    }
    printf("\n");
}

int main(){
    struct Fila fila;
    fila.inicio = NULL;
    remover(&fila); 
    adicionaFim(&fila, 10);
    adicionaFim(&fila, 5);
    adicionaFim(&fila, 3);
    adicionaFim(&fila, 2);
    remover(&fila);
    mostrar(&fila);
    return 0;
}