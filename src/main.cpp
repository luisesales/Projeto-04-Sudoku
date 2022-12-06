#include <iostream>

#include "sudoku.h";

int main(int argc, char* argv[])
{   
    sdkg::SudokuGame game;

    // Iniciar o Jogo com os parâmetros
    game.Init(argc,argv)

    // Display de Mensagem de Início
    game.welcomeMessage()

    while(!game.Over()){
        // Ler comando escrito pelo usuário
        game.inputCommand()
        // Atualizar o Jogo de acordo com o que é jogado
        game.update();
        // Renderizar no console a visualização do usuário
        game.render();
    }
    return 0
}