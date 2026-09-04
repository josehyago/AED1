//Capítulo 2 — Cadastro dinâmico de jogadores e equipes
//Atividade 13 - Matrizes dinâmicas de duas formas 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definindo os tamanhos fixos
#define TAMANHO_NOME 80
#define TAMANHO_APELIDO 30
#define TAMANHO_SENHA 16
#define TAMANHO_EQUIPE 50
#define TAMANHO_LINHAS 5
#define TAMANHO_COLUNAS 5

// Funções da Atividade 11
void inicializar_mapa(int linhas, int colunas, int mapa[linhas][colunas])
{
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            mapa[il][ic] = -1;
        }
    }
}

void exibir_mapa(int linhas, int colunas, int mapa[linhas][colunas])
{
    printf("\nMapa atual\n");
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

void posicionar_jogador(int linhas, int colunas, int quantidade, int mapa[linhas][colunas], char lista_jogadores[quantidade][80])
{
    int il, ic;

    for(int i = 0; i < quantidade; i++) {
        printf("\nPosicionando o Jogador %d: %s\n", i + 1, lista_jogadores[i]);
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

void reposicionar_jogador(int linhas, int colunas, int quantidade, int mapa[linhas][colunas])
{
    int jogador, nova_linha, nova_coluna;
    int encontrado = 0;

    printf("\nReposicionar Jogador\n");
    printf("Digite o numero do jogador que deseja mover (1 a %d): ", quantidade);
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

// Funções da Atividade 12
void exibir_diagnostico(void *dado, char tipo)
{
    if (tipo == 'i'){
        int *valor_inteiro = (int *)dado;
        printf("Valor inteiro recebido: %d\n", *valor_inteiro); 
    }else if(tipo == 's'){
        char *valor_string = (char *)dado;
        printf("Texto recebido: %s\n", valor_string);
    }else printf("Tipo de dado nao suportado\n");


}

int *alocar_historico(int quantidade_partidas)
{
    if (quantidade_partidas <= 0 || quantidade_partidas > 100){
        printf("Erro: Quantidade de partidas invalida.\n");
        return NULL;
    }

    int *historico = (int *) malloc(quantidade_partidas * sizeof(int));
    
    return historico; 
}

void preencher_historico(int *historico, int quantidade_partidas)
{
    printf("\nPreenchimento do Historico\n");

    for(int i = 0; i < quantidade_partidas; i++){
        printf("Digite a pontuacao da partida %d: ", i + 1);
        scanf("%d", &historico[i]);
    }
}

void exibir_historico(int *historico, int quantidade_partidas)
{
    printf("\nHistorico de Pontuacoes\n");

    for(int i = 0; i < quantidade_partidas; i++){
        printf("Partida %d: %d pontos\n", i + 1, historico[i]);
    }
}

void calcular_media(int *historico, int quantidade_partidas)
{
    int soma = 0;
    
    for(int i = 0; i < quantidade_partidas; i++){
        soma += historico[i];
    }
    
    float media = (float)soma / quantidade_partidas; 
    printf("Media de pontuacao: %.2f\n", media);
}

void localizar_maior(int *historico, int quantidade_partidas) {
    int maior_valor = historico[0];
    int posicao = 0;

    for(int i = 1; i < quantidade_partidas; i++){
        if(historico[i] > maior_valor) {
            maior_valor = historico[i];
            posicao = i;
        }
    }
    printf("Maior pontuacao: %d (alcancada na partida %d)\n", maior_valor, posicao + 1);
}

// Funções da Atividade 13

// Comparação entre as duas formas de alocação de matrizes dinâmicas:
// Matriz Linear: Mais rapida pois os dados estao em um bloco continuo na memoria (melhor uso de cache). Exige apenas um malloc e um free, mas o acesso (l * colunas + c) é menos intuitiva.
// Matriz de Ponteiros: Acesso padrão (matriz[l][c]), porem a memoria fica fragmentada. Exige varios mallocs e frees, sendo mais lenta e complexa de gerenciar em caso de falha.

int *alocar_matriz_linear(int linhas, int colunas)
{
    if(linhas <= 0 || colunas <= 0 || (linhas * colunas) > 1000000){
        printf("Erro: Valores invalidos ou grandes para a matriz linear.\n");
        return NULL;
    }
    int *matriz = (int *) malloc(linhas * colunas * sizeof(int));
    return matriz;
}

void preencher_matriz_linear(int *matriz, int linhas, int colunas)
{
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            matriz[il * colunas + ic] = -1; 
        }
    }
}

void exibir_matriz_linear(int *matriz, int linhas, int colunas)
{
    printf("\nExibicao - Matriz Linear\n");
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            if(matriz[il * colunas + ic] == -1) printf("[ ~ ]");
            else printf("[ %d ]", matriz[il * colunas + ic]);
        }
        printf("\n");
    }
}

int **alocar_matriz_ponteiros(int linhas, int colunas)
{
    if (linhas <= 0 || colunas <= 0) return NULL;

    int **matriz = (int **) malloc(linhas * sizeof(int *));
    if (matriz == NULL) return NULL;

    for(int i = 0; i < linhas; i++){
        matriz[i] = (int *) malloc(colunas * sizeof(int));
        
        if (matriz[i] == NULL){
            printf("Erro de memoria na linha %d.\n", i);
            for(int j = 0; j < i; j++){
                free(matriz[j]);
            }

            free(matriz);
            return NULL;
        }
    }
    return matriz;
}

void preencher_matriz_ponteiros(int **matriz, int linhas, int colunas)
{
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            matriz[il][ic] = -1;
        }
    }
}

void exibir_matriz_ponteiros(int **matriz, int linhas, int colunas)
{
    printf("\nExibicao - Matriz de Ponteiros\n");
    for(int il = 0; il < linhas; il++){
        for(int ic = 0; ic < colunas; ic++){
            if(matriz[il][ic] == -1) printf("[ * ]");
            else printf("[ %d ]", matriz[il][ic]);
        }
        printf("\n");
    }
}

void liberar_matriz_ponteiros(int **matriz, int linhas)
{
    if(matriz == NULL) return;
    for (int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int main()
{
    // Variáveis da Atividade 11
    char nome[TAMANHO_NOME], apelido[TAMANHO_APELIDO], senha[TAMANHO_SENHA], confirmacao[TAMANHO_SENHA], equipe[TAMANHO_EQUIPE];
    char (*lista_jogadores)[80] = NULL;
    char apelido_busca[TAMANHO_NOME];
    int erro, i, a, tamanho_necessario, encontrado, quantidade = 0; 
    int mapa_fixo[TAMANHO_LINHAS][TAMANHO_COLUNAS];
    
    // Variáveis da Atividade 12
    int quantidade_partidas = 0;
    int *historico = NULL;
    
    // Variáveis da Atividade 13
    int linhas_mapa, colunas_mapa;
    int *mapa_linear = NULL;
    int **mapa_ponteiro = NULL;
    int opcao;

    do
    {
        printf("\tMENU PRINCIPAL\n");
        printf("\n1 - Cadastrar Equipe e Posicionar o Mapa. (Ativ. 11)");
        printf("\n2 - Historico de Pontuacoes. (Ativ. 12)");
        printf("\n3 - Matrizes Dinamicas. (Ativ. 13)");
        printf("\n0 - Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1:
                printf("\nCadastro de Equipe\n");
                printf("\nDigite o nome da equipe: ");
                fgets(equipe, sizeof(equipe), stdin);
                equipe[strcspn(equipe, "\n")] = '\0';

                printf("Digite a quantidade de jogadores da equipe: ");
    
                while(1) {
                    scanf("%d", &quantidade);
                    getchar();

                    if(quantidade > 0) break;
                        printf("\nQuantidade invalida. Digite um numero maior que zero: \n");
                    }
                    if (lista_jogadores != NULL){
                        free(lista_jogadores); 
                        lista_jogadores = NULL;
                    }
                                    
                    lista_jogadores = (char (*)[80]) malloc(quantidade * sizeof(*lista_jogadores)); 
                    // A vantagem de usar sizeof(*lista_jogadores) é que o compilador calcula automaticamente a quantidade de caracteres que foi definido no vetor, caso queira modificar, só será necessário mudar lá na declaração, assim evitando trocar nas duas linhas sempre.

                    if (lista_jogadores == NULL) {
                        printf("\nMemoria insuficiente para alocar os jogadores.");
                        return 1;
                    }   

                printf("\nFerramenta de Diagnostico\n");
                exibir_diagnostico(&quantidade, 'i');
                exibir_diagnostico(equipe, 's');
    
                for(a = 0; a < quantidade; a++){

                    printf("\nCadastro do Jogador %d\n", a + 1);

                    printf("Digite o nome completo do jogador %d: ", a + 1);
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0'; //Substitui o '\n' por '\0'

                    do
                    {
                        erro = 0;
        
                        printf("Digite o apelido do jogador %d: ", a + 1);
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

                        printf("Digite a senha do jogador %d: ", a + 1);
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

                        printf("Confirme a sua senha: ");
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
                
                printf("\nCadastro concluido com sucesso!\n");
        
                printf("\nLista de jogadores: \n");
                for(a = 0; a < quantidade; a++){
                    printf("Jogador %d: %s\n", a + 1, lista_jogadores[a]);
                }
        
                printf("\nDigite um jogador para buscar (Apelido - Equipe): ");
                fgets(apelido_busca, sizeof(apelido_busca), stdin);
                apelido_busca[strcspn(apelido_busca, "\n")] = '\0';

                encontrado = 0;
                for(a = 0; a < quantidade; a++){
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

                inicializar_mapa(TAMANHO_LINHAS, TAMANHO_COLUNAS, mapa_fixo);
                exibir_mapa(TAMANHO_LINHAS, TAMANHO_COLUNAS, mapa_fixo);

                posicionar_jogador(TAMANHO_LINHAS, TAMANHO_COLUNAS, quantidade, mapa_fixo, lista_jogadores);
                exibir_mapa(TAMANHO_LINHAS, TAMANHO_COLUNAS, mapa_fixo);

                reposicionar_jogador(TAMANHO_LINHAS, TAMANHO_COLUNAS, quantidade, mapa_fixo);
                exibir_mapa(TAMANHO_LINHAS, TAMANHO_COLUNAS, mapa_fixo);
    
                break;

            case 2:
                printf("\nHistorico de Partidas\n");
                printf("\nQuantas partidas a equipe jogou? (Max: 100): ");
                scanf("%d", &quantidade_partidas);

                if (historico != NULL){
                    free(historico); 
                    historico = NULL;}

                historico = alocar_historico(quantidade_partidas);
                if (historico == NULL){
                    printf("\nNao foi possivel criar o historico de partidas.\n");
                    free(lista_jogadores); 
                    return 1; 
                }

                preencher_historico(historico, quantidade_partidas);
                exibir_historico(historico, quantidade_partidas);
                calcular_media(historico, quantidade_partidas);
                localizar_maior(historico, quantidade_partidas);
                break;
                
            case 3:
                printf("\nMatrizes Dinamicas\n");
                printf("Digite as dimensoes para os novos mapas (linhas e colunas): ");
                scanf("%d %d", &linhas_mapa, &colunas_mapa);

                mapa_linear = alocar_matriz_linear(linhas_mapa, colunas_mapa);
                if (mapa_linear != NULL){
                    preencher_matriz_linear(mapa_linear, linhas_mapa, colunas_mapa);
                    exibir_matriz_linear(mapa_linear, linhas_mapa, colunas_mapa);
                    free(mapa_linear);
                    mapa_linear = NULL;
                }

                mapa_ponteiro = alocar_matriz_ponteiros(linhas_mapa, colunas_mapa);
                if (mapa_ponteiro != NULL){
                    preencher_matriz_ponteiros(mapa_ponteiro, linhas_mapa, colunas_mapa);
                    exibir_matriz_ponteiros(mapa_ponteiro, linhas_mapa, colunas_mapa);
                    liberar_matriz_ponteiros(mapa_ponteiro, linhas_mapa);
                    mapa_ponteiro = NULL;
                }
                break;

            case 0:
                printf("\nEncerrando.\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    if (lista_jogadores != NULL) free(lista_jogadores);
    if (historico != NULL) free(historico);

    return 0;
}