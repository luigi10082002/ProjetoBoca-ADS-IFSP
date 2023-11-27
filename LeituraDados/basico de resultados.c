#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boca.h"

int main() {
  // Abre o arquivo de submissão
  FILE *arquivo_submissao = fopen("submissao.txt", "r");
  if (arquivo_submissao == NULL) {
    printf("Erro ao abrir o arquivo de submissão.\n");
    return 1;
  }

  // Lê o cabeçalho do arquivo
  char *nome_problema;
  int dificuldade;
  int tempo_limite;
  fscanf(arquivo_submissao, "%s %d %d\n", &nome_problema, &dificuldade, &tempo_limite);

  // Lê o código do arquivo
  char *codigo;
  int tamanho_codigo;
  fscanf(arquivo_submissao, "%d\n", &tamanho_codigo);
  codigo = malloc(sizeof(char) * tamanho_codigo);
  fgets(codigo, tamanho_codigo, arquivo_submissao);

  // Fecha o arquivo de submissão
  fclose(arquivo_submissao);

  // Compila o código
  int status = boca_compilar(codigo);
  if (status != 0) {
    printf("Erro ao compilar o código.\n");
    return 1;
  }

  // Executa o código
  int resultado = boca_executar(codigo);

  // Obtém os resultados da submissão
  int status_submissao;
  float pontuacao_submissao;
  boca_obter_resultados_submissao(nome_problema, &status_submissao, &pontuacao_submissao);

  // Imprime os resultados
  printf("Status da submissão: %d\n", status_submissao);
  printf("Pontuação da submissão: %.2f\n", pontuacao_submissao);

  // Liberta a memória alocada
  free(codigo);

  return 0;
}
