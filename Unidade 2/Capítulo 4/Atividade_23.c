/*
 Capítulo 4 - Persistência do catálogo de partidas
 Atividade 23 - Validação e transformação de arquivos de texto
 
 Contexto: Ao final de uma temporada, o sistema precisa ler resultados brutos, aplicar uma regra de bonificação e produzir um relatório processado. O arquivo de origem pode não existir, e o destino pode não ser criado por falta de permissão ou outro erro.
 Descrição detalhada: Implemente uma transformação completa entre dois arquivos. Para cada partida válida lida do arquivo de origem, aplique um bônus documentado e escreva o resultado no destino. Nenhuma operação poderá ocorrer antes de verificar se a abertura correspondente foi bem-sucedida.
 Requisitos:
 - verificar todos os retornos de fopen;
 - emitir mensagens específicas para falha de origem e de destino;
 - processar cada registro apenas quando a leitura for completa;
 - escrever os dados transformados em outro arquivo;
 - fechar os dois arquivos nos caminhos de sucesso e erro;
 - apresentar a quantidade de registros processados.
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

// Função que lê da origem, aplica bônus e salva no destino
int processar_temporada(const char *arq_origem, const char *arq_destino){
    FILE *forigem = fopen(arq_origem, "r");

    if (forigem == NULL){
        perror("Erro ao abrir o arquivo de origem");
        return -1;
    }

    FILE *fdestino = fopen(arq_destino, "w");

    if (fdestino == NULL){
        perror("Erro ao criar o arquivo de destino");
        fclose(forigem);
        return -1;
    }

    Partida p;
    int processados = 0;
    int bonus = 50; 

    printf("\nProcessando temporada...\n");

    while (fscanf(forigem, "ID: %d | Nome: %49s | Pontuacao: %d\n", &p.id, p.jogador, &p.pontuacao) == 3){
        p.pontuacao += bonus; 
        fprintf(fdestino, "ID: %d | Nome: %s | Pontuacao: %d\n", p.id, p.jogador, p.pontuacao);
        processados++;
    }

    if (feof(forigem)){
        printf("Processamento concluido com sucesso ate o fim do arquivo.\n");
    } else {
        printf("Aviso: O processamento parou antes do fim. Dados malformados na origem!\n");
    }

    fclose(forigem);
    fclose(fdestino);

    return processados;
}

int main(){
    const char *arquivo = "./partidas.txt";
    const char *arquivo_relatorio = "./partidas_relatorio.txt";

    Partida p;

    printf("Digite as informacoes da partida (ID, Nome, Pontuacao): ");
    if (scanf("%d %49s %d", &p.id, p.jogador, &p.pontuacao) != 3){
        printf("Entrada invalida.\n");
        return 1;
    }

    if (adicionar_partida(arquivo, p)){
        printf("\nPartida salva com sucesso em '%s'.\n", arquivo);
    }

    ler_partidas(arquivo);

    int total = processar_temporada(arquivo, arquivo_relatorio);

    if (total >= 0){
        printf("\nForam processados e bonificados %d registros no relatorio final.\n", total);
        
        printf("\nRelatorio Final:");
        ler_partidas(arquivo_relatorio); 
    }
    return 0;
}