#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main(){
    Pilha *pilha = criarPilha();
    adicionar(pilha, 10);
    adicionar(pilha, 5);
    mostrar(pilha);
    remover(pilha);
    mostrar(pilha);
    remover(pilha);
    remover(pilha);
    return 0;
}