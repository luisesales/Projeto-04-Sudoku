#include <cassert>
#include <stdexcept>
#include <iterator>
#include <string.h>

#include "sudoku_gm.h"


namespace sdkg {

    /// Lambda expression that transform the string to lowercase.
    auto STR_LOWERCASE = [](const char * t)->std::string{
        std::string str{ t };
        std::transform( str.begin(), str.end(), str.begin(), ::tolower );
        return str;
    };

    /// Default constructor
    SudokuGame::SudokuGame(){
        m_opt.total_checks = 3; // Default value.
        m_opt.input_filename = "../data/input.txt"; // Default value.
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
        }
        else if ( m_game_state == game_state_e::READING_MAIN_OPT )
        {

        }
        else if ( m_game_state == game_state_e::PLAYING_MODE )
        {

        }
        else if ( m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH )
        {
        }
    }
    
    void SudokuGame::initialize(int argc,char* argv[]){
        m_game_state = game_state_e::STARTING;
        if(argc > 1){
            for(size_t i{1}; i < argc;i++){
                if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i],"--help") == 0){
                    SudokuGame::usage("");
                }
                else{ 
                    if( strcmp(argv[i],"-c") == 0 && argc > 2 && isdigit(argv[i+1])){
                        m_checks_left = argv[i+1];
                    }
                    // if(){}
                }
            }
        }
        // if(argc < 3){
        //     for(size_t i{1}; i < argc;i++){
        //         if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i],"--help") == 0){
        //             std::cout << "Usage: sudoku [<options>] [<input_puzzle_file>] \n   Game Options" << std::endl;
        //             std::cout << "    --ncheck <num> Number of checks per game. Default = 3." << std::endl;
        //             std::cout << "    --help         Print this help text." << std::endl;
        //             return false;
        //         }
        //         if(strcmp)
        //     };
        // }
        // else{
        //     if(strcmp(argv[i],"--ncheck") == 0){
        //             if()
        //         }
        // }
    }

    void SudokuGame::update(){
    }

    void SudokuGame::render(void){
    }

}
