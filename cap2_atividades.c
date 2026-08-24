//Capítulo 2 — Cadastro dinâmico de jogadores e equipes
//Atividade 7 - Dados textuais do jogador
#include <stdio.h>
#include <string.h>

//Definindo os tamanhos fixos
#define TAMANHO_NOME 80
#define TAMANHO_APELIDO 30
#define TAMANHO_SENHA 16

int main()
{
    char nome[TAMANHO_NOME], apelido[TAMANHO_APELIDO], senha[TAMANHO_SENHA], confirmacao[TAMANHO_SENHA];
    int erro, i;
    
    printf("Digite o seu nome completo: \n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; //Substitui o '\n' por '\0'

    do
    {
        erro = 0;
        
        printf("Digite o seu apelido: \n");
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

        printf("Digite a sua senha: \n");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if(strlen(senha) < 1) {
            erro = 1;
            printf("A senha nao pode ficar em branco\n");
        }else {

        for(i = 0; senha[i] != '\0'; i++)
    {

        if(senha[i] == ' ')
        {
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

    printf("Cadastro concluido com sucesso!");

    return 0;
}