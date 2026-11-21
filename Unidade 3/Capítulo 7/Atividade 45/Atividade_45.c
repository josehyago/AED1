/*
 Capítulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 45 — Inserção antes e remoção do primeiro nó

 Contexto: Uma missão urgente pode precisar entrar antes de outra já agendada. Além disso, a primeira missão pode ser concluída e removida da agenda.
 Descrição detalhada: Implemente inserção antes de um identificador, lembrando que inserir antes do primeiro nó altera o início. Depois, crie a remoção do primeiro nó, devolvendo ou mostrando os dados removidos antes de liberar sua memória.
 Requisitos:
 - tratar a inserção antes do início;
 - manter ponteiro anterior e atual durante a busca;
 - não modificar a lista se a referência não existir;
 - impedir remoção em lista vazia;
 - atualizar o início antes de chamar free;
 - testar listas com um e vários nós.
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

// gcc Atividade_45.c agenda.c -o Atividade_45 -Wall -Wextra
// ./Atividade_45.exe

int main(){
    Lista lista;
    inicializar_lista(&lista);

    // Teste de Lista Vazia
    printf("--- Lista vazia ---\n");
    exibir_lista(&lista);
    resultado_operacao(inserir_antes(&lista, 1, criar_missao(9, "X", 1)));
    resultado_operacao(inserir_apos(&lista, 1, criar_missao(9, "X", 1)));
    resultado_operacao(remover_inicio(&lista));

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

    // Teste de Lista com apenas um nó
    printf("\n--- Lista com apenas um no ---\n");
    Lista unico;
    inicializar_lista(&unico);
    resultado_operacao(inserir_inicio(&unico, criar_missao(1, "Unico", 1)));
    exibir_lista(&unico);
    resultado_operacao(inserir_antes(&unico, 1, criar_missao(2, "NovoInicio", 1)));
    resultado_operacao(inserir_apos(&unico, 1, criar_missao(3, "NovoFim", 1)));
    printf("\n--- Lista apos insercoes antes e apos o unico no ---\n");
    exibir_lista(&unico);

    // Teste de Lista NULL
    printf("\n--- Lista NULL ---\n");
    if (!inserir_inicio(NULL, criar_missao(9, "X", 1))) printf("inserir_inicio recusou NULL\n");
    if (!inserir_fim(NULL, criar_missao(10, "Y", 1))) printf("inserir_fim recusou NULL\n");
    printf("inserir_apos recusou NULL, retorno: %d (esperado 0)\n", inserir_apos(NULL, 1, criar_missao(9, "X", 1)));
    printf("inserir_antes recusou NULL, retorno: %d (esperado 0)\n\n", inserir_antes(NULL, 1, criar_missao(9, "X", 1)));
    exibir_lista(NULL);

    // Teste de remoção com vários nós, até sobrar um
    for (int i = 0; i < 7; i++){
        resultado_operacao(remover_inicio(&lista));
    }
    printf("\n--- Lista apos remocoes ate sobrar um no ---\n");
    exibir_lista(&lista);

    // Removendo o último nó e testando a lista vazia
    resultado_operacao(remover_inicio(&lista));
    printf("\n--- Lista vazia ---\n");
    exibir_lista(&lista);
    resultado_operacao(remover_inicio(&lista));
    printf("remover_inicio recusou NULL, retorno: %d (esperado -1)\n", remover_inicio(&lista));

    printf("\n--- Removendo todos os nos de listas com ids repetidos e unico ---\n");
    for (int i = 0; i < 3; i++)
        resultado_operacao(remover_inicio(&dup));

    for (int i = 0; i < 3; i++)
        resultado_operacao(remover_inicio(&unico));
    
    return 0;
}