#include <stdio.h>
#include <dirent.h>

int main() {
    // Especifique o caminho do diret�rio que voc� deseja listar
    const char *caminho = "./teste"; // Ponto refere-se ao diret�rio atual

    // Abra o diret�rio
    DIR *diretorio = opendir(caminho);

    // Verifique se o diret�rio foi aberto com sucesso
    if (diretorio) {
        // Leia os arquivos no diret�rio
        struct dirent *entrada;
        while ((entrada = readdir(diretorio)) != NULL) {
            // Imprima o nome do arquivo
            printf("%s\n", entrada->d_name);
        }

        // Feche o diret�rio ap�s a leitura
        closedir(diretorio);
    } else {
        // Se houver um erro ao abrir o diret�rio, imprima uma mensagem de erro
        perror("Erro ao abrir o diret�rio");
    }

    return 0;
}
