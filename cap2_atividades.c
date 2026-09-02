//Capítulo 2 — Cadastro dinâmico de jogadores e equipes
//Atividade 8 - Cópia, concatenação e lista de nomes
#include <stdio.h>
#include <string.h>

//Definindo os tamanhos fixos
#define TAMANHO_NOME 80
#define TAMANHO_APELIDO 30
#define TAMANHO_SENHA 16
#define TAMANHO_EQUIPE 50

int main()
{
    char nome[TAMANHO_NOME], apelido[TAMANHO_APELIDO], senha[TAMANHO_SENHA], confirmacao[TAMANHO_SENHA], equipe[TAMANHO_EQUIPE];
    int erro, i, a, tamanho_necessario, encontrado;
    char lista_jogadores[5][80], apelido_busca[TAMANHO_NOME];
    
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

    return 0;
}