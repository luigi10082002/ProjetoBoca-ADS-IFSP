#include <stdio.h>
#include <string.h>

int main() {
    FILE *file;
    char line[100];

    file = fopen("teste3.txt", "r");
    if (file == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        int num = atoi(line);
        printf("Numero lido: %d\n", num);
    }

    fclose(file);
    return 0;
}
