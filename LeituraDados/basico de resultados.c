#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boca.h"

int main() {
  // Abre o arquivo de submiss�o
  FILE *arquivo_submissao = fopen("submissao.txt", "r");
  if (arquivo_submissao == NULL) {
    printf("Erro ao abrir o arquivo de submiss�o.\n");
    return 1;
  }

  // L� o cabe�alho do arquivo
  char *nome_problema;
  int dificuldade;
  int tempo_limite;
  fscanf(arquivo_submissao, "%s %d %d\n", &nome_problema, &dificuldade, &tempo_limite);

  // L� o c�digo do arquivo
  char *codigo;
  int tamanho_codigo;
  fscanf(arquivo_submissao, "%d\n", &tamanho_codigo);
  codigo = malloc(sizeof(char) * tamanho_codigo);
  fgets(codigo, tamanho_codigo, arquivo_submissao);

  // Fecha o arquivo de submiss�o
  fclose(arquivo_submissao);

  // Compila o c�digo
  int status = boca_compilar(codigo);
  if (status != 0) {
    printf("Erro ao compilar o c�digo.\n");
    return 1;
  }

  // Executa o c�digo
  int resultado = boca_executar(codigo);

  // Obt�m os resultados da submiss�o
  int status_submissao;
  float pontuacao_submissao;
  boca_obter_resultados_submissao(nome_problema, &status_submissao, &pontuacao_submissao);

  // Imprime os resultados
  printf("Status da submiss�o: %d\n", status_submissao);
  printf("Pontua��o da submiss�o: %.2f\n", pontuacao_submissao);

  // Liberta a mem�ria alocada
  free(codigo);

  return 0;
}
