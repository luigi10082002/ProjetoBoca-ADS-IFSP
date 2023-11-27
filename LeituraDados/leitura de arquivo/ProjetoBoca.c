#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void navigationPastas() {

    char caminhoArquivo[] = "./AmbienteTeste/";
    char caminhoEntradas[] = "/entrada";
    char op[100]; // Tamanho suficientemente grande para a entrada do usuário

    // Receber uma entrada do usuário e atribuir à string
    printf("Digite uma string: ");
    scanf("%99s", op); // Evita estouro de buffer usando um tamanho menor que o array

    // Determinar o tamanho da nova string
    int tamanho = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoEntradas) + strlen(op) + 1; // +1 para o caractere nulo

    // Alocar espaço para a nova string
    char concatCaminho[tamanho];

    // Concatenar as strings
    snprintf(concatCaminho, sizeof(concatCaminho), "%s%s%s", caminhoArquivo, op, caminhoEntradas);

    const char *caminho = concatCaminho; // Ponto refere-se ao diretório atual

    // Abra o diretório
    DIR *diretorio = opendir(caminho);

    printf("%s\n", concatCaminho);
    // Verifique se o diretório foi aberto com sucesso
    if (diretorio) {
        // Leia os arquivos no diretório
        struct dirent *entrada;
        while ((entrada = readdir(diretorio)) != NULL) {
            // Imprima o nome do arquivo
            printf("%s\n", entrada->d_name);
        }

        // Feche o diretório após a leitura
        closedir(diretorio);
    } else {
        // Se houver um erro ao abrir o diretório, imprima uma mensagem de erro
        perror("Erro ao abrir o diretorio");
    }
}

int main() {
    navigationPastas();

    // Abre o arquivo de entrada
    FILE *arquivo_entrada = fopen("entrada.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Lê o cabeçalho do arquivo
    char nome_problema[100];
    int dificuldade;
    int tempo_limite;
    fscanf(arquivo_entrada, "%s %d %d\n", nome_problema, &dificuldade, &tempo_limite);

    // Lê a entrada do problema
    char *entrada;
    int tamanho_entrada;
    fscanf(arquivo_entrada, "%d\n", &tamanho_entrada);
    entrada = malloc(sizeof(char) * tamanho_entrada);
    fgets(entrada, tamanho_entrada, arquivo_entrada);

    // Fecha o arquivo de entrada
    fclose(arquivo_entrada);

    // Imprime as informações do problema
    printf("Nome do problema: %s\n", nome_problema);
    printf("Dificuldade: %d\n", dificuldade);
    printf("Tempo limite: %d segundos\n", tempo_limite);
    printf("Entrada: %s\n", entrada);

    // Liberta a memória alocada
    free(entrada);

    return 0;
}

