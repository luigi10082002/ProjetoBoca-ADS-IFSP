#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ... (seu código anterior)

int main() {
    // ... (seu código anterior)

    // Concatena o caminho completo do arquivo code.txt
    int tamanhoCodeTxt = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoCode) + strlen("/code.txt") + 1;
    char concatCaminhoCodeTxt[tamanhoCodeTxt];
    snprintf(concatCaminhoCodeTxt, sizeof(concatCaminhoCodeTxt), "%s%s%s%s", caminhoArquivo, op, caminhoCode, "/code.txt");

    const char *caminhoCodeTxt = concatCaminhoCodeTxt;

    // Comando para compilar o código
    char comandoCompilar[100];
    snprintf(comandoCompilar, sizeof(comandoCompilar), "gcc -o temp_executable temp_code.c");

    // Cria um arquivo temporário para armazenar o código do arquivo code.txt
    FILE *tempFile = fopen("temp_code.c", "w");
    if (tempFile == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo temporário.\n");
        return 1;
    }

    // Lê o conteúdo do arquivo code.txt e grava no arquivo temporário
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

    // Executa o comando de compilação
    if (system(comandoCompilar) == 0) {
        // Comando de compilação bem-sucedido
        printf("Compilação concluída com sucesso.\n");

        // Redireciona a saída para um arquivo temporário
        system("./temp_executable > temp_output.txt");

        // Lê o arquivo temporário com a saída do programa compilado
        FILE *outputFile = fopen("temp_output.txt", "r");
        if (outputFile == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo temporário de saída.\n");
            return 1;
        }

        // Exibe ou armazena a saída do programa compilado
        while (fgets(linha, sizeof(linha), outputFile) != NULL) {
            printf("%s", linha);
        }

        fclose(outputFile);
    } else {
        // Erro na compilação
        fprintf(stderr, "Erro na compilação do código.\n");
    }

    // Remove os arquivos temporários
    remove("temp_code.c");
    remove("temp_executable");
    remove("temp_output.txt");

    // ... (seu código posterior)

    return 0;
}

