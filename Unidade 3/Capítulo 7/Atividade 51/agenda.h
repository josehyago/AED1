#ifndef AGENDA_H
#define AGENDA_H

#define TAM_TITULO 100
#define MAX_LOTE 100
#define MAX_REGISTROS 1000

/*
    - Missao e Lista são públicas: A main precisa criar missões e declarar a lista.
    - No fica oculto: Aqui ele é só um tipo incompleto. A main vê o campo "inicio", mas não consegue seguir os nós ou mexer em "prox". A struct no só é definida no agenda.c. 
*/

typedef struct{
    int id;
    char titulo[TAM_TITULO];
    int prioridade;
} Missao;

typedef struct no No;

typedef struct{
    No *inicio;
} Lista;


void inicializar_lista(Lista *l);

// Retornos de inserir_inicio e inserir_fim: 1 = inseriu | 0 = erro (lista NULL ou malloc)
int inserir_inicio(Lista *l, Missao m);
int inserir_fim(Lista *l, Missao m);

// Retornos de inserir_apos e inserir_antes: 1 = inseriu | 0 = erro (lista NULL ou malloc) | -1 = referencia nao encontrada (lista intacta)
int inserir_apos(Lista *l, int id, Missao m);
int inserir_antes(Lista *l, int id, Missao m);

// Auxiliar de mensagem: traduz os codigos de retorno em texto (vale para insercoes e remocoes)
void resultado_operacao(int r);

void exibir_lista(const Lista *l);

int remover_inicio(Lista *l);
int remover_final(Lista *l);
int remover_missao(Lista *l, int id);
// remover_apos e remover_antes: 1 = removeu | 0 = lista NULL | -1 = referencia nao encontrada/lista vazia | -2 = nao ha no apos/antes da referencia
int remover_apos(Lista *l, int id);
int remover_antes(Lista *l, int id);

// limpar_lista: 1 = limpou | 0 = lista NULL | -1 = lista ja vazia
int limpar_lista(Lista *l);
// alterar_missao: 1 = alterou | 0 = lista NULL | -1 = identificador nao encontrado | -2 = dados invalidos
int alterar_missao(Lista *l, int id, Missao nova);

int tamanho_lista(const Lista *l);
// inserir_lote preserva a ordem do vetor e adiciona o lote ao final da lista.
int inserir_lote(Lista *l, const Missao *lote, int qtd);

// Ordena por prioridade crescente (1 primeiro) e, em caso de empate, por ID decrescente.
int ordenar_lista(Lista *l);
int salvar_lista(const Lista *l, const char *caminho);

// Carrega somente quando a lista estiver vazia. Retornos: 1 sucesso, 0 erro,
// -1 arquivo inexistente, -2 lista nao vazia.
int carregar_lista(Lista *l, const char *caminho);

Missao criar_missao(int id, const char *titulo, int prioridade);
void exibir_missao(const Missao *m);

#endif
