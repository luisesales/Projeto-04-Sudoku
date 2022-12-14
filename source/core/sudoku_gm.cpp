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

    
    
    void SudokuGame::initialize(int argc,char* argv[]){        
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
                    if( strcmp(argv[i],"-c") == 0 && argc > 1 && isdigit((*argv[i+1]) + 1)){                        
                        m_opt.total_checks = *argv[i+1] - '0';                    
                    }
                    // Checks if the user inputs a personalized input file
                    if(isFile(argv[i])){
                        m_opt.input_filename = argv[i];
                    }
                }
            }
        }
        m_checks_left = m_opt.total_checks;

        // Read the File
        MESSAGE("Opening input file ["+m_opt.input_filename+"]");
        bReader.open(m_opt.input_filename);
        if(!bReader.is_open()){
           MESSAGE("Error on opening file: " + m_opt.input_filename);
           exit(1);
        }
        else{
            MESSAGE("Processing Files, please wait");
            while(bReader >> rBoard[pAux]){
                pAux++;
                if(pAux == SB_SIZE*SB_SIZE){
                     pAux = 0;       
                    if(rBoard.is_valid(rBoard.get_board())){                                                                                                              
                        pbAux.updateBoard(rBoard);                        
                        m_total_boards.push_back(pbAux);                          
                    }
                }
            }
        MESSAGE("Finished reading input data file");            
        }
    }

    


    void SudokuGame::display_welcome(){
        std::cout << "==================================================\n";
        std::cout << "  Welcome to a terminal version of Sudoku, v1.0\n  Copyright (C) 2020, Selan R. dos Santos\n";
        std::cout << "==================================================\n";
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
            // Reading Option Chosen
            uint aux;
            std::cin >> aux;
            std::string line;
            std::getline(std::cin, line); 
            if(aux > 4 || aux < 1) m_curr_main_menu_opt = main_menu_opt_e::INVALID;
            else{
                aux--;
                m_curr_main_menu_opt = main_menu_opt_e(aux);
            } 
            

        }
        else if ( m_game_state == game_state_e::PLAYING_MODE ||
                  m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH)
        {
            // Reading Command Chosen            
            std::getline(std::cin, m_command_line); 
        }
        else if(m_game_state == game_state_e::REQUESTING_NEW_GAME){
            
        }
    }

    void SudokuGame::update(){
        if ( m_game_state == game_state_e::STARTING or
             m_game_state == game_state_e::HELPING  or
             m_game_state == game_state_e::FINISHED_PUZZLE )
        {
            m_game_state = game_state_e::READING_MAIN_OPT;
        }
        else if(m_game_state == game_state_e::READING_MAIN_OPT){
            // Updating Current Message to Default Value
            m_curr_msg = "";

            // Updating Program Based on Main Menu Option Chosen
            switch (m_curr_main_menu_opt)
            {
            // Option Chosen = Play
            case main_menu_opt_e::PLAY:  
                          
                m_game_state = game_state_e::PLAYING_MODE;
                break;
            
            // Option Chosen = New Game
            case main_menu_opt_e::NEW_GAME:
                if(m_progress){ 
                    m_game_state = game_state_e::CONFIRMING_QUITTING_MATCH;
                    m_curr_msg = "Are you sure you want to leave this game?";
                }
                else m_game_state = game_state_e::REQUESTING_NEW_GAME;                
                break;
            
            // Option Chosen = Quit
            case main_menu_opt_e::QUIT:            
                m_game_state = game_state_e::QUITTING;
                break;
            
            // Option Chosen = Help
            case main_menu_opt_e::HELP:                
                m_game_state = game_state_e::HELPING;
                break;
            
            // Option Chosen = Invalid
            case main_menu_opt_e::INVALID:
                m_curr_msg = "Please insert a Valid value from [1,4]";
                break;

            default:
                break;
            }
        }
        else if(m_game_state == game_state_e::REQUESTING_NEW_GAME){
            // Selecting a New Board from Read File
            m_game_state = game_state_e::READING_MAIN_OPT;
            m_total_boards[m_board_position].resetBoard();
            m_board_position = (m_board_position+1)%m_total_boards.size();    
            m_checks_left = m_opt.total_checks;        
            m_progress = false;
        }

        else if(m_game_state == game_state_e::PLAYING_MODE){
            // Restarting message for the next comand
            m_curr_msg.clear();

            // Checks if Line has command
            if(m_command_line != ""){
                size_t pos{m_command_line.find("p")}; // Var for checking if any of known commands were put inside the command line
                char digit1; // Var for the checking the validation of the first other character on the command
                short digit2; // Var for the checking the validation of the second other character on the command
                short value; // Var for saving the value aplied from the command line
                short board_pos; // Var for mapping the board position which is going to change 
                auto solution = m_total_boards[m_board_position].getSolutionBoard();  // Var for comparing with solution    
                
                // Determines that user tried a command
                m_progress = true;

                // Checks if a valid place command was written
                if(pos != string::npos){
                    digit1 = std::toupper(m_command_line[pos+2]);
                    digit2 = (m_command_line[pos+4] - '0') - 1;
                    value = m_command_line[pos+6] - '0';
                    board_pos = (digit1 - 'A')*SB_SIZE + digit2;
                   if(
                    digit1 >= 65 && 
                    digit1 <= 74 &&
                    digit2 >= 1 &&
                    digit2 <= 9 &&
                    value >= 1 &&
                    value <= 9 && 
                    solution[board_pos] < 0)
                    {                    
                        // Checks if value is correct
                        if(value == std::abs(solution[board_pos])){
                            value+=10;
                            m_total_boards[m_board_position].updateBoardPotition( board_pos, value);
                        }

                        // Checks if value is valid
                        else{
                            value+=20;
                            m_total_boards[m_board_position].updateBoardPotition( board_pos, value);
                        }
                    }
                    else{
                        m_curr_msg = "Please Insert a Valid Place Command";
                    }
                }
                else if(m_command_line.find("r") != string::npos){ 
                    pos = m_command_line.find("r");
                    digit1 = std::toupper(m_command_line[pos+2]);
                    digit2 = (m_command_line[pos+4] - '0') - 1;
                    board_pos = (digit1 - 'A')*SB_SIZE + digit2;
                    if(
                    pos != string::npos &&
                    digit1 >= 65 && 
                    digit1 <= 74 &&
                    digit2 >= 1 &&
                    digit2 <= 9 &&
                    solution[board_pos] < 0)
                    {
                        value = 0;
                        m_total_boards[m_board_position].updateBoardPotition( board_pos, value);
                    }
                    else{
                        m_curr_msg = "Please Insert a Valid Remove Command";
                    }
                }
                else if(m_command_line.find("u") != string::npos &&
                        m_command_line.size() == 1)
                {

                }

                else if(m_command_line.find("c") != string::npos &&
                        m_command_line.size() == 1 &&
                        m_checks_left > 0)
                {
                    m_game_state = game_state_e::CHECKING_MOVES;
                    m_checking_board = true;
                }
                else{
                    m_curr_msg = "Please Insert a Valid Command";
                }                
            }
            else{
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
        }
        else if(m_game_state == game_state_e::CHECKING_MOVES)
        { 
            m_checking_board = false;
            m_checks_left--;
            m_game_state = game_state_e::PLAYING_MODE;
        }
        else if(m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH){
            if(m_command_line.size() == 1){ 
                if(m_command_line[0] == 'y' || m_command_line[0] == 'Y'){m_game_state = game_state_e::REQUESTING_NEW_GAME;}
                else m_game_state = game_state_e::READING_MAIN_OPT;
                m_curr_msg.clear();
            }
            else{
                m_curr_msg = "Please Insert a Valid Command";
            }
        }
    }

    void SudokuGame::render(void){
        if(m_game_state == game_state_e::READING_MAIN_OPT ||            
           m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH ||
           m_game_state == game_state_e::FINISHED_PUZZLE)
        {
            // Printing Main Menu
            clear_screen();                        
            std::cout << Color::tcolor("|--------[ MAIN SCREEN ]--------|\n",Color::BRIGHT_BLUE);                          
            m_total_boards[m_board_position].printBoard(false);
            std::cout << Color::tcolor("  MSG : [" + m_curr_msg + "]\n\n",Color::BRIGHT_YELLOW);
            
        }
        if(m_game_state == game_state_e::READING_MAIN_OPT ||
           m_game_state == game_state_e::FINISHED_PUZZLE){
            std::cout << "  1-Play  2-New Game  3-Quit  4-Help\n  Select Option [1,4] > ";
        }
        if(m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH){
            std::cout << "  Your Choice [y/n] > ";
        }
        else if(m_game_state == game_state_e::HELPING){
                // Printing Main Menu Tutorial
                clear_screen();
                std::cout << Color::tcolor("-------------------------------------------------------------------------------\n",Color::GREEN);
                std::cout << Color::tcolor("  The goal of Sudoku is to fill a 9x9 grid with numbers so that each row,\n  column nad section (nonet) contain all of the digits between 1 and 9.\n\n",Color::GREEN);
                std::cout << Color::tcolor("  The Sudoku rules are:\n  1. Each row, column and nonet can contain each number (typically 1 to 9)\n     exactly once.\n",Color::GREEN);
                std::cout << Color::tcolor("  2. The sum of all numbers in any nonet, row, or column must be equal to 45.\n",Color::GREEN);
                std::cout << Color::tcolor("-------------------------------------------------------------------------------\n",Color::GREEN);
        }


        else if(m_game_state == game_state_e::PLAYING_MODE  || 
                m_game_state == game_state_e::FINISHED_PUZZLE ||
                m_game_state == game_state_e::CHECKING_MOVES)
            {
                // Printing Action Mode Board
                std::string checks = std::to_string(m_checks_left);
                clear_screen();
                std::cout << Color::tcolor("|--------[ ACTION MODE ]--------|\n",Color::BRIGHT_BLUE);
                m_total_boards[m_board_position].printBoard(m_checking_board);
                
                // Printing Current Game Info
                std::cout << Color::tcolor("  Checks Left: [" + checks + "]\n",Color::BRIGHT_YELLOW);
                std::cout << Color::tcolor("  MSG : [" + m_curr_msg + "]\n\n",Color::BRIGHT_YELLOW);     
                
            }
        if(m_game_state == game_state_e::PLAYING_MODE){
                // Printing Command Syntax
                std::cout << Color::tcolor("Comands Syntax:\n  'enter' (without typping anything)  -> go back to previous menu.\n",Color::GREEN);
                std::cout << Color::tcolor("  'p' <row> <col> <number> + 'enter'  -> place <number> on board at the location (<row>, <col>).\n",Color::GREEN);
                std::cout << Color::tcolor("  'r' <row> <col> + 'enter'           -> remove on board at the location (<row>, <col>).\n",Color::GREEN);
                std::cout << Color::tcolor("  'c' + 'enter'                       -> check which moves made are correct.\n",Color::GREEN);
                std::cout << Color::tcolor("  'u' + 'enter'                       -> undo last play.\n",Color::GREEN);
                std::cout << Color::tcolor("  <col>, <number> must be in range [1,9].\n",Color::GREEN);
                std::cout << Color::tcolor("  <rol> must be a lowercase or uppercase letter in range [A,I].\n\n",Color::GREEN);

                // Printing Command Input Line
                std::cout << Color::tcolor("Enter Command > ",Color::BRIGHT_YELLOW);
        }

        
    }

    bool SudokuGame::game_over(){
        return m_game_state == game_state_e::QUITTING;
    }

}
