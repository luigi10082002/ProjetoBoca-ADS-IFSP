#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ... (seu c�digo anterior)

int main() {
    // ... (seu c�digo anterior)

    // Concatena o caminho completo do arquivo code.txt
    int tamanhoCodeTxt = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoCode) + strlen("/code.txt") + 1;
    char concatCaminhoCodeTxt[tamanhoCodeTxt];
    snprintf(concatCaminhoCodeTxt, sizeof(concatCaminhoCodeTxt), "%s%s%s%s", caminhoArquivo, op, caminhoCode, "/code.txt");

    const char *caminhoCodeTxt = concatCaminhoCodeTxt;

    // Comando para compilar o c�digo
    char comandoCompilar[100];
    snprintf(comandoCompilar, sizeof(comandoCompilar), "gcc -o temp_executable temp_code.c");

    // Cria um arquivo tempor�rio para armazenar o c�digo do arquivo code.txt
    FILE *tempFile = fopen("temp_code.c", "w");
    if (tempFile == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo tempor�rio.\n");
        return 1;
    }

    // L� o conte�do do arquivo code.txt e grava no arquivo tempor�rio
    char linha[1000];
    FILE *codeFile = fopen(caminhoCodeTxt, "r");
    if (codeFile == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", caminhoCodeTxt);
        return 1;
    }

    while (fgets(linha, sizeof(linha), codeFile) != NULL) {
        fputs(linha, tempFile);
    }

    fclose(codeFile);
    fclose(tempFile);

    // Executa o comando de compila��o
    if (system(comandoCompilar) == 0) {
        // Comando de compila��o bem-sucedido
        printf("Compila��o conclu�da com sucesso.\n");

        // Redireciona a sa�da para um arquivo tempor�rio
        system("./temp_executable > temp_output.txt");

        // L� o arquivo tempor�rio com a sa�da do programa compilado
        FILE *outputFile = fopen("temp_output.txt", "r");
        if (outputFile == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo tempor�rio de sa�da.\n");
            return 1;
        }

        // Exibe ou armazena a sa�da do programa compilado
        while (fgets(linha, sizeof(linha), outputFile) != NULL) {
            printf("%s", linha);
        }

        fclose(outputFile);
    } else {
        // Erro na compila��o
        fprintf(stderr, "Erro na compila��o do c�digo.\n");
    }

    // Remove os arquivos tempor�rios
    remove("temp_code.c");
    remove("temp_executable");
    remove("temp_output.txt");

    // ... (seu c�digo posterior)

    return 0;
}

