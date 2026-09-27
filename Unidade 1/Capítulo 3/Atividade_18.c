/*
 Capítulo 3 — Catalágo dinâmico de personagens
 Atividade 18 - Alteração por ponteiro e operador seta

 Contexto: Operações como receber dano, avançar no mapa e ganhar pontos devem afetar o personagem realmente armazenado, não uma cópia descartada ao término da função.
 Descrição detalhada: Implemente versões modificadoras que recebam Personagem *. Use o operador seta para atualizar os campos e compare essa sintaxe com (*ponteiro).membro. As funções deverão rejeitar ponteiro nulo e valores incompatíveis com as regras do catálogo.
 Requisitos:
 - criar funções para vida, posição e pontuação;
 - acessar membros principalmente com ->;
 - impedir vida negativa ou superior ao máximo definido;
 - validar ponteiro nulo;
 - demonstrar ao menos uma expressão equivalente com (*p).membro;
 - confirmar as alterações após o retorno das funções.
*/

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

Personagem construir_personagem(int id, char *nome, int vida, int pontuacao, float posicao_x, float posicao_y);
void exibir_personagem(Personagem personagem);

void simular_dano(Personagem personagem);

void vida(Personagem *personagem, int quantidade);
void pontuacao(Personagem *personagem, int quantidade);
void posicao(Personagem *personagem, float posx, float posy);

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

    vida(&personagem[0], 50);
    pontuacao(&personagem[0], 300);
    posicao(&personagem[0], 2.0, 0.0);

    printf("Estado apos eventos: \n");
    exibir_personagem(personagem[0]);

    simular_dano(personagem[0]);
    printf("\nEstado Externo apos a funcao:\n");
    exibir_personagem(personagem[0]);

    // Efeito e Custo da Cópia (Passagem por Valor): O efeito positivo é a segurança: a função trabalha com um clone dos dados, garantindo que o registro original no main não seja alterado acidentalmente. 
    // O custo é a performance e memória: a cada chamada da função, o programa precisa alocar espaço e copiar todos os bytes da estrutura (int, char[50], floats). Em estruturas muito grandes ou em chamadas frequentes, isso consome muito processamento, sendo preferível usar ponteiros.

    printf("\nDigite a nova capacidade: ");
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

void exibir_personagem(Personagem personagem){
    printf("ID: %d | Nome: %s | Vida: %d | Pontos: %d | Posicao: (%.2f, %.2f)\n", 
           personagem.id, personagem.nome, personagem.vida, personagem.pontuacao, personagem.posicao_x, personagem.posicao_y);
}

void simular_dano(Personagem personagem){
    printf("\nDentro da funcao simular_dano:\n");
    printf("O personagem sofreu um ataque.\n");
    
    personagem.vida -= 30; 
    
    printf("Estado Interno (Copia): \n");
    exibir_personagem(personagem);
}

void vida(Personagem *personagem, int quantidade){
    if(personagem == NULL) return;
    
    personagem->vida += quantidade;

    if(quantidade < 0) printf("Seu personagem sofreu %d de dano\n", quantidade);
    if(quantidade > 0) printf("Seu personagem ganhou %d de vida\n", quantidade);

    if (personagem->vida > 100) personagem->vida = 100;
    else if (personagem->vida < 0) personagem->vida = 0;
}

void pontuacao(Personagem *personagem, int quantidade){
    if(personagem == NULL) return;
    
    personagem->pontuacao += quantidade;

    if(quantidade > 0) printf("Seu personagem ganhou %d de pontuacao\n", quantidade);
    if(quantidade < 0) printf("Seu personagem perdeu %d de pontuacao\n", quantidade);

    if (personagem->pontuacao < 0) personagem->pontuacao = 0;
}

void posicao(Personagem *personagem, float posx, float posy){
    if(personagem == NULL) return;

    if(posx != 0 || posy != 0){
    (*personagem).posicao_x += posx; //Equivalência com (->)
    personagem->posicao_y += posy;
    }

    if(posx > 0) printf("Seu personagem andou pra frente (+%2.0f no eixo x)\n", posx);
    if(posx < 0) printf("Seu personagem andou pra tras (-%2.0f no eixo x)\n", posx);
    if(posy > 0) printf("Seu personagem pulou pra cima (+%2.0f no eixo y)\n", posy);
    if(posy < 0) printf("Seu personagem pulou pra baixo (-%2.0f no eixo y)\n", posy);
}