#include <iostream>

#include "sudoku.h";

int main(int argc, char* argv[])
{   
    SudokuGame sdkg;

    // Iniciar o Jogo com os parâmetros
    sdkg.gameInit(argc,argv)

    // Display de Mensagem de Início
    sdkg.welcomeMessage()

    while(!sdkg.gameOver()){
        // Ler comando escrito pelo usuário
        sdkg.inputCommand()
        // Atualizar o Jogo de acordo com o que é jogado
        sdkg.update();
        // Renderizar no console a visualização do usuário
        sdkg.render();
    }
    return 0
}