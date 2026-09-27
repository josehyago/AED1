/*
 Capítulo 4 - Persistência do catálogo de partidas
 Atividade 22 - Histórico incremental e fim de arquivo
 
 Contexto: Registrar uma nova partida não pode apagar as anteriores. O arquivo deverá funcionar como um histórico crescente e sua listagem precisa terminar corretamente no final dos dados.
 Descrição detalhada: Continue o gerenciador acrescentando novos registros ao fim do relatório. Crie uma função para percorrer todo o histórico e exibi-lo sem repetir o último registro, evitando o erro comum de testar feof antes de tentar a leitura.
 Requisitos:
 - abrir o histórico em modo de anexação;
 - preservar o conteúdo previamente gravado;
 - basear o laço no retorno de fscanf, fgets ou operação equivalente;
 - diferenciar fim normal de leitura e dado malformado;
 - contar os registros lidos;
 - informar quando o histórico estiver vazio.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

// Função responsável por salvar os dados no arquivo.
int adicionar_partida(const char *caminho, Partida p_escrita){
    FILE *file = fopen(caminho, "a");

    if (file == NULL){
        perror("Erro ao abrir o arquivo para escrita"); // Exibe a mensagem personalizada junto com o erro do sistema.
        return 0; // Falha.
    }

    fprintf(file, "ID: %d | Nome: %s | Pontuacao: %d\n", p_escrita.id, p_escrita.jogador, p_escrita.pontuacao);

    fclose(file);
    return 1; // Sucesso.
}

// Função responsável por ler e checar o histórico.
int ler_partidas(const char *caminho){
    FILE *file = fopen(caminho, "r");

    if (file == NULL){
        perror("Erro ao abrir o arquivo para leitura");
        return 0;
    }

    Partida p_leitura;
    int lidos = 0;

    printf("\nHistorico de partidas:\n");

    // Lê enquanto a operação retornar sucesso (retorna 3 valores lidos corretamente).
    while (fscanf(file, "ID: %d | Nome: %49s | Pontuacao: %d\n", &p_leitura.id, p_leitura.jogador, &p_leitura.pontuacao) == 3){
        printf("ID: %d | Jogador: %s | Pontuacao: %d\n", p_leitura.id, p_leitura.jogador, p_leitura.pontuacao);
        lidos++;
    }

    if (lidos == 0){
        printf("O historico esta vazio. Nenhuma partida registrada.\n");
    } else {
        printf("\nTotal de partidas registradas: %d\n", lidos);
    }

    // Diferenciar fim normal de dado malformado.
    if (feof(file)){
        // Saiu porque chegou no fim do arquivo.
        printf("Leitura concluida com sucesso (FEOF).\n");
    } else{
        // Saiu, mas não chegou no fim do arquivo.
        printf("Aviso: A leitura foi interrompida. Dados malformados encontrados no arquivo!\n");
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

    if (adicionar_partida(arquivo, p)){
        printf("\nPartida salva com sucesso em '%s'.\n", arquivo);
    }

    ler_partidas(arquivo);

    return 0;
}