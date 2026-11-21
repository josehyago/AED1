/*
 Capitulo 7 - Biblioteca Modular de Lista Encadeada
 Atividade 51 - Leitura do arquivo e modulo completo

 Contexto: Ao iniciar uma nova sessão, a agenda precisa reconstruir as missões salvas na mesma ordem. O módulo final deve esconder sua implementação e oferecer uma interface clara ao programa principal.
 Descrição detalhada: Implemente o carregamento e insira cada registro de modo a preservar a ordem gravada. Defina se a lista atual será limpa ou se o carregamento será recusado para evitar duplicações. Revise o cabeçalho, a implementação e o menu de testes.
 Requisitos:
 - continuar com lista vazia quando o arquivo não existir;
 - validar cada leitura antes de inserir;
 - preservar a ordem original;
 - impedir duplicação em carregamentos sucessivos;
 - documentar as funções públicas no .h;
 - manter detalhes dos nós dentro do módulo quando possível.

 gcc Atividade_51.c agenda.c -o Atividade_51 -Wall -Wextra
 ./Atividade_51.exe
*/

#include <stdio.h>
#include <string.h>
#include "agenda.h"

#define ARQUIVO "agenda.bin"

static int ler_inteiro(const char *mensagem, int *valor){
    printf("%s", mensagem);
    if (scanf("%d", valor) != 1){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    return 1;
}

static int ler_missao(Missao *missao){
    int id;
    int prioridade;
    char titulo[TAM_TITULO];

    if (!ler_inteiro("Id: ", &id)) return 0;
    if (!ler_inteiro("Prioridade: ", &prioridade)) return 0;
    getchar();

    printf("Titulo: ");
    if (fgets(titulo, sizeof(titulo), stdin) == NULL) return 0;

    if (strchr(titulo, '\n') == NULL){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    titulo[strcspn(titulo, "\n")] = '\0';

    if (titulo[0] == '\0' || prioridade < 0) return 0;

    *missao = criar_missao(id, titulo, prioridade);
    return 1;
}

int main(){
    Lista agenda;
    inicializar_lista(&agenda);

    Missao missao;
    int id;
    int opcao;

    do{
        printf("\n===== AGENDA DE MISSOES =====\n");
        printf(" 1. Inserir no inicio          10. Alterar missao\n");
        printf(" 2. Inserir no fim             11. Tamanho da lista\n");
        printf(" 3. Inserir apos um id         12. Importar lote\n");
        printf(" 4. Inserir antes de um id     13. Ordenar por prioridade\n");
        printf(" 5. Remover o primeiro         14. Salvar em arquivo (%s)\n", ARQUIVO);
        printf(" 6. Remover o ultimo           15. Carregar do arquivo\n");
        printf(" 7. Remover por id             16. Limpar a lista\n");
        printf(" 8. Remover apos um id         17. Exibir a lista\n");
        printf(" 9. Remover antes de um id\n");
        printf(" 0. Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1;
        }

        switch (opcao){
            case 1:
                if (ler_missao(&missao)) resultado_operacao(inserir_inicio(&agenda, missao));
                else printf("Entrada invalida.\n");
                break;

            case 2:
                if (ler_missao(&missao)) resultado_operacao(inserir_fim(&agenda, missao));
                else printf("Entrada invalida.\n");
                break;

            case 3:
                if (ler_inteiro("Id da referencia: ", &id) && ler_missao(&missao))
                    resultado_operacao(inserir_apos(&agenda, id, missao));
                else printf("Entrada invalida.\n");
                break;

            case 4:
                if (ler_inteiro("Id da referencia: ", &id) && ler_missao(&missao))
                    resultado_operacao(inserir_antes(&agenda, id, missao));
                else printf("Entrada invalida.\n");
                break;

            case 5:
                resultado_operacao(remover_inicio(&agenda));
                break;

            case 6:
                resultado_operacao(remover_final(&agenda));
                break;

            case 7:
                if (ler_inteiro("Id a remover: ", &id))
                    resultado_operacao(remover_missao(&agenda, id));
                else printf("Entrada invalida.\n");
                break;

            case 8:
                if (ler_inteiro("Id da referencia: ", &id))
                    resultado_operacao(remover_apos(&agenda, id));
                else printf("Entrada invalida.\n");
                break;

            case 9:
                if (ler_inteiro("Id da referencia: ", &id))
                    resultado_operacao(remover_antes(&agenda, id));
                else printf("Entrada invalida.\n");
                break;

            case 10:
                printf("Informe o id da missao e os novos dados (o id original sera preservado).\n");
                if (ler_inteiro("Id a alterar: ", &id) && ler_missao(&missao))
                    resultado_operacao(alterar_missao(&agenda, id, missao));
                else printf("Entrada invalida.\n");
                break;

            case 11:
                printf("Tamanho: %d\n", tamanho_lista(&agenda));
                break;

            case 12: {
                Missao lote[MAX_LOTE];
                int quantidade;

                if (!ler_inteiro("Quantidade do lote: ", &quantidade)){
                    printf("Entrada invalida.\n");
                    break;
                }
                if (quantidade <= 0 || quantidade > MAX_LOTE){
                    resultado_operacao(-2);
                    break;
                }

                int valido = 1;
                for (int i = 0; i < quantidade && valido; i++){
                    printf("Missao %d do lote\n", i + 1);
                    valido = ler_missao(&lote[i]);
                }
                if (!valido){
                    printf("Entrada invalida.\n");
                    break;
                }

                printf("Tamanho antes: %d\n", tamanho_lista(&agenda));
                resultado_operacao(inserir_lote(&agenda, lote, quantidade));
                printf("Tamanho depois: %d\n", tamanho_lista(&agenda));
                break;
            }

            case 13:
                resultado_operacao(ordenar_lista(&agenda));
                break;

            case 14:
                resultado_operacao(salvar_lista(&agenda, ARQUIVO));
                break;

            case 15:
                resultado_operacao(carregar_lista(&agenda, ARQUIVO));
                break;

            case 16:
                resultado_operacao(limpar_lista(&agenda));
                break;

            case 17:
                exibir_lista(&agenda);
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    limpar_lista(&agenda);
    return 0;
}
