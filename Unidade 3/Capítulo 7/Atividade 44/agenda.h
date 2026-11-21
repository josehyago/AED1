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

// Retornos: 1 = inseriu | 0 = erro (lista NULL ou malloc) | -1 = referencia nao encontrada

int inserir_inicio(Lista *l, Missao m);
int inserir_fim(Lista *l, Missao m);
int inserir_apos(Lista *l, int id, Missao m);
void resultado_operacao(int r);

void exibir_lista(const Lista *l);

Missao criar_missao(int id, const char *titulo, int prioridade);
void exibir_missao(const Missao *m);

#endif