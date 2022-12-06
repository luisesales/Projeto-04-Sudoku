#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#define EMPTY short(0)
#define SIZE 9

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>

using std::vector;


enum gameState{
    GAMENTRANCE = 0,
    MAINMENU,
    HELPING,
    NEWGAME,
    FINISHEDGAME,
    PLAYMODE,
    PLACING,
    REMOVING,
    UNDOING,
    CHECKING,
    QUITTING,
    ENDING
};

namespace sudoku{

    class SudokuGame{
        vector<vector<short>> m_Rboard;
        gameController gControl;

    };

    

    /// Controlador do jogo em andamento
    class boardController{
        /// Função que valida um vector que recebeu se ele é válido
        bool validate(const vector<short> b);

        /// Função que validará um tabuleiro inteiro utilizando da função validate
        bool is_valid( vector<vector<short>> b);
    };

    /// Gerador dos resultados do controller
    class gamePrinter{

    };
    /// Leitor de configuração do jogo
    class gameConfig{
        boardController bControl;
        vector<vector<short>> m_Rboard; // Tabueliro completo lido pelo arquivo

        public:
        // Ctro
        gameConfig();
        // Método que lerá as configurações e aplicará dados as variáveis
        bool ReadConfig(int argc, char* argv[]); 

        // Método que retornará o vector lido
        vector<vector<short>> get_Rboard(void) const
        { return m_Rboard; };
    };
};

#endif