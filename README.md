###### TERAFAS ######

# 1 -> Receber dados da interface
    A -> Problema que sera testado
	  B -> Respostas esperadas
	  C -> Entradas do usuario
	  D -> Saidas esperadas
	
# 2 -> Tratar dados
    A -> Validar arquivo a ser lido
    B -> Validar se o arquivo n�o esta corrompido
    C -> Validar se existe um c�digo a ser testado
    D -> Validar se existe uma resposta a ser usada como saida esperada
	
# 3 -> Rodar o c�digo a ser testado
    A -> Testar se existem erros de compila��o no codigo
    B -> Testar codigo completo
	
# 4 -> Receber respostas da execucao do codigo
    A -> Receber resposta do codigo
    B -> Comparar com respostas esperadas

##### DIVISÃO DAS TAREFAS #####

## Luigi ##
  # 1
  # 2

## Vinicius ##
  # 3

## Arthur ##
  # 4

#### DIARIO DE CONCLUSÕES ####

### Luigi ###
  21/11/2023 -> Leitura de arquivo .txt
  21/11/2023 -> Adição de input para escolha de atividade que será corrigida
  21/11/2023 -> Adequação de caminho para a pasta da atividade escolhida

  23/11/2023 -> Navegação entre pastas 
  23/11/2023 -> Correção de bugs
  23/11/2023 -> Inicio da junção entre leitura de aquivos e navegação entre pastas
