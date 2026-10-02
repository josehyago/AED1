/*
 Capítulo 4 - Persistência do catálogo de partidas
 Atividade 25 - Vetores binários e tratamento de erros
 
 Contexto: O usuário deseja salvar toda a temporada em uma única operação e recuperá-la posteriormente, mantendo a quantidade e a ordem das partidas.
 Descrição detalhada: Finalize o gerenciador persistindo um vetor completo de estruturas. Grave metadados suficientes para saber quantos elementos devem ser reconstruídos, aloque o vetor durante a leitura e só substitua os dados atuais quando a operação terminar corretamente.
 Requisitos:
 - salvar a quantidade antes dos registros;
 - verificar possíveis valores inválidos ao carregar;
 - alocar espaço para a quantidade registrada;
 - conferir o total devolvido por fread e fwrite;
 - liberar memória e fechar o arquivo em caso de erro;
 - oferecer menu para cadastrar, listar, salvar e carregar partidas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

int adicionar_partida(const char *caminho, Partida p_escrita);
int processar_temporada(const char *arq_origem, const char *arq_destino);
int salvar_binario(const char *caminho, Partida *p_escrita, int quantidade);
int ler_binario(const char *caminho, Partida **p_leitura, int *quantidade);
int exibir_binario(const char *caminho);
int ler_partidas(const char *caminho);
void limpar_buffer(void);
void menu();

int main(){
    const char *arquivo_txt = "./partidas.txt";
    const char *arquivo_relatorio = "./partidas_relatorio.txt";
    const char *arquivo_bin = "./partida.bin";

    Partida *historico = NULL; // Começa vazio
    int total_partidas = 0;
    int opcao;

    do {
        menu();
        if (scanf("%d", &opcao) != 1){
            limpar_buffer();
            opcao = 0;
        }

        switch(opcao){
            case 1: {
                Partida *temp = realloc(historico, (total_partidas + 1) * sizeof(Partida));
                if (temp == NULL){
                    printf("Falha ao alocar memoria para nova partida.\n");
                    free(historico);
                    exit(1);
                }
                historico = temp;
                printf("\nNova Partida\n");
                printf("ID: "); 
                scanf("%d", &historico[total_partidas].id);
                printf("Jogador: "); 
                scanf("%49s", historico[total_partidas].jogador);
                printf("Pontuacao: "); 
                scanf("%d", &historico[total_partidas].pontuacao);
                limpar_buffer();
                total_partidas++;
                printf("Partida cadastrada.\n");
                break;
            }
            case 2:
                printf("\nPartidas Registradas (%d)\n", total_partidas);
                if (total_partidas == 0){
                    printf("Nenhuma partida em memoria no momento.\n");
                }
                for (int i = 0; i < total_partidas; i++){
                    printf("ID: %d | Jogador: %s | Pontuacao: %d\n", historico[i].id, historico[i].jogador, historico[i].pontuacao);
                }
                break;
            case 3:
                if (salvar_binario(arquivo_bin, historico, total_partidas)){
                    printf("Tudo salvo.\n");
                }
                break;
            case 4:
                ler_binario(arquivo_bin, &historico, &total_partidas);
                break;
            case 5:
                exibir_binario(arquivo_bin);
                break;
            case 6:
                if (total_partidas == 0){
                    printf("Nenhuma partida na memoria para salvar no texto.\n");
                } else {
                    // Pega o ultimo elemento do vetor em memoria e grava no .txt
                    if (adicionar_partida(arquivo_txt, historico[total_partidas - 1])) {
                        printf("Partida ID %d salva com sucesso em %s!\n", historico[total_partidas - 1].id, arquivo_txt);
                    }
                }
                break;
            case 7:
                ler_partidas(arquivo_txt);
                break;
            case 8: 
            {
                int proc = processar_temporada(arquivo_txt, arquivo_relatorio);
                if (proc >= 0){
                    printf("Processamento concluido! %d partidas atualizadas com bonus no arquivo %s.\n", proc, arquivo_relatorio);
                }
                break;
            }
            case 9:
                ler_partidas(arquivo_relatorio);
                break;
            case 10:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 10);

    if (historico != NULL){
        free(historico);
    }

    return 0;
}

void limpar_buffer(void){
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

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

    printf("\nProcessando temporada (%s -> %s)...\n", arq_origem, arq_destino);

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
int salvar_binario(const char *caminho, Partida *p_escrita, int quantidade){
    FILE *file = fopen(caminho, "wb");

    if (file == NULL){
        perror("Erro ao salvar arquivo binario.");
        return 0;
    }

    // Grava o Metadado (a quantidade de partidas).
    if (fwrite(&quantidade, sizeof(int), 1, file) != 1){
        printf("Erro ao gravar a quantidade.\n");
        fclose(file);
        return 0;
    }

    // Grava o vetor inteiro de uma vez só.
    if (quantidade > 0){
        size_t escritos = fwrite(p_escrita, sizeof(Partida), quantidade, file);
        if (escritos != (size_t)quantidade){
            printf("Erro: Foram gravadas apenas %zu de %d partidas.\n", escritos, quantidade);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

// Função para ler em binário
int ler_binario(const char *caminho, Partida **p_leitura, int *quantidade){
    FILE *file = fopen(caminho, "rb");

    if (file == NULL){
        perror("Erro ao abrir arquivo binario para leitura");
        return 0;
    }

    int quantidade_lida;

    // Lê a quantidade primeiro
    if (fread(&quantidade_lida, sizeof(int), 1, file) != 1){
        printf("Erro ao ler metadados do arquivo.\n");
        fclose(file);
        return 0;
    }

    if (quantidade_lida < 0 || quantidade_lida > 10000){ // Um limite máximo de segurança
        printf("Erro: Arquivo corrompido (Quantidade invalida: %d).\n", quantidade_lida);
        fclose(file);
        return 0;
    }

    // Aloca memória temporária.
    Partida *p_temp = NULL;
    if (quantidade_lida > 0){
        p_temp = (Partida *)malloc(quantidade_lida * sizeof(Partida));
        if (p_temp == NULL){
            printf("Erro: Falta de memoria.\n");
            fclose(file);
            return 0;
        }
    
        // Lê todas as partidas de uma vez para o vetor temporário.
        size_t lidos = fread(p_temp, sizeof(Partida), quantidade_lida, file);
        if (lidos != (size_t)quantidade_lida){
            printf("Erro ao ler os registros. Arquivo incompleto.\n");
            free(p_temp); // libera memória em caso de erro.
            fclose(file);
            return 0;
        }
    }

    if (*p_leitura != NULL){
        free(*p_leitura); // Libera o vetor antigo.
    }
    
    *p_leitura = p_temp; // Aponta para o novo vetor que acabamos de carregar.
    *quantidade = quantidade_lida; // Atualiza a quantidade.

    fclose(file);
    printf("Temporada carregada com sucesso. (%d partidas)\n", quantidade_lida);
    return 1;
}

// Lê o arquivo .bin
int exibir_binario(const char *caminho){
    FILE *file = fopen(caminho, "rb");

    if (file == NULL){
        perror("Erro ao abrir arquivo binario para leitura");
        return 0;
    }

    int quantidade_lida = 0;

    // Le o metadado (quantidade)
    if (fread(&quantidade_lida, sizeof(int), 1, file) != 1){
        printf("Erro ao ler quantidade do arquivo binario.\n");
        fclose(file);
        return 0;
    }

    printf("\nLendo Conteudo do Arquivo Binario (%s)\n", caminho);
    printf("Total de registros: %d\n\n", quantidade_lida);

    Partida p;
    int lidos = 0;

    // Le estrutura por estrutura
    for (int i = 0; i < quantidade_lida; i++){
        if (fread(&p, sizeof(Partida), 1, file) == 1){
            printf("ID: %d | Jogador: %s | Pontuacao: %d\n", p.id, p.jogador, p.pontuacao);
            lidos++;
        } else {
            printf("Aviso: O arquivo terminou antes do esperado na posicao %d.\n", i + 1);
            break;
        }
    }

    if (lidos == 0){
        printf("Nenhum registro encontrado no arquivo binario.\n");
    }

    fclose(file);
    return 1;
}

void menu(){
    printf("\nMENU\n");
    printf("1. Cadastrar Partida (Memoria)\n");
    printf("2. Listar Partidas (Memoria)\n");
    printf("3. Salvar Temporada (Binario .bin)\n");
    printf("4. Carregar Temporada (Binario .bin)\n");
    printf("5. Ler e Exibir Arquivo Binario (Binario .bin)\n");
    printf("6. Salvar Ultima Partida Cadastrada (Texto .txt)\n");
    printf("7. Ler Historico de Partidas (Texto .txt)\n");
    printf("8. Processar Temporada Texto (+50 pts -> Relatorio .txt)\n");
    printf("9. Ler Arquivo Texto de Relatorio (partidas_relatorio.txt)\n");
    printf("10. Sair\n");
    printf("Escolha: ");
}