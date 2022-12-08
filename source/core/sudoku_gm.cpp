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

    bool isDirectory(char* name) {
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            return true;
        }

        std::string strName = convertToString(name, 256);
        if (strName.find(".") != std::string::npos) {
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

        
        // Initialize the game state
        m_game_state = game_state_e::STARTING;

        // Checks if there are more than 1 arguments on the input line
        if(argc > 1){
            for(size_t i{1}; i < argc;i++){
                // Checks if the user needs for help
                if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i],"--help") == 0){
                    SudokuGame::usage("");
                }
                else{ 
                    // Checks if the user inputs a pesonalized checks amount
                    if( strcmp(argv[i],"-c") == 0 && argc > 2 && isdigit(*argv[i+1])){
                        m_opt.total_checks = (short) *argv[i+1];
                    
                    }
                    // Checks if the user inputs a personalized input file
                     if(isDirectory(argv[i])){
                        m_opt.input_filename = *argv[i];
                     }
                }
            }
        }
        struct dirent* pDirent;
        DIR* pDir;
        // Ensure we can open directory.
        pDir = opendir(m_opt.input_filename.c_str());
        if (pDir == NULL) {
            std::cout << "Cannot open directory " << m_opt.input_filename << "\n";
        }
    }

    void SudokuGame::update(){
    }

    void SudokuGame::render(void){
    }

}
