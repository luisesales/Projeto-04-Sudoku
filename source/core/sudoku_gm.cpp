#include <cassert>
#include <stdexcept>
#include <iterator>
#include <string.h>

#include "sudoku_gm.h"


namespace sdkg {
    
    std::string convertToString(char* a, int size) {
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        if (a[i] == '\0') {
        return s;
        }
        s = s + a[i];
    }
    return s;
    }
    void clear_screen(){
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

    bool isFile(char* name) {
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            return true;
        }

        std::string strName = convertToString(name, 256);
        if (strName.find(".") == std::string::npos) {
            return false;
        }

        return true;
    }
    /// Lambda expression that transform the string to lowercase.
    auto STR_LOWERCASE = [](const char * t)->std::string{
        std::string str{ t };
        std::transform( str.begin(), str.end(), str.begin(), ::tolower );
        return str;
    };

    /// Default constructor
    SudokuGame::SudokuGame(){
        m_opt.total_checks = 3; // Default value.
        m_opt.input_filename = "./data/input.txt"; // Default value.
    }

    void SudokuGame::usage( std::string msg ) const{
        if ( msg != "" ) std::cerr << "sudoku: " << msg << "\n\n";

        std::cerr << "Usage: sudoku [-c <num>] [--help] <input_puzzle_file>\n"
                  << "  Game options:\n"
                  << "    -c     <num> Number of checks per game. Default = 3.\n"
                  << "    --help       Print this help text.\n";
        std::cerr << std::endl;

        exit( msg != "" ? 1 : 0 );
    }

    void SudokuGame::process_events(){
        if ( m_game_state == game_state_e::STARTING or
             m_game_state == game_state_e::HELPING  or
             m_game_state == game_state_e::CHECKING_MOVES or
             m_game_state == game_state_e::FINISHED_PUZZLE )
        {
            // Reading a simple enter from user.
            std::string line;
            std::getline(std::cin, line);
            m_game_state = game_state_e::READING_MAIN_OPT;     
        }
        else if ( m_game_state == game_state_e::READING_MAIN_OPT )
        {
            uint aux;
            std::cin >> aux;
            if(aux > 3 || aux < 0) m_curr_main_menu_opt = main_menu_opt_e::INVALID;
            else m_curr_main_menu_opt = main_menu_opt_e(aux);
            switch (m_curr_main_menu_opt)
            {
            case main_menu_opt_e::PLAY:
                m_game_state = game_state_e::PLAYING_MODE;
                break;
            
            case main_menu_opt_e::NEW_GAME:
                m_game_state = game_state_e::REQUESTING_NEW_GAME;
                break;
            
            case main_menu_opt_e::QUIT:
                m_game_state = game_state_e::QUITTING;
                break;
            
            case main_menu_opt_e::HELP:
                m_game_state = game_state_e::HELPING;
                break;
            
            case main_menu_opt_e::INVALID:
                m_curr_msg = "Please insert a Valid value from [1,4]";
                break;

            default:
                break;
            }

        }
        else if ( m_game_state == game_state_e::PLAYING_MODE )
        {

        }
        else if ( m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH )
        {
        }
    }
    
    void SudokuGame::initialize(int argc,char* argv[]){
        std::stringstream ss;
        string line; // Var where lines will be saved
        std::fstream bReader; // File Reader;
        short pAux{0}; // Auxiliar var for number reading 
        SBoard rBoard; // Auxiliar var for reading board
        PlayerBoard pbAux; // Auxiliar player board for inserting in the vector
        // Initialize the game state
        m_game_state = game_state_e::STARTING;

        // Checks if there are more than 1 arguments on the input line
        if(argc > 0){
            for(int i{1}; i < argc;i++){
                // Checks if the user needs for help
                if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i],"--help") == 0){
                    usage("");
                }
                else{ 
                    // Checks if the user inputs a pesonalized checks amount
                    if( strcmp(argv[i],"-c") == 0 && argc > 1 && isdigit((*argv[i+1] - '0') + 1)){
                        m_opt.total_checks = (short) *argv[i+1];
                    
                    }
                    // Checks if the user inputs a personalized input file
                    if(isFile(argv[i])){
                        m_opt.input_filename = argv[i];
                    }
                }
            }
        }
        // Read the File
        MESSAGE("Opening input file ["+m_opt.input_filename+"]");
        bReader.open(m_opt.input_filename);
        if(!bReader.is_open()){
           MESSAGE("Error on opening file: " + m_opt.input_filename);
        }
        else{
            MESSAGE("Processing Files, please wait");
            while(bReader >> rBoard[pAux]){
                pAux++;
                if(pAux == SB_SIZE*SB_SIZE){
                     pAux = 0;       
                    if(rBoard.is_valid(rBoard.get_board())){                                
                        pbAux.updateBoard(rBoard);      
                        // pbAux.printBoard();  
                        // std::cout << m_total_boards.size() << std::endl;
                        m_total_boards.push_back(rBoard);   
                    }
                }
            }
        MESSAGE("Finished reading input data file");                
        }
    }



    PlayerBoard::PlayerBoard(const PlayerBoard & target){
    }

    PlayerBoard & PlayerBoard::operator=(const PlayerBoard & target){
        return *this;
    }



    void SudokuGame::display_welcome(){
        std::cout << "==================================================\n";
        std::cout << "  Welcome to a temrinal version of Sudoku, v1.0\n  Copyright (C) 2020, Selan R. dos Santos\n";
        std::cout << "==================================================\n";
    }

    void SudokuGame::update(){
    }

    void SudokuGame::render(void){
        switch (m_game_state)
            {
            case game_state_e::READING_MAIN_OPT:
                clear_screen();
                std::cout << "|--------[ MAIN SCREEN ]--------|\n";
                // std::cout << m_total_boards.size() << std::endl;                
                m_total_boards[m_board_position].printBoard();
                std::cout << "MSG : [" << m_curr_msg << "]\n\n";
                std::cout << "1-Play  2-New Game  3-Quit  4-Help\nSelect Option [1,4] > ";
            break;
                
        default:
            break;
        }
        
    }


    bool SudokuGame::game_over(){
        return false;
    }
}
