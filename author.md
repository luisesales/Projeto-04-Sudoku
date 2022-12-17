# Introduction

Sudoku é um jogo de tabuleiro clássico cujo objetivo é completar o tabuleiro preenchendo-o com números de 1 à 9 de forma que toda linha, coluna e sessão (noneto) possua todos os números uma vez pelo menos.

Breve descrição do projeto.

# Author(s)

Luís Eduardo de Oliveira Sales
duduosales@hotmail.com
Indique o nome do autor e email.

# Problems found or limitations

<!-- TODO -->
Lista aqui os problemas encontrados (se houve algum) e as
possíveis limitações do programa.

# Grading

<!-- TODO -->
Preencha os itens que você implementou, indicando qual a nota esperada para cada item.


Item     | Valor máximo   | Valor esperado
-------- | :-----: | :-----:
Trata corretamente os argumentos de linha de comando | 5 pts | 5
Lê e armazena os vários puzzles contidos em um arquivo de entrada |5 pts| 5
Exibe corretamente a tela principal com o menu de ações |5 pts| 5
Permite a escolha dos vários puzzles lidos do arquivo  |5 pts| 5
Executa corretamente a ação de posicionamento de dígitos no tabuleiro (comando posicionar) identificação jogadas inválidas |11 pts| 11
Executa corretamente a remoção de dígitos posicionados pelo jogador (comando remover) |10 pts| 10
Executa corretamente o comando de desfazer ação |12 pts| 12
Executa corretamente o comando de verificação do tabuleiro |12 pts| 12
Exibe as regras do jogo quando solicitado |5 pts| 5
Indica corretamente se uma partida finalizada foi vencida ou perdida |5 pts| 5
Apresenta uma interface com usuário igual ou similar a que foi especificada nesse documento |5 pts| 5
Apresenta uma validação robusta dos comandos textuais de ação fornecidos pelo usuário |5 pts| 5
Exibe corretamente a lista de dígitos disponíveis, conforme o progresso do jogo |5 pts| 5
Apresenta as indicações com `setas` da coordenada da célula que foi alvo da última ação |5 pts| 5
Apresenta um fluxo correto entre telas, com opção de retomar uma partida suspensa e solicitação de confirmação de finalização de partida, caso exista uma partida em andamento |5 pts| 5

# Compiling and Runnig

mkdir build
cmake -S source -B build
cmake --build build
./build/sudoku <options>
./build/sudoku <-help||--help> for usage

Indique aqui como compilar e executar seu programa.
