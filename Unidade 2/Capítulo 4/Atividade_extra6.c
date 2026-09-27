/*
 Capítulo 4 - Persistência do catálogo de partidas
 Atividade Extra

 - Realize a atividade 21 - leitura e escrita de arquivos.
 Atividade 21 - Leitura e escrita de arquivo de texto
 
 Contexto: Resultados mantidos apenas na memória desaparecem ao fechar o programa. O gerenciador precisa criar um relatório simples, que também possa ser aberto e conferido em um editor de texto.
 Descrição detalhada: Defina uma estrutura de partida e implemente a gravação de seus campos em formato textual. Depois de fechar o arquivo de escrita, abra-o novamente para leitura e apresente os dados recuperados. Separe as responsabilidades em funções e trate cada recurso de arquivo em seu próprio fluxo.
 Requisitos:
 - armazenar identificador, jogador e pontuação em cada partida;
 - abrir o arquivo no modo correto para escrita;
 - utilizar um formato textual consistente;
 - fechar e reabrir o arquivo para leitura;
 - ler somente enquanto a operação retornar sucesso;
 - confirmar na tela os dados recuperados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

// Função responsável por salvar os dados no arquivo
int salvar_partida(const char *caminho, Partida p_escrita){
    FILE *file = fopen(caminho, "w");

    if (file == NULL){
        perror("Erro ao abrir o arquivo para escrita"); // Exibe a mensagem personalizada junto com o erro do sistema
        return 0; // Falha
    }

    fprintf(file, "ID: %d | Nome: %s | Pontuacao: %d\n", p_escrita.id, p_escrita.jogador, p_escrita.pontuacao);

    fclose(file);
    return 1; // Sucesso
}

// Função responsável por ler e exibir os dados recuperados
int ler_partidas(const char *caminho){
    FILE *file = fopen(caminho, "r");

    if (file == NULL){
        perror("Erro ao abrir o arquivo para leitura");
        return 0;
    }

    Partida p_leitura;
    printf("\nDados Recuperados do Arquivo:\n");

    // Lê enquanto a operação retornar sucesso (retorna 3 valores lidos corretamente)
    while (fscanf(file, "ID: %d | Nome: %49s | Pontuacao: %d", &p_leitura.id, p_leitura.jogador, &p_leitura.pontuacao) == 3){
        printf("ID: %d | Jogador: %s | Pontuacao: %d\n", p_leitura.id, p_leitura.jogador, p_leitura.pontuacao);
    }

    fclose(file);
    return 1;
}

int main(){
    Partida p;

    printf("Digite as informacoes da partida (ID, Nome, Pontuacao): ");
    if (scanf("%d %49s %d", &p.id, p.jogador, &p.pontuacao) != 3){
        printf("Entrada invalida.\n");
        return 1;
    }

    const char *arquivo = "./partidas.txt";

    if (salvar_partida(arquivo, p)){
        printf("\nPartida salva com sucesso em '%s'.\n", arquivo);
    }

    ler_partidas(arquivo);

    return 0;
}