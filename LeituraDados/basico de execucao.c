#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boca.h"

int main() {
  // Abre o arquivo de c�digo
  FILE *arquivo_codigo = fopen("codigo.c", "r");
  if (arquivo_codigo == NULL) {
    printf("Erro ao abrir o arquivo de c�digo.\n");
    return 1;
  }

  // L� o c�digo do arquivo
  char *codigo;
  int tamanho_codigo;
  fscanf(arquivo_codigo, "%d\n", &tamanho_codigo);
  codigo = malloc(sizeof(char) * tamanho_codigo);
  fgets(codigo, tamanho_codigo, arquivo_codigo);

  // Fecha o arquivo de c�digo
  fclose(arquivo_codigo);

  // Compila o c�digo
  int status = boca_compilar(codigo);
  if (status != 0) {
    printf("Erro ao compilar o c�digo.\n");
    return 1;
  }

  // Executa o c�digo
  int resultado = boca_executar(codigo);

  // Imprime o resultado
  printf("Resultado: %d\n", resultado);

  // Liberta a mem�ria alocada
  free(codigo);

  return 0;
}
