/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 47 — Remoção depois e antes de uma referência

 Contexto: Ao cancelar uma etapa de uma sequência, o coordenador pode querer retirar a missão imediatamente anterior ou posterior a uma referência conhecida.
 Descrição detalhada: Implemente as duas remoções posicionais. Para remover antes, acompanhe pelo menos a referência, seu anterior e, quando necessário, o nó anterior ao anterior. Analise cuidadosamente situações em que não existe nó para remover.
 Requisitos:
 - tratar referência ausente;
 - impedir remoção depois do último nó;
 - impedir remoção antes do primeiro nó;
 - atualizar o início quando o removido for o primeiro;
 - preservar o restante do encadeamento;
 - liberar a memória e informar os dados removidos.
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

// gcc Atividade_47.c agenda.c -o Atividade_47 -Wall -Wextra
// ./Atividade_47.exe

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
    resultado_operacao(remover_antes(&lista, 1));
    resultado_operacao(remover_apos(&lista, 1));
    resultado_operacao(remover_antes(&lista, 1));
    resultado_operacao(remover_apos(&lista, 1));

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

    // Teste das remocoes posicionais
    Lista posicional;
    inicializar_lista(&posicional);
    inserir_fim(&posicional, criar_missao(7, "Infiltracao", 1));
    inserir_fim(&posicional, criar_missao(3, "Patrulha", 4));
    inserir_fim(&posicional, criar_missao(5, "Ataque", 1));
    inserir_fim(&posicional, criar_missao(1, "Resgate", 5));
    inserir_fim(&posicional, criar_missao(2, "Escolta", 3));
    inserir_fim(&posicional, criar_missao(4, "Reconhecimento", 2));
    inserir_fim(&posicional, criar_missao(8, "Exfiltracao", 1));
    inserir_fim(&posicional, criar_missao(6, "Defesa", 1));

    printf("\n--- Remocoes posicionais (lista 7, 3, 5, 1, 2, 4, 8, 6) ---\n");

    printf("\nReferencia inexistente:\n");
    resultado_operacao(remover_apos(&posicional, 99));
    resultado_operacao(remover_antes(&posicional, 99));

    printf("\nRemover apos o ultimo no (id 6):\n");
    resultado_operacao(remover_apos(&posicional, 6));
    exibir_lista(&posicional);

    printf("\nRemover antes do primeiro no (id 7):\n");
    resultado_operacao(remover_antes(&posicional, 7));
    exibir_lista(&posicional);

    printf("\nRemover apos (id 5 apos referencia 3):\n");
    resultado_operacao(remover_apos(&posicional, 3));
    exibir_lista(&posicional);

    printf("\nRemover antes (id 1 antes da referencia 2):\n");
    resultado_operacao(remover_antes(&posicional, 2));
    exibir_lista(&posicional);

    printf("\nRemover antes do inicio (atualiza o inicio):\n");
    resultado_operacao(remover_antes(&posicional, 3));
    exibir_lista(&posicional);

    printf("\nRemover apos no meio (id 4 apos referencia 2):\n");
    resultado_operacao(remover_apos(&posicional, 2));
    exibir_lista(&posicional);

    printf("\n--- Remocoes posicionais em lista com um no ---\n");
    Lista unico_posicional;
    inicializar_lista(&unico_posicional);
    inserir_fim(&unico_posicional, criar_missao(20, "NoUnico", 1));
    resultado_operacao(remover_apos(&unico_posicional, 20));
    resultado_operacao(remover_antes(&unico_posicional, 20));
    exibir_lista(&unico_posicional);

    Lista vazia_posicional;
    inicializar_lista(&vazia_posicional);
    printf("\n--- Remocoes posicionais em lista vazia ---\n");
    resultado_operacao(remover_apos(&vazia_posicional, 1));
    resultado_operacao(remover_antes(&vazia_posicional, 1));

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
    printf("remover_apos recusou NULL, retorno: %d (esperado 0)\n", remover_apos(NULL, 1));
    printf("remover_antes recusou NULL, retorno: %d (esperado 0)\n", remover_antes(NULL, 1));
    exibir_lista(NULL);
    
    return 0;
}