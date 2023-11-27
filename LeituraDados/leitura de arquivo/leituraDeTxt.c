#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("teste3.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char line[100];
    while (fgets(line, 100, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
    return 0;
}
