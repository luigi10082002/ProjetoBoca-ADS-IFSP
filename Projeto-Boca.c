#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MAX_ARQUIVOS 1000
#define MAX_TAMANHO_CONTEUDO 10000

// Funcaoo para imprimir os arquivos em um diretorio
void printFilesInDirectory(const char *caminho) {
    DIR *diretorio = opendir(caminho);

    if (diretorio) {
        struct dirent *entrada;
        while ((entrada = readdir(diretorio)) != NULL) {
            printf("%s\n", entrada->d_name);
        }

        closedir(diretorio);
    } else {
        perror("Erro ao abrir o diretorio");
    }
}

// Funcaoo para ler o conteudo de um arquivo e armazenar em um array
int readFile(const char *caminho, const char *nomeArquivo, char *conteudoArray[], int *linhas) {
    char caminhoCompleto[256];
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", caminho, nomeArquivo);

    FILE *arquivo = fopen(caminhoCompleto, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", caminhoCompleto);
        return 1;  // Indica erro
    }

    char linha[256];
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

char** readAllFiles(const char *diretorio) {
    DIR *dir;
    struct dirent *entrada;

    // Aloca espaco para armazenar os resultados
    char **resultados = (char **)malloc(MAX_ARQUIVOS * sizeof(char *));
    int num_resultados = 0;

    // Abre o diretorio
    dir = opendir(diretorio);

    // Verifica se o diretorio foi aberto com sucesso
    if (dir == NULL) {
        perror("Erro ao abrir o diretorio");
        exit(EXIT_FAILURE);
    }

    // Itera sobre cada entrada no diretorio
    while ((entrada = readdir(dir)) != NULL) {
        // Ignora as entradas "." e ".."
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            char caminho_completo[PATH_MAX];
            snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", diretorio, entrada->d_name);

            // Verifica se a entrada e um arquivo (nao um diretorio)
            struct stat st;
            if (stat(caminho_completo, &st) == 0 && S_ISREG(st.st_mode)) {
                FILE *arquivo = fopen(caminho_completo, "r");

                // Verifica se o arquivo foi aberto com sucesso
                if (arquivo == NULL) {
                    perror("Erro ao abrir o arquivo");
                    exit(EXIT_FAILURE);
                }

                // Aloca espaco para armazenar o conteudo do arquivo
                char *conteudo = (char *)malloc(MAX_TAMANHO_CONTEUDO * sizeof(char));
                if (conteudo == NULL) {
                    perror("Erro ao alocar memoria");
                    exit(EXIT_FAILURE);
                }

                // Le o conteudo do arquivo
                int pos = 0;
                char caractere;
                while ((caractere = fgetc(arquivo)) != EOF) {
                    conteudo[pos++] = caractere;
                }

                // Adiciona o conteudo ao array de resultados
                conteudo[pos] = '\0';  // Adiciona o caractere nulo ao final do conteudo
                resultados[num_resultados++] = conteudo;

                // Fecha o arquivo
                fclose(arquivo);
            }
        }
    }

    // Fecha o diretorio
    closedir(dir);

    // Adiciona um marcador de final ao array de resultados
    resultados[num_resultados] = NULL;

    return resultados;
}



int main() {
	int i;
	
    char caminhoArquivo[] = "./AmbienteTeste/";
    char caminhoCode[] = "/code";
    char caminhoEntradas[] = "/entrada";
    char caminhoSaidasEsperadas[] = "/saidaEsperada";
    
    //char execCode[] = "gcc -o temp_executable ";
    
    char op[100];
    char nomeArquivoEscolhido[100];

    printf("Digite em maiusculo a questao: ");
    scanf("%99s", op);

    int tamanho = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoCode) + 1;
    char concatCaminho[tamanho];
    snprintf(concatCaminho, sizeof(concatCaminho), "%s%s%s", caminhoArquivo, op, caminhoCode);

    const char *caminho = concatCaminho;

    // Chama a funcao para imprimir os arquivos no diretorio
    printFilesInDirectory(caminho);

    printf("Digite o nome do arquivo que deseja ler (incluindo a extensao .txt): ");
    scanf("%99s", nomeArquivoEscolhido);

    // Array para armazenar as linhas do arquivo
    char *conteudoArray[100];  // Defina um tamanho apropriado

    // Variavel para armazenar o numero total de linhas
    int numLinhas = 0;

    // Chama a funcao para ler o conteudo do arquivo e armazenar no array
    int resultado = readFile(caminho, nomeArquivoEscolhido, conteudoArray, &numLinhas);
	
    // Verifica se a leitura do arquivo foi bem-sucedida
    if (resultado == 0) {
        //printf("Leitura do arquivo concluida com sucesso.\n");

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
	        printf("Compilacao concluida com sucesso.\n");
	        
	
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
    }
	
    // Remove o arquivo temporário
    remove("temp_code.c");
    remove("temp_executable");
    remove("temp_output.txt");

    // Libera a memoria alocada para cada linha
    for (i = 0; i < numLinhas; i++) {
        free(conteudoArray[i]);
    }
    	
	int tamanhoEntradas = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoEntradas) + 1;
    char concatCaminhoEntradas[tamanhoEntradas];
    snprintf(concatCaminhoEntradas, sizeof(concatCaminhoEntradas), "%s%s%s", caminhoArquivo, op, caminhoEntradas);

    const char *caminhoEntradasArquivos = concatCaminhoEntradas;
        
	char **resultadosEntradas = readAllFiles(caminhoEntradasArquivos);
    
    printf("==================================================\n");
    printf("Entradas\n");
    printf("==================================================\n");

    // Imprime os resultados
    for (i = 0; resultadosEntradas[i] != NULL; i++) {
        printf("Conteudo do arquivo %d:\n%s\n", i + 1, resultadosEntradas[i]);
        printf("==================================================\n");
        free(resultadosEntradas[i]); // Libera a memÃƒÂ³ria alocada para cada conteÃƒÂºdo
    }
    
    // Libera a memoria alocada para o array de resultados
    free(resultadosEntradas);
    
    int tamanhoSaidasEsperadas = strlen(caminhoArquivo) + strlen(op) + strlen(caminhoSaidasEsperadas) + 1;
    char concatCaminhoSaidasEsperadas[tamanhoSaidasEsperadas];
    snprintf(concatCaminhoSaidasEsperadas, sizeof(concatCaminhoSaidasEsperadas), "%s%s%s", caminhoArquivo, op, caminhoSaidasEsperadas);

    const char *caminhoSaidasEsperadasArquivos = concatCaminhoSaidasEsperadas;
        
	char **resultadosSaidasEsperadasArquivos = readAllFiles(caminhoSaidasEsperadasArquivos);
    
    printf("==================================================\n");
    printf("Saidas Esperadas\n");
    printf("==================================================\n");


    // Imprime os resultados
    for (i = 0; resultadosSaidasEsperadasArquivos[i] != NULL; i++) {
        printf("Conteudo do arquivo %d:\n%s\n", i + 1, resultadosSaidasEsperadasArquivos[i]);
        printf("==================================================\n");
        free(resultadosSaidasEsperadasArquivos[i]); // Libera a memÃƒÂ³ria alocada para cada conteÃƒÂºdo
    }

    // Libera a memoria alocada para o array de resultados
    free(resultadosSaidasEsperadasArquivos);


    
	//compilarExecutarCodigo(conteudoArray);

    // ... O restante do seu codigo permanece inalterado

    return 0;
}
