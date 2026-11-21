/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 42 — Tipo abstrato de dados e inserção no início

 Contexto: A agenda precisa controlar sua própria representação interna. O programa principal deverá solicitar operações sem depender de como os nós estão encadeados.
 Descrição detalhada: Defina os tipos necessários para a lista e implemente a inicialização e a inserção no início. Sempre que uma missão for adicionada, um novo nó deverá ser alocado, preenchido e conectado antes do antigo primeiro nó. Preserve o máximo possível de encapsulamento no módulo.
 Requisitos:
 - representar um nó com dado e ponteiro para o próximo;
 - inicializar a lista vazia;
 - alocar e validar o novo nó;
 - copiar os dados da missão para o nó;
 - atualizar corretamente o início;
 - expor uma função pública simples para a operação.
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

// gcc Atividade_42.c agenda.c -o Atividade_42 -Wall -Wextra
// ./Atividade_42.exe

int main(){
    Lista lista;
    inicializar_lista(&lista);

    if (!inserir_inicio(&lista, criar_missao(1, "Resgate", 5))) printf("Falha ao inserir A\n");
    if (!inserir_inicio(&lista, criar_missao(2, "Escolta", 3))) printf("Falha ao inserir B\n");
    if (!inserir_inicio(&lista, criar_missao(3, "Patrulha", 4))) printf("Falha ao inserir C\n");

    // caso de erro: lista NULL deve devolver 0
    if (!inserir_inicio(NULL, criar_missao(9, "X", 1))) printf("Lista NULL recusada\n");

    return 0;
}