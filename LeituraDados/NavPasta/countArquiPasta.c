#include <stdio.h>
#include <dirent.h>

int main() {
    // Especifique o caminho do diretório que você deseja listar
    const char *caminho = "./teste"; // Ponto refere-se ao diretório atual

    // Abra o diretório
    DIR *diretorio = opendir(caminho);

    // Verifique se o diretório foi aberto com sucesso
    if (diretorio) {
        // Leia os arquivos no diretório
        struct dirent *entrada;
        while ((entrada = readdir(diretorio)) != NULL) {
            // Imprima o nome do arquivo
            printf("%s\n", entrada->d_name);
        }

        // Feche o diretório após a leitura
        closedir(diretorio);
    } else {
        // Se houver um erro ao abrir o diretório, imprima uma mensagem de erro
        perror("Erro ao abrir o diretório");
    }

    return 0;
}
