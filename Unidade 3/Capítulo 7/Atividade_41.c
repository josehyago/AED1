/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 41 - Separação do programa em arquivos
 
 Contexto: A agenda de missões terá muitas operações e não deve ficar concentrada em um único arquivo. A interface pública, a implementação e o programa que usa a agenda precisam ter responsabilidades distintas.
 Descrição detalhada: Crie do zero a estrutura modular do projeto. Defina uma struct Missao, coloque declarações compartilhadas no cabeçalho e implemente ao menos funções simples de criação e exibição no arquivo .c. A main deverá utilizar somente o que foi exposto pela interface.
 Requisitos:
 - criar main.c, arquivo .h e arquivo .c do módulo;
 - proteger o cabeçalho com include guards;
 - declarar tipos e protótipos no local adequado;
 - não incluir arquivos .c dentro de outros arquivos;
 - evitar variáveis globais desnecessárias;
 - compilar e vincular todos os módulos em conjunto.
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

// gcc Atividade_41.c agenda.c -o Atividade_41 -Wall -Wextra
// ./Atividade_41.exe

int main(){
    int id, prioridade;
    char titulo[TAM_TITULO];

    printf("Digite o id: ");
    if (scanf("%d", &id) != 1) return 1;

    printf("Digite a prioridade: ");
    if (scanf("%d", &prioridade) != 1) return 1;

    getchar();

    printf("Digite o titulo: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    Missao m = criar_missao(id, titulo, prioridade);
    exibir_missao(&m);

    return 0;
}