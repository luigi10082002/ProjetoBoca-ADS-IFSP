/*#include <stdio.h>

int main() {
    // Definir um tamanho fixo para a string
    char minhaString[50];

    // Receber uma entrada do usuário e atribuir à string
    printf("Digite uma string: ");
    scanf("%s", minhaString);
    
    minhaString[] = "teste";
    
	printf("%s\n", minhaString);

    return 0;
}*/

#include <stdio.h>
#include <string.h>

int main() {
    // Definir arrays de caracteres
    char string1[20] = "Hello, ";
    char string2[] = "World!";

    // Concatenar as strings
    strcat(string1, string2);

    // Imprimir a string resultante
    printf("Concatenada: %s\n", string1);

    return 0;
}
