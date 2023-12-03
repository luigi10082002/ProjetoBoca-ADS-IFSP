#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void navigationPastas() {
    char caminhoArquivo[] = "./AmbienteTeste/";
    char caminhoEntradas[] = "/entrada";
    char op[100]; // Tamanho suficientemente grande para a entrada do usu�rio

    // Receber uma entrada do usu�rio e atribuir � string
    printf("Digite uma string: ");
    scanf("%99s", op); // Evita estouro de buffer usando um tamanho menor que o array

    // Determinar o tamanho da nova string
    int tamanho = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoEntradas) + 1; // +1 para o caractere nulo

    // Alocar espa�o para a nova string
    char concatCaminho[tamanho];

    // Concatenar as strings
    snprintf(concatCaminho, sizeof(concatCaminho), "%s%s%s", caminhoArquivo, op, caminhoEntradas);

    const char *caminho = concatCaminho; // Ponto refere-se ao diret�rio atual

    // Abrir o diret�rio
    DIR *diretorio = opendir(caminho);

    //printf("%s\n", concatCaminho);
    // Verificar se o diret�rio foi aberto com sucesso
    if (diretorio) {
        // Ler os arquivos no diret�rio
        struct dirent *entrada;
        while ((entrada = readdir(diretorio)) != NULL) {
            // Imprimir o nome do arquivo
            printf("%s\n", entrada->d_name);

            // Verificar se � um arquivo TXT
            if (strstr(entrada->d_name, ".txt") != NULL) {
                // Se sim, abrir o arquivo e ler seu conte�do
                char caminhoCompleto[256]; // Tamanho suficientemente grande
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", caminho, entrada->d_name);

                FILE *arquivo = fopen(caminhoCompleto, "r");

                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", caminhoCompleto);
                    return;
                }

                // Ler e imprimir o conte�do do arquivo
                char linha[256]; // Tamanho suficientemente grande
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    printf("%s", linha);
                }

                // Fechar o arquivo
                fclose(arquivo);
            }
        }

        // Fechar o diret�rio ap�s a leitura
        closedir(diretorio);
    } else {
        // Se houver um erro ao abrir o diret�rio, imprimir uma mensagem de erro
        perror("Erro ao abrir o diretorio");
    }
}

int main() {
    navigationPastas();

    // ... O restante do seu c�digo permanece inalterado

    return 0;
}

