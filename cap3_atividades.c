// Capítulo 3 — Catalágo dinâmico de personagens
// Atividade 17 - Tipos próprios e passagens por valor

// Contexto: As funções do catálogo precisam de assinaturas mais legíveis. Algumas delas servem apenas para consultar dados e podem trabalhar sobre uma cópia sem alterar o registro armazenado.
// Descrição detalhada: Crie o tipo Personagem com typedef e implemente funções de consulta que recebam a estrutura por valor. Faça uma alteração intencional na cópia local e mostre que o personagem existente na main continua igual.
// Requisitos:
// - substituir usos externos de struct pelo nome definido no typedef;
// - criar ao menos duas funções que recebam Personagem por valor;
// - calcular ou exibir dados sem modificar o original;
// - alterar a cópia dentro de uma função de demonstração;
// - comparar os estados interno e externo;
// - comentar o efeito e o custo da cópia.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char nome[50];
    int vida;
    int pontuacao;
    float posicao_x;
    float posicao_y;
} Personagem;

Personagem construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y){
    Personagem novo_personagem;
    
    novo_personagem.id = id;

    strncpy(novo_personagem.nome, nome, sizeof(novo_personagem.nome) - 1);
    novo_personagem.nome[sizeof(novo_personagem.nome) - 1] = '\0';

    novo_personagem.vida = vida;
    novo_personagem.pontuacao = pontuacao;
    novo_personagem.posicao_x = posicao_x;
    novo_personagem.posicao_y = posicao_y;

    return novo_personagem;
}

void exibir_personagem(Personagem personagem);
void simular_dano(Personagem personagem);

int main(){
    int capacidade, capacidade_nova, i;
    capacidade = 5;
    char nome_novo[50];

    Personagem exemplo = {0, "Inicializacao posicional ou designada", 100, 0, 0.0, 0.0};
    (void)exemplo;

    Personagem *personagem = (Personagem *) calloc(capacidade, sizeof(Personagem));

    if(personagem == NULL){
        printf("Nao ha memoria suficiente");
        exit (1);
    }

    personagem[0] = construir_personagem(1, "Hyago", 80, 0, 10.5, 5.0);

    printf("\nEstado Inicial (Externo): \n");
    exibir_personagem(personagem[0]);

    printf("Aplicando item de cura (+50 de vida)\n");
    personagem[0].vida += 50; 
    
    printf("Aplicando pontuacao (+300 pontos)\n");
    personagem[0].pontuacao += 300;

    printf("Personagem andou para frente (+2 no eixo x)\n");
    personagem[0].posicao_x += 2.0;

    if (personagem[0].vida > 100){
        personagem[0].vida = 100;
    }
    if (personagem[0].pontuacao < 0){
        personagem[0].pontuacao = 0;
    }

    printf("Estado apos eventos: \n");
    exibir_personagem(personagem[0]);

    simular_dano(personagem[0]);
    printf("\nEstado Externo apos a funcao:\n");
    exibir_personagem(personagem[0]);

    // Efeito e Custo da Cópia (Passagem por Valor): O efeito positivo é a segurança: a função trabalha com um clone dos dados, garantindo que o registro original no main não seja alterado acidentalmente. 
    // O custo é a performance e memória: a cada chamada da função, o programa precisa alocar espaço e copiar todos os bytes da estrutura (int, char[50], floats). Em estruturas muito grandes ou em chamadas frequentes, isso consome muito processamento, sendo preferível usar ponteiros.

    printf("Digite a nova capacidade: ");
    scanf("%d", &capacidade_nova);
    getchar();

    if(capacidade_nova <= 0){
        printf("Capacidade invalida.");
        free(personagem);
        exit(1);
    }

        Personagem *personagem_temporario = (Personagem *) realloc(personagem, capacidade_nova * sizeof(Personagem));

        if (personagem_temporario == NULL){
        printf("Nao ha memoria suficiente para realocar.\n");
        free(personagem);
        exit(1);
    }
        personagem = personagem_temporario;

        if (capacidade_nova > capacidade) {
        for (i = capacidade; i < capacidade_nova; i++) {
            personagem[i] = construir_personagem(0, "", 0, 0, 0.0, 0.0);
        }
    }

        printf("Capacidade Anterior = %d | Capacidade Nova = %d\n", capacidade, capacidade_nova);

        printf("\nDigite o novo nome para o personagem 1: ");
        fgets(nome_novo, sizeof(nome_novo), stdin);
        nome_novo[strcspn(nome_novo, "\n")] = '\0';

        strncpy(personagem[0].nome, nome_novo, sizeof(personagem[0].nome) - 1);
        personagem[0].nome[sizeof(personagem[0].nome) - 1] = '\0';

        printf("\nRegistro Apos Alteracao: \n");
        printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", personagem[0].id, personagem[0].nome, personagem[0].vida, personagem[0].pontuacao, personagem[0].posicao_x, personagem[0].posicao_y);

    free(personagem);
    personagem = NULL;

    return 0;
}

void exibir_personagem(Personagem personagem){
    printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", 
           personagem.id, personagem.nome, personagem.vida, personagem.pontuacao, personagem.posicao_x, personagem.posicao_y);
}

void simular_dano(Personagem personagem){
    printf("\nDentro da funcao simular_dano:\n");
    printf("O personagem sofreu um ataque.\n");
    
    personagem.vida -= 30; 
    
    printf("Estado Interno (Copia): ");
    exibir_personagem(personagem);
}