#ifndef PILHA_H
#define PILHA_H

typedef struct no No;
typedef struct pilha Pilha;

Pilha *criarPilha();
void adicionar(Pilha* pilha, int dado);
void remover(Pilha* pilha);
void mostrar(Pilha* pilha);

#endif