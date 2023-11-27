#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boca.h"

int main() {
  // Abre o arquivo de código
  FILE *arquivo_codigo = fopen("codigo.c", "r");
  if (arquivo_codigo == NULL) {
    printf("Erro ao abrir o arquivo de código.\n");
    return 1;
  }

  // Lê o código do arquivo
  char *codigo;
  int tamanho_codigo;
  fscanf(arquivo_codigo, "%d\n", &tamanho_codigo);
  codigo = malloc(sizeof(char) * tamanho_codigo);
  fgets(codigo, tamanho_codigo, arquivo_codigo);

  // Fecha o arquivo de código
  fclose(arquivo_codigo);

  // Compila o código
  int status = boca_compilar(codigo);
  if (status != 0) {
    printf("Erro ao compilar o código.\n");
    return 1;
  }

  // Executa o código
  int resultado = boca_executar(codigo);

  // Imprime o resultado
  printf("Resultado: %d\n", resultado);

  // Liberta a memória alocada
  free(codigo);

  return 0;
}
