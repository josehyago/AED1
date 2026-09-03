//Capítulo 2 — Cadastro dinâmico de jogadores e equipes
//Atividade 9 - Mapa matricial da equipe
#include <stdio.h>
#include <string.h>

//Definindo os tamanhos fixos
#define TAMANHO_NOME 80
#define TAMANHO_APELIDO 30
#define TAMANHO_SENHA 16
#define TAMANHO_EQUIPE 50
#define TAMANHO_LINHAS 5
#define TAMANHO_COLUNAS 5

void inicializar_mapa(int linhas, int colunas, int mapa[linhas][colunas])
{
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            mapa[il][ic] = -1;
        }
    }
}

void posicionar_jogador(int linhas, int colunas, int mapa[linhas][colunas], char lista_jogadores[5][80]){
    
    int il, ic;

    for(int i = 0; i < 5; i++) {
        printf("Posicionando o Jogador %d: %s\n", i + 1, lista_jogadores[i]);
        printf("Digite as coordenadas (linha e coluna entre 0 e %d):\n", linhas - 1);
    
        while(1) {
            scanf("%d %d", &il, &ic);
            
            if(il >= linhas || il < 0 || ic >= colunas || ic < 0){
                printf("Erro: Coordenadas fora do limite do mapa. Tente novamente:\n");
            } 
            else if(mapa[il][ic] != -1) {
                printf("Erro: Ja esta ocupada por outro jogador. Tente outra:\n");
            } 
            else {
                mapa[il][ic] = i + 1; 
                break;
            }
        }
    }
}

void reposicionar_jogador(int linhas, int colunas, int mapa[linhas][colunas]){
    int jogador, nova_linha, nova_coluna;
    int encontrado = 0;

    printf("Reposicionar Jogador\n");
    printf("Digite o numero do jogador que deseja mover (1 a 5): ");
    scanf("%d", &jogador);

    for(int il = 0; il < linhas; il++) {
        for(int ic = 0; ic < colunas; ic++) {
            if(mapa[il][ic] == jogador) {
                mapa[il][ic] = -1;
                encontrado = 1;
            }
        }
    }

    if(encontrado == 0) {
        printf("Aviso: Esse jogador nao foi encontrado em nenhuma posicao do mapa.\n");
        return;
    }

    printf("Digite as novas coordenadas (linha e coluna) para o Jogador %d:\n", jogador);
    while(1) {
        scanf("%d %d", &nova_linha, &nova_coluna);

        if(nova_linha >= linhas || nova_linha < 0 || nova_coluna >= colunas || nova_coluna < 0) {
            printf("Erro: Coordenadas invalidas. Tente novamente:\n");
        } 
        else if(mapa[nova_linha][nova_coluna] != -1) {
            printf("Erro: Essa posicao ja esta ocupada. Escolha outra:\n");
        } 
        else {
            mapa[nova_linha][nova_coluna] = jogador;
            printf("Jogador reposicionado com sucesso.\n");
            break;
        }
    }
}

void exibir_mapa(int linhas, int colunas, int mapa[linhas][colunas])
{
    printf("Mapa atual\n");
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            
            if(mapa[il][ic] == -1){ 
                printf("[ ~ ]");
            }else{
                printf("[Jogador %d ]", mapa[il][ic]);}      
        }
        printf("\n");
    }
}

int main()
{
    char nome[TAMANHO_NOME], apelido[TAMANHO_APELIDO], senha[TAMANHO_SENHA], confirmacao[TAMANHO_SENHA], equipe[TAMANHO_EQUIPE];
    int erro, i, a, tamanho_necessario, encontrado;
    int linhas = TAMANHO_LINHAS;
    int colunas = TAMANHO_COLUNAS;
    char lista_jogadores[5][80], apelido_busca[TAMANHO_NOME];
    int mapa[TAMANHO_LINHAS][TAMANHO_COLUNAS];
    
    printf("Digite o nome da equipe: \n");
    fgets(equipe, sizeof(equipe), stdin);
    equipe[strcspn(equipe, "\n")] = '\0';

    for(a = 0; a < 5; a++){

        printf("Cadastro do Jogador %d\n", a + 1);

        printf("Digite o nome completo do jogador %d: \n", a + 1);
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; //Substitui o '\n' por '\0'

        do
        {
            erro = 0;
        
            printf("Digite o apelido do jogador %d: \n", a + 1);
            fgets(apelido, sizeof(apelido), stdin);
            apelido[strcspn(apelido, "\n")] = '\0';

            if(strlen(apelido) < 3) //strlen verifica o tamanho do apelido.
            {
                erro = 1;
                printf("O apelido deve ter pelo menos 3 caracteres\n");
            }else{

                for(i = 0; apelido[i] != '\0'; i++){
            
                    if(apelido[i] == ' ')  
                    {
                        erro = 1;
                        printf("O apelido nao pode conter espacos\n");
                        break;
        }
    }
}
        }while(erro == 1);

        do
        {
            erro = 0;

            printf("Digite a senha do jogador %d: \n", a + 1);
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = '\0';

            if(strlen(senha) < 1) {
                erro = 1;
                printf("A senha nao pode ficar em branco\n");
            }else{
                
                for(i = 0; senha[i] != '\0'; i++){

                    if(senha[i] == ' '){
            
                        erro = 1;
                        printf("A senha nao pode conter espacos\n");
                        break;
        }
    }
}
        }while(erro == 1);

        do
        {
            erro = 0;

            printf("Confirme a sua senha: \n");
            fgets(confirmacao, sizeof(confirmacao), stdin);
            confirmacao[strcspn(confirmacao, "\n")] = '\0';
        
            if(strcmp(senha, confirmacao) != 0){ //strcmp compara a senha e a confirmação
                erro = 1;
                printf("As duas senhas nao sao iguais\n");
            }
        }while(erro == 1);

        tamanho_necessario = strlen(apelido) + strlen(equipe) + 4;

        if (tamanho_necessario < sizeof(lista_jogadores[a])){
            strcpy(lista_jogadores[a], apelido);
            strcat(lista_jogadores[a], " - ");
            strcat(lista_jogadores[a], equipe);
        }else{
            printf("Erro: O tamanho do nome da equipe e do apelido excede o limite permitido\n");
    }
}
        printf("Cadastro concluido com sucesso!\n");
        
        printf("Lista de jogadores: \n");
        for(a = 0; a < 5; a++){
            printf("Jogador %d: %s\n", a + 1, lista_jogadores[a]);
        }
        
        printf("Digite um jogador para buscar (Apelido - Equipe):\n");
        fgets(apelido_busca, sizeof(apelido_busca), stdin);
        apelido_busca[strcspn(apelido_busca, "\n")] = '\0';

        encontrado = 0;
        for(a = 0; a < 5; a++){
            if(strcmp(lista_jogadores[a], apelido_busca) == 0){
                encontrado = 1;
                break;
           }
        }
        if(encontrado == 1) {
        printf("Esse jogador esta na lista.\n");
    } else {
        printf("Esse jogador nao esta na lista.\n");
    }

    inicializar_mapa(linhas, colunas, mapa);
    exibir_mapa(linhas, colunas, mapa);

    posicionar_jogador(linhas, colunas, mapa, lista_jogadores);
    exibir_mapa(linhas, colunas, mapa);

    reposicionar_jogador(linhas, colunas, mapa);
    exibir_mapa(linhas, colunas, mapa);

    return 0;
}