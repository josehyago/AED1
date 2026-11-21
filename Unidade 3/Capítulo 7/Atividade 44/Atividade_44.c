/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 44 — Busca e inserção após um nó

 Contexto: Algumas missões dependem de uma tarefa anterior específica. O usuário precisa localizar a missão de referência e inserir a nova tarefa imediatamente depois dela.
 Descrição detalhada: Implemente uma busca por identificador e reutilize seu resultado na inserção posterior. Se a missão não existir, a lista deverá permanecer inalterada. A operação precisa funcionar também quando a referência for o último nó.
 Requisitos:
 - percorrer até encontrar o primeiro identificador correspondente;
 - retornar um resultado que diferencie sucesso e ausência;
 - alocar o novo nó somente em fluxo seguro;
 - ligar o novo nó ao antigo sucessor da referência;
 - atualizar a referência para apontar ao novo nó;
 - mostrar o resultado da operação ao usuário.
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

// gcc Atividade_44.c agenda.c -o Atividade_44 -Wall -Wextra
// ./Atividade_44.exe

int main(){
    Lista lista;
    inicializar_lista(&lista);

    // Teste de Lista Vazia
    printf("--- Lista vazia ---\n");
    exibir_lista(&lista);
    printf("Referencia inexistente, retorno: %d (esperado -1)\n", inserir_apos(&lista, 1, criar_missao(9, "X", 1)));

    printf("\n--- Inserindo missoes ---\n");
    // Lista base: 3, 1, 2, 4
    resultado_operacao(inserir_inicio(&lista, criar_missao(1, "Resgate", 5)));
    resultado_operacao(inserir_fim(&lista, criar_missao(2, "Escolta", 3)));
    resultado_operacao(inserir_inicio(&lista, criar_missao(3, "Patrulha", 4)));
    resultado_operacao(inserir_fim(&lista, criar_missao(4, "Reconhecimento", 2)));

    // Referências: primeiro nó e último nó
    resultado_operacao(inserir_apos(&lista, 3, criar_missao(5, "Ataque", 1)));
    resultado_operacao(inserir_apos(&lista, 4, criar_missao(6, "Defesa", 1)));

    printf("\n--- Lista (3, 5, 1, 2, 4, 6) ---\n");
    exibir_lista(&lista);

    // Teste de referência inexistente em lista não vazia
    printf("\n--- Referencia inexistente em lista nao vazia ---\n");
    resultado_operacao(inserir_apos(&lista, 99, criar_missao(7, "Inexistente", 1)));

    // Teste de ids repetidos
    printf("\n--- Lista com ids repetidos ---\n");
    Lista dup;
    inicializar_lista(&dup);

    inserir_fim(&dup, criar_missao(2, "Primeiro", 1));
    inserir_fim(&dup, criar_missao(2, "Segundo", 1));
    inserir_apos(&dup, 2, criar_missao(8, "Novo", 1));
    printf("\n--- Lista com ids repetidos (esperado: Primeiro, Novo, Segundo) ---\n");
    exibir_lista(&dup);

    // Teste de Lista NULL
    printf("\n--- Lista NULL ---\n");
    if (!inserir_inicio(NULL, criar_missao(9, "X", 1))) printf("inserir_inicio recusou NULL\n");
    if (!inserir_fim(NULL, criar_missao(10, "Y", 1))) printf("inserir_fim recusou NULL\n");
    printf("inserir_apos recusou NULL, retorno: %d (esperado 0)\n\n", inserir_apos(NULL, 1, criar_missao(9, "X", 1)));
    exibir_lista(NULL);

    return 0;
}