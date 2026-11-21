/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 46 — Remoção do último nó e por critério

 Contexto: A agenda pode ter sua tarefa final cancelada ou precisar excluir uma missão específica, independentemente da posição que ela ocupa.
 Descrição detalhada: Acrescente uma função para remover o último nó e outra para remover a primeira missão com o identificador informado. As duas deverão tratar corretamente lista vazia, lista com um único elemento e remoção no início.
 Requisitos:
 - localizar o último nó e seu antecessor;
 - tornar a lista vazia ao remover seu único elemento;
 - religar os vizinhos na remoção por critério;
 - liberar exatamente o nó retirado;
 - informar se nenhum registro corresponde ao critério;
 - comprovar a integridade da lista após cada operação.
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

// gcc Atividade_46.c agenda.c -o Atividade_46 -Wall -Wextra
// ./Atividade_46.exe

int main(){
    Lista lista;
    inicializar_lista(&lista);

    // Teste de Lista Vazia
    printf("--- Lista vazia ---\n");
    exibir_lista(&lista);
    resultado_operacao(inserir_antes(&lista, 1, criar_missao(9, "X", 1)));
    resultado_operacao(inserir_apos(&lista, 1, criar_missao(9, "X", 1)));
    resultado_operacao(remover_inicio(&lista));
    resultado_operacao(remover_final(&lista));
    resultado_operacao(remover_missao(&lista, 1));

    printf("\n--- Inserindo missoes ---\n");
    // Lista base: 3, 1, 2, 4
    resultado_operacao(inserir_inicio(&lista, criar_missao(1, "Resgate", 5)));
    resultado_operacao(inserir_fim(&lista, criar_missao(2, "Escolta", 3)));
    resultado_operacao(inserir_inicio(&lista, criar_missao(3, "Patrulha", 4)));
    resultado_operacao(inserir_fim(&lista, criar_missao(4, "Reconhecimento", 2)));

    // Referências: primeiro nó e último nó
    resultado_operacao(inserir_apos(&lista, 3, criar_missao(5, "Ataque", 1)));
    resultado_operacao(inserir_apos(&lista, 4, criar_missao(6, "Defesa", 1)));
    resultado_operacao(inserir_antes(&lista, 3, criar_missao(7, "Infiltracao", 1)));
    resultado_operacao(inserir_antes(&lista, 6, criar_missao(8, "Exfiltracao", 1)));

    printf("\n--- Lista (7, 3, 5, 1, 2, 4, 8, 6) ---\n");
    exibir_lista(&lista);

    // Teste de referência inexistente em lista não vazia
    printf("\n--- Referencia inexistente em lista nao vazia ---\n");
    resultado_operacao(inserir_apos(&lista, 99, criar_missao(7, "Inexistente", 1)));
    resultado_operacao(inserir_antes(&lista, 99, criar_missao(7, "Inexistente", 1)));

    printf("Lista intacta apos tentativas de insercao em referencia inexistente:\n");
    exibir_lista(&lista);

    // Teste de ids repetidos
    Lista dup;
    inicializar_lista(&dup);

    inserir_fim(&dup, criar_missao(2, "Primeiro", 1));
    inserir_fim(&dup, criar_missao(2, "Segundo", 1));
    inserir_apos(&dup, 2, criar_missao(8, "Novo", 1));
    printf("\n--- Lista com ids repetidos (esperado: Primeiro, Novo, Segundo) ---\n");
    exibir_lista(&dup);

    printf("\n--- Remover missao em lista com ids repetidos ---\n");
    resultado_operacao(remover_missao(&dup, 2));
    printf("Sai so a 1a ocorrencia (esperado: Novo, Segundo):\n");
    exibir_lista(&dup);

    // Teste de Lista com apenas um nó
    printf("\n--- Inserir apos e antes em Lista com apenas um no ---\n");
    Lista unico;
    inicializar_lista(&unico);
    resultado_operacao(inserir_inicio(&unico, criar_missao(1, "Unico", 1)));
    exibir_lista(&unico);
    resultado_operacao(inserir_antes(&unico, 1, criar_missao(2, "NovoInicio", 1)));
    resultado_operacao(inserir_apos(&unico, 1, criar_missao(3, "NovoFim", 1)));
    printf("\n--- Lista apos insercoes antes e apos o unico no ---\n");
    exibir_lista(&unico);

    printf("\n--- Remocoes em listas com um no ---\n");
    Lista unico_inicio;
    inicializar_lista(&unico_inicio);
    inserir_fim(&unico_inicio, criar_missao(9, "UnicoInicio", 1));
    resultado_operacao(remover_inicio(&unico_inicio));
    printf("unico_inicio apos remover_inicio (esperado: Lista vazia!):\n");
    exibir_lista(&unico_inicio);

    Lista unico_final;
    inicializar_lista(&unico_final);
    inserir_fim(&unico_final, criar_missao(10, "UnicoFinal", 1));
    resultado_operacao(remover_final(&unico_final));
    printf("unico_final apos remover_final (esperado: Lista vazia!):\n");
    exibir_lista(&unico_final);

    Lista unico_missao;
    inicializar_lista(&unico_missao);
    inserir_fim(&unico_missao, criar_missao(11, "UnicoMissao", 1));
    resultado_operacao(remover_missao(&unico_missao, 11));
    printf("unico_missao apos remover_missao (esperado: Lista vazia!):\n");
    exibir_lista(&unico_missao);

    printf("\n--- Remover Inicio: removendo 2 nos (7 e 3) ---\n");
    for (int i = 0; i < 2; i++)
        resultado_operacao(remover_inicio(&lista));

    exibir_lista(&lista);
    // Lista agora: 5, 1, 2, 4, 8, 6

    printf("\n--- Remover Missao ---\n");

    printf("\nRemovendo do meio (id 2), esperado: 5, 1, 4, 8, 6\n");
    resultado_operacao(remover_missao(&lista, 2));
    exibir_lista(&lista);

    printf("\nId inexistente (99), lista deve ficar igual: 5, 1, 4, 8, 6\n");
    resultado_operacao(remover_missao(&lista, 99));
    exibir_lista(&lista);

    printf("\nRemovendo do inicio (id 5), esperado: 1, 4, 8, 6\n");
    resultado_operacao(remover_missao(&lista, 5));
    exibir_lista(&lista);

    printf("\nRemovendo do fim (id 6), esperado: 1, 4, 8\n");
    resultado_operacao(remover_missao(&lista, 6));
    exibir_lista(&lista);

    printf("\n--- Remover Final: removendo 2 nos (esperado: 1) ---\n");
    for (int i = 0; i < 2; i++)
        resultado_operacao(remover_final(&lista));

    exibir_lista(&lista);

    printf("\n--- Remover Final: removendo o ultimo no (esperado: Lista vazia!) ---\n");
    resultado_operacao(remover_final(&lista));
    exibir_lista(&lista);

    printf("\nremover_final em lista vazia (esperado -1): %d\n", remover_final(&lista));
    printf("remover_missao em lista vazia (esperado -1): %d\n", remover_missao(&lista, 1));
    printf("remover_inicio em lista vazia, retorno: %d (esperado -1)\n", remover_inicio(&lista));

    for (int i = 0; i < 1; i++)
        remover_final(&dup);

    for (int i = 0; i < 2; i++)
        remover_inicio(&unico);

    printf("\n--- Lista NULL ---\n");
    if (!inserir_inicio(NULL, criar_missao(9, "X", 1))) printf("inserir_inicio recusou NULL\n");
    if (!inserir_fim(NULL, criar_missao(10, "Y", 1))) printf("inserir_fim recusou NULL\n");
    printf("inserir_apos recusou NULL, retorno: %d (esperado 0)\n", inserir_apos(NULL, 1, criar_missao(9, "X", 1)));
    printf("inserir_antes recusou NULL, retorno: %d (esperado 0)\n", inserir_antes(NULL, 1, criar_missao(9, "X", 1)));
    printf("remover_inicio recusou NULL, retorno: %d (esperado 0)\n", remover_inicio(NULL));
    printf("remover_final recusou NULL, retorno: %d (esperado 0)\n", remover_final(NULL));
    printf("remover_missao recusou NULL, retorno: %d (esperado 0)\n", remover_missao(NULL, 1));
    exibir_lista(NULL);
    
    return 0;
}