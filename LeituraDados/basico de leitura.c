#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boca.h"

int main() {
  // Abre o arquivo de entrada
  FILE *arquivo_entrada = fopen("entrada.txt", "r");
  if (arquivo_entrada == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }

  // Lê o cabeçalho do arquivo
  char *nome_problema;
  int dificuldade;
  int tempo_limite;
  fscanf(arquivo_entrada, "%s %d %d\n", &nome_problema, &dificuldade, &tempo_limite);

  // Lê a entrada do problema
  char *entrada;
  int tamanho_entrada;
  fscanf(arquivo_entrada, "%d\n", &tamanho_entrada);
  entrada = malloc(sizeof(char) * tamanho_entrada);
  fgets(entrada, tamanho_entrada, arquivo_entrada);

  // Fecha o arquivo de entrada
  fclose(arquivo_entrada);

  // Imprime as informações do problema
  printf("Nome do problema: %s\n", nome_problema);
  printf("Dificuldade: %d\n", dificuldade);
  printf("Tempo limite: %d segundos\n", tempo_limite);
  printf("Entrada: %s\n", entrada);

  // Liberta a memória alocada
  free(entrada);

  return 0;
}
