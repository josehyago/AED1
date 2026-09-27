/*
 Capítulo 4 - Persistência do catálogo de partidas
 Atividade Extra

 - Realize a atividade 24 - escrita e leitura de arquivos binários
 Atividade 24 - Registros em arquivo binário
 
 Contexto: Além do relatório legível, o jogo precisa de um formato direto para restaurar registros sem interpretar linhas de texto. Um arquivo binário pode armazenar a estrutura persistente de cada partida.
 Descrição detalhada: Acrescente rotinas que gravem e leiam uma estrutura de partida com fwrite e fread. Compare o registro restaurado com o original e trate leituras incompletas. Caso a estrutura venha a conter ponteiros, eles não deverão ser persistidos como endereços.
 Requisitos:
 - usar os modos wb e rb;
 - calcular tamanhos com sizeof;
 - conferir a quantidade escrita e lida;
 - gravar somente campos que façam sentido após reiniciar o programa;
 - detectar arquivo vazio ou registro incompleto;
 - exibir o objeto reconstruído.
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

// Função para gravar em binário
int salvar_binario(const char *caminho, Partida p_escrita){
    FILE *file = fopen(caminho, "wb");

    if (file == NULL){
        perror("Erro ao criar arquivo binario");
        return 0;
    }

    size_t escritos = fwrite(&p_escrita, sizeof(Partida), 1, file);
    
    if (escritos != 1){
        printf("Erro na gravacao do registro.\n");
    }

    fclose(file);
    return (escritos == 1);
}

// Função para ler em binário
int ler_binario(const char *caminho){
    FILE *file = fopen(caminho, "rb");

    if (file == NULL){
        perror("Erro ao abrir arquivo binario para leitura");
        return 0;
    }

    Partida p_leitura;

    size_t lidos = fread(&p_leitura, sizeof(Partida), 1, file);

    if (lidos == 1){
        printf("\nRegistro realizado com sucesso (Binario):\n");
        printf("ID: %d | Jogador: %s | Pontuacao: %d\n", p_leitura.id, p_leitura.jogador, p_leitura.pontuacao);
    } else {
        if (feof(file)){
            printf("Arquivo binario esta vazio ou o registro esta incompleto.\n");
        } else {
            printf("Erro de leitura no arquivo binario.\n");
        }
    }

    fclose(file);
    return (lidos == 1);
}

int main(){
    const char *arquivo = "./partidas.txt";
    const char *arquivo_relatorio = "./partidas_relatorio.txt";
    const char *arquivo_bin = "./partida.bin";

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

    if (salvar_binario(arquivo_bin, p)){
        printf("\nPartida salva em binario com sucesso.\n");
    }

    ler_binario(arquivo_bin);

    return 0;
}