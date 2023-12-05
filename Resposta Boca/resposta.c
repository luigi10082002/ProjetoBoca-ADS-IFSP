#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_NAME 256
#define MAX_STRING_SIZE 100

void removeNewLine(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    char aluno[MAX_STRING_SIZE];
    char saida[MAX_STRING_SIZE];

    printf("Digite a saída do aluno: ");
    fgets(aluno, sizeof(aluno), stdin);
    removeNewLine(aluno);

    printf("Digite o nome do arquivo de saída esperada: ");
    char fileName[MAX_FILE_NAME];
    fgets(fileName, sizeof(fileName), stdin);
    removeNewLine(fileName);

    // Abrir o arquivo de saída esperada
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", fileName);
        return 1;
    }

    // Ler o conteúdo do arquivo
    fgets(saida, sizeof(saida), file);
    removeNewLine(saida);

    // Fechar o arquivo
    fclose(file);

    // Compare as strings usando strcmp()
    int comparacao = strcmp(aluno, saida);

    // Verifique o resultado da comparação
    if (comparacao == 0) {
        printf("As saídas são iguais.\n");
    } else {
        printf("As saídas são diferentes.\n");
    }

    return 0;
}

