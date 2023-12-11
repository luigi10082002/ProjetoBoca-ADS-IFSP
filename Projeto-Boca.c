#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_TAMANHO_CAMINHO 256
#define MAX_TAMANHO_LINHA 1000

// Enumeracao para representar opcoes de continuacao
enum OpcaoContinuar {
    CONTINUAR_SIM = 's',
    CONTINUAR_NAO = 'n',
};

// Estrutura para armazenar configuracoes
typedef struct {
    char diretorioPrincipal[MAX_TAMANHO_CAMINHO];
    char caminhoCode[MAX_TAMANHO_CAMINHO];
    char caminhoEntradas[MAX_TAMANHO_CAMINHO];
    char caminhoSaidasEsperadas[MAX_TAMANHO_CAMINHO];
} Configuracoes;

// Funcao para liberar a memoria alocada para o conteudoArray
void liberarMemoriaConteudoArray(char *conteudoArray[], int numLinhas) {
	int i;
    for (i = 0; i < numLinhas; i++) {
        free(conteudoArray[i]);
    }
}

// Funcao para comparar duas strings ignorando espa�os em branco no inicio e no final
int compararStringsIgnorandoEspacos(const char *str1, const char *str2) {
    while (isspace(*str1)) {
        str1++;
    }

    while (isspace(*str2)) {
        str2++;
    }

    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    // Ignora espacos no final das strings
    while (isspace(*str1)) {
        str1++;
    }

    while (isspace(*str2)) {
        str2++;
    }

    // Retorna a diferenca entre os caracteres, se houver
    return (*str1 - *str2);
}

// Funcao para realizar a compilacao do codigo
int realizarCompilacao(const char *caminhoCodeTxt) {
    char comandoCompilar[MAX_TAMANHO_CAMINHO + 50];
    snprintf(comandoCompilar, sizeof(comandoCompilar), "gcc -o temp_executable %s", caminhoCodeTxt);

    if (system(comandoCompilar) == 0) {
        printf("Compila��o concluida com sucesso.\n");

        system("./temp_executable > temp_output.txt");

        FILE *outputFile = fopen("temp_output.txt", "r");
        if (outputFile == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo temporario de saida.\n");
            return 1;
        }

        char linha[MAX_TAMANHO_LINHA];
        while (fgets(linha, sizeof(linha), outputFile) != NULL) {
            printf("%s", linha);
        }

        fclose(outputFile);
    } else {
        fprintf(stderr, "Erro na compilacao do codigo.\n");
        return 1;
    }

    return 0;
}

// Funcao para realizar a comparacao entre a saida e a saida esperada
bool realizarComparacao(const char *saida, const char *saidaEsperada) {
    printf("Saida do programa:\n%s", saida);
    printf("Saida esperada:\n%s", saidaEsperada);

    int resultadoComparacao = compararStringsIgnorandoEspacos(saida, saidaEsperada);

    if (resultadoComparacao == 0) {
        printf("As saidas coincidem. Teste bem-sucedido!\n");
        return true;
    } else {
        printf("As saidas nao coincidem. Teste falhou.\n");
        return false;
    }
}

// Fun��o para ler o conte�do de um arquivo e armazenar em um array
int readFile(const char *caminho, const char *nomeArquivo, char *conteudoArray[], int *linhas) {
    char caminhoCompleto[MAX_TAMANHO_LINHA];
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", caminho, nomeArquivo);

    FILE *arquivo = fopen(caminhoCompleto, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", caminhoCompleto);
        return 1;  // Indica erro
    }

    char linha[MAX_TAMANHO_LINHA];
    int contadorLinhas = 0;

    // le cada linha do arquivo e armazena no array
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Aloca memoria para a linha e a armazena no array
        conteudoArray[contadorLinhas] = strdup(linha);

        // Incrementa o contador de linhas
        contadorLinhas++;
    }

    // Atualiza o numero total de linhas
    *linhas = contadorLinhas;

    fclose(arquivo);
    return 0;  // Indica sucesso
}

// Funcao principal
int main() {
    Configuracoes config = {
        .diretorioPrincipal = "./AmbienteTeste/",  // Diretorio principal onde todas as questoes estao localizadas
        .caminhoCode = "/code",
        .caminhoEntradas = "/entrada",
        .caminhoSaidasEsperadas = "/saidaEsperada",
    };

    char opcaoContinuar;

    char *conteudoArray[100];  // Declare antes do loop do-while
    char nomeQuestao[100];     // Ajuste o tamanho conforme necess�rio
    char nomeArquivoCode[100]; // Adicao para o nome do arquivo de codigo

    printf("Bem vindo ao programa de teste.\n");

    do {
        printf("Digite o nome da questao: ");
        scanf("%99s", nomeQuestao); // Garanta que o tamanho n�o exceda 99 caracteres

        // Adiciona o nome da quest�o aos caminhos espec�ficos
        snprintf(config.caminhoCode, sizeof(config.caminhoCode), "%s%s/code", config.diretorioPrincipal, nomeQuestao);
        snprintf(config.caminhoEntradas, sizeof(config.caminhoEntradas), "%s%s/entrada", config.diretorioPrincipal, nomeQuestao);
        snprintf(config.caminhoSaidasEsperadas, sizeof(config.caminhoSaidasEsperadas), "%s%s/saidaEsperada", config.diretorioPrincipal, nomeQuestao);

        printf("Digite o nome do arquivo de codigo: ");
        scanf("%99s", nomeArquivoCode);

        if (nomeQuestao[0] == '\0' || nomeArquivoCode[0] == '\0') {
            printf("Nome da questao ou nome do arquivo de codigo invalido. Tente novamente.\n");
            continue;
        }

        char caminhoCodeTxt[MAX_TAMANHO_CAMINHO + MAX_TAMANHO_CAMINHO + 10];
        snprintf(caminhoCodeTxt, sizeof(caminhoCodeTxt), "%s/%s.txt", config.caminhoCode, nomeArquivoCode);

        if (realizarCompilacao(caminhoCodeTxt) == 0) {
            char caminhoSaidaEsperada[MAX_TAMANHO_CAMINHO + MAX_TAMANHO_CAMINHO + 20];
            snprintf(caminhoSaidaEsperada, sizeof(caminhoSaidaEsperada), "%s/saidaEsperada.txt", config.caminhoSaidasEsperadas);

            char *saidaEsperadaArray[100];
            int numLinhasSaidaEsperada = 0;

            int resultadoLeituraSaidaEsperada = readFile(caminhoSaidaEsperada, "saidaEsperada.txt", saidaEsperadaArray, &numLinhasSaidaEsperada);

            if (resultadoLeituraSaidaEsperada == 0) {
                // Realiza a compara��o entre a sa�da e a sa�da esperada
                char caminhoSaida[MAX_TAMANHO_CAMINHO + MAX_TAMANHO_CAMINHO + 20];
                snprintf(caminhoSaida, sizeof(caminhoSaida), "%s/saida.txt", config.caminhoEntradas);

                int numLinhasSaida = 0;
                int resultadoLeituraSaida = readFile(caminhoSaida, "saida.txt", conteudoArray, &numLinhasSaida);

                if (resultadoLeituraSaida == 0) {
                    realizarComparacao(conteudoArray[0], saidaEsperadaArray[0]);

                    // Libera a mem�ria alocada para cada linha da sa�da esperada
                    liberarMemoriaConteudoArray(saidaEsperadaArray, numLinhasSaidaEsperada);
                }
            }
        }

        printf("Deseja continuar (S/n)? ");
        scanf(" %c", &opcaoContinuar);

    } while (opcaoContinuar == CONTINUAR_SIM);

    // Libera a mem�ria alocada para os resultados
    liberarMemoriaConteudoArray(conteudoArray, 1);

    return 0;
}
