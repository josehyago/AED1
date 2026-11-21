/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
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
#include <string.h>
#include "agenda.h"

// gcc Atividade_43.c agenda.c -o Atividade_43 -Wall -Wextra
// ./Atividade_43.exe

int main(){
    Lista lista;
    inicializar_lista(&lista);

    printf("--- Lista vazia ---\n");
    exibir_lista(&lista);

    if (!inserir_inicio(&lista, criar_missao(1, "Resgate", 5))) printf("Falha ao inserir A\n");
    if (!inserir_fim(&lista, criar_missao(2, "Escolta", 3))) printf("Falha ao inserir B\n");
    if (!inserir_inicio(&lista, criar_missao(3, "Patrulha", 4))) printf("Falha ao inserir C\n");
    if (!inserir_fim(&lista, criar_missao(4, "Reconhecimento", 2))) printf("Falha ao inserir D\n");

    printf("\n--- Lista (3, 1, 2, 4) ---\n");
    exibir_lista(&lista);

    Lista lista2;
    inicializar_lista(&lista2);
    if (!inserir_fim(&lista2, criar_missao(7, "Defesa", 1))) printf("Falha ao inserir X\n");

    printf("\n--- Lista 2 (7) ---\n");
    exibir_lista(&lista2);

    // caso de erro: lista NULL deve devolver 0
    if (!inserir_inicio(NULL, criar_missao(9, "X", 1))) printf("\ninserir_inicio recusou NULL\n");
    if (!inserir_fim(NULL, criar_missao(10, "Y", 1))) printf("inserir_fim recusou NULL\n");
    exibir_lista(NULL);

    return 0;
}