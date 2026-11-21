#ifndef AGENDA_H
#define AGENDA_H

#define TAM_TITULO 100

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

// Auxiliar de mensagem: traduz 1 / 0 / -1 em texto (vale para insercoes e remocao)
void resultado_operacao(int r);

void exibir_lista(const Lista *l);

int remover_inicio(Lista *l);

Missao criar_missao(int id, const char *titulo, int prioridade);
void exibir_missao(const Missao *m);

#endif