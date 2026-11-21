#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agenda.h"

struct no{
    Missao dado;
    struct no *prox;
};

void inicializar_lista(Lista *l){
    if (l == NULL) return;
    l->inicio = NULL;
}

int inserir_inicio(Lista *l, Missao m){
    if (l == NULL) return 0;

    No *novo = (No *) malloc(sizeof(*novo));
    if (novo == NULL) return 0;

    novo->dado = m;
    novo->prox = l->inicio;
    l->inicio = novo;

    return 1;
}

int inserir_fim(Lista *l, Missao m){
    if (l == NULL) return 0;

    No *novo = (No *) malloc(sizeof(*novo));
    if (novo == NULL) return 0;

    novo->dado = m;
    novo->prox = NULL;

    if (l->inicio == NULL){
        l->inicio = novo;
        return 1;
    }

    No *ultimo = l->inicio;
    while (ultimo->prox != NULL){
        ultimo = ultimo->prox;
    }
    ultimo->prox = novo;
    return 1;
}

static No *buscar_missao(const Lista *l, int id){
    if (l == NULL) return NULL;
    
    No *pi = l->inicio;
    while (pi != NULL && pi->dado.id != id){
        pi = pi->prox;
    }
    return pi;
}

int inserir_apos(Lista *l, int id, Missao m){
    if (l == NULL) return 0;

    No *referencia = buscar_missao(l, id);
    if (referencia == NULL) return -1;

    No *novo = (No *) malloc(sizeof(*novo));
    if (novo == NULL) return 0;

    novo->dado = m;
    novo->prox = referencia->prox;
    referencia->prox = novo;
    return 1;
}

int inserir_antes(Lista *l, int id, Missao m){
    if (l == NULL) return 0;

    No *anterior = NULL;
    No *atual = l->inicio;

    while (atual != NULL && atual->dado.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return -1;

    No *novo = (No *) malloc(sizeof(*novo));
    if (novo == NULL) return 0;

    novo->dado = m;
    novo->prox = atual;

    if (anterior == NULL) l->inicio = novo;
    else anterior->prox = novo;
    return 1;
}

void resultado_operacao(int r){
    switch (r){
        case 1:  printf("Operacao realizada com sucesso!\n"); break;
        case 0: printf("Erro na operacao!\n"); break;
        case -1:  printf("Missao de referencia nao encontrada ou lista vazia\n"); break;
        case -2: printf("Referencia sem missao adjacente ou dados da missao invalidos\n"); break;
        default: printf("Codigo de retorno desconhecido: %d\n", r); break;
    }
}

void exibir_lista(const Lista *l){
    if (l == NULL) return;
    if (l->inicio == NULL){ 
        printf("Lista vazia!\n"); 
        return;
    }

    for (No *pi = l->inicio; pi != NULL; pi = pi->prox){
        exibir_missao(&pi->dado);
    }
}

int remover_inicio(Lista *l){
    if (l == NULL) return 0;
    if (l->inicio == NULL) return -1;

    No *alvo = l->inicio;
    printf("\nRemovendo missao:\n");
    exibir_missao(&alvo->dado);
    l->inicio = alvo->prox;
    free(alvo);
    return 1;
}

int remover_final(Lista *l){
    if (l == NULL) return 0;
    if (l->inicio == NULL) return -1;

    No *anterior = NULL;
    No *atual = l->inicio;

    while (atual->prox != NULL){
        anterior = atual;
        atual = atual->prox;
    }

    printf("\nRemovendo missao:\n");
    exibir_missao(&atual->dado);

    if (anterior == NULL) l->inicio = NULL;
    else anterior->prox = NULL;

    free(atual);
    return 1;
}

int remover_missao(Lista *l, int id){
    if (l == NULL) return 0;
    if (l->inicio == NULL) return -1;

    No *anterior = NULL;
    No *atual = l->inicio;

    while (atual != NULL && atual->dado.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return -1;

    printf("\nRemovendo missao:\n");
    exibir_missao(&atual->dado);

    if (anterior == NULL) l->inicio = atual->prox;
    else anterior->prox = atual->prox;

    free(atual);
    return 1;
}

int remover_apos(Lista *l, int id){
    if (l == NULL) return 0;

    No *referencia = l->inicio;
    while (referencia != NULL && referencia->dado.id != id) referencia = referencia->prox;
    if (referencia == NULL) return -1;

    No *alvo = referencia->prox;
    if (alvo == NULL) return -2;

    printf("\nRemovendo missao:\n");
    exibir_missao(&alvo->dado);
    referencia->prox = alvo->prox;
    free(alvo);
    return 1;
}

int remover_antes(Lista *l, int id){
    if (l == NULL) return 0;

    No *ant_anterior = NULL;
    No *anterior = NULL;
    No *atual = l->inicio;

    while (atual != NULL && atual->dado.id != id){
        ant_anterior = anterior;
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return -1;
    if (anterior == NULL) return -2;

    printf("\nRemovendo missao:\n");
    exibir_missao(&anterior->dado);
    if (ant_anterior == NULL) l->inicio = atual;
    else ant_anterior->prox = atual;
    free(anterior);
    return 1;
}

// Regras da agenda: titulo nao vazio (e terminado em '\0') e prioridade >= 0.
static int missao_valida(const Missao *m){
    if (m == NULL) return 0;
    if (memchr(m->titulo, '\0', TAM_TITULO) == NULL) return 0;
    if (m->titulo[0] == '\0') return 0;
    if (m->prioridade < 0) return 0;
    return 1;
}

int limpar_lista(Lista *l){
    if (l == NULL) return 0;
    if (l->inicio == NULL) return -1;

    No *atual = l->inicio;
    while (atual != NULL){
        No *proximo = atual->prox;
        printf("\nLiberando missao:\n");
        exibir_missao(&atual->dado);
        free(atual);
        atual = proximo;
    }
    l->inicio = NULL;
    return 1;
}

int alterar_missao(Lista *l, int id, Missao nova){
    if (l == NULL) return 0;
    if (!missao_valida(&nova)) return -2;

    No *alvo = buscar_missao(l, id);
    if (alvo == NULL) return -1;

    strncpy(alvo->dado.titulo, nova.titulo, TAM_TITULO - 1);
    alvo->dado.titulo[TAM_TITULO - 1] = '\0';
    alvo->dado.prioridade = nova.prioridade;
    return 1;
}

int tamanho_lista(const Lista *l){
    if (l == NULL) return -1;

    int n = 0;
    for (const No *pi = l->inicio; pi != NULL; pi = pi->prox){
        n++;
    }
    return n;
}

int inserir_lote(Lista *l, const Missao *lote, int qtd){
    if (l == NULL || lote == NULL) return 0;
    if (qtd <= 0 || qtd > MAX_LOTE) return -2;

    for (int i = 0; i < qtd; i++){
        if (!missao_valida(&lote[i])) return -2;
    }

    No *ultimo_original = l->inicio;
    if (ultimo_original != NULL){
        while (ultimo_original->prox != NULL){
            ultimo_original = ultimo_original->prox;
        }
    }

    No *ultimo = ultimo_original;
    for (int i = 0; i < qtd; i++){
        No *novo = (No *) malloc(sizeof(*novo));
        if (novo == NULL){
            No *sobra = (ultimo_original == NULL) ? l->inicio : ultimo_original->prox;
            if (ultimo_original == NULL) l->inicio = NULL;
            else ultimo_original->prox = NULL;
            while (sobra != NULL){
                No *proximo = sobra->prox;
                free(sobra);
                sobra = proximo;
            }
            return 0;
        }

        novo->dado = lote[i];
        novo->prox = NULL;
        if (ultimo == NULL) l->inicio = novo;
        else ultimo->prox = novo;
        ultimo = novo;
    }
    return 1;
}

static int vem_depois(const Missao *a, const Missao *b){
    if (a->prioridade != b->prioridade) return a->prioridade > b->prioridade;
    return a->id < b->id;
}

int ordenar_lista(Lista *l){
    if (l == NULL) return 0;
    if (l->inicio == NULL) return -1;

    // Ordenacao por troca de dados: prioridade 1 primeiro, empate pelo maior ID.
    // Os ponteiros dos nos continuam inalterados.
    No *fim = NULL;
    int trocou;

    do {
        trocou = 0;
        No *pi = l->inicio;
        while (pi->prox != fim){
            if (vem_depois(&pi->dado, &pi->prox->dado)){
                Missao temp = pi->dado;
                pi->dado = pi->prox->dado;
                pi->prox->dado = temp;
                trocou = 1;
            }
            pi = pi->prox;
        }
        fim = pi;
    } while (trocou && fim != l->inicio);
    return 1;
}

int salvar_lista(const Lista *l, const char *caminho){
    if (l == NULL || caminho == NULL || caminho[0] == '\0') return 0;

    int qtd = tamanho_lista(l);
    if (qtd < 0) return 0;
    if (qtd > MAX_REGISTROS) return -2;

    FILE *arq = fopen(caminho, "wb");
    if (arq == NULL) return -1;

    if (fwrite(&qtd, sizeof(qtd), 1, arq) != 1){
        fclose(arq);
        return 0;
    }

    for (const No *pi = l->inicio; pi != NULL; pi = pi->prox){
        if (fwrite(&pi->dado, sizeof(pi->dado), 1, arq) != 1){
            fclose(arq);
            return 0;
        }
    }

    if (fclose(arq) != 0) return 0;
    return 1;
}

Missao criar_missao(int id, const char *titulo, int prioridade){
    Missao m;

    m.id = id;
    m.prioridade = prioridade;

    if (titulo == NULL) m.titulo[0] = '\0';
        else { 
            strncpy(m.titulo, titulo, TAM_TITULO - 1);
            m.titulo[TAM_TITULO - 1] = '\0';
    }
    return m;
}

void exibir_missao(const Missao *m){
    if (m == NULL) return;
    printf("ID: %d | Titulo: %s | Prioridade: %d\n", m->id, m->titulo, m->prioridade);
}