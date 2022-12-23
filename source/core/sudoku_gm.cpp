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
            std::string line;
            std::getline(std::cin, line); 
            aux = line[0] - '0';
            if(aux > 4 || aux < 1 || line.size() != 1) m_curr_main_menu_opt = main_menu_opt_e::INVALID;
            else{
                aux--;
                m_curr_main_menu_opt = main_menu_opt_e(aux);
            } 
            

        }
        else if ( m_game_state == game_state_e::PLAYING_MODE ||
                  m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH)
        {
            // Reading Command Chosen   
            m_command_line.clear();         
            std::getline(std::cin, m_command_line); 
        }
        else if( m_game_state == game_state_e::UNDOING_PLAY){
            m_game_state = game_state_e::PLAYING_MODE;
        }
    }

    void SudokuGame::update(){
        if ( m_game_state == game_state_e::STARTING or
             m_game_state == game_state_e::HELPING  or
             m_game_state == game_state_e::FINISHED_PUZZLE )
        {
            m_game_state = game_state_e::READING_MAIN_OPT;
            m_curr_msg.clear();
        }
        else if(m_game_state == game_state_e::READING_MAIN_OPT){
            // Updating Current Message to Default Value
            m_curr_msg.clear();

            // Updating Program Based on Main Menu Option Chosen
            switch (m_curr_main_menu_opt)
            {
            // Option Chosen = Play
            case main_menu_opt_e::PLAY:  
                          
                m_game_state = game_state_e::PLAYING_MODE;
                update_avaliable();
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

            // Reseting the board he left for future plays
            m_total_boards[m_board_position].resetBoard();

            // Change the board to a new board
            m_board_position = (m_board_position+1)%m_total_boards.size();    

            // Resets the amount of checks for a new game
            m_checks_left = m_opt.total_checks;        

            // Resets the controller for checking if theres progress
            m_progress = false;

            // Reseting the undo_log for future plays
            undo_log.clear();
        }

        else if(m_game_state == game_state_e::PLAYING_MODE){
            // Restarting message for the next comand
            m_curr_msg.clear();            

            // Checks if Line has command
            if(m_command_line != ""){
                
                auto comands = split(m_command_line,' ');
                size_t size{comands.size()}; // Var for checking if any of known commands were put inside the command line
                char digit1; // Var for the checking the validation of the first other character on the command
                short digit2; // Var for the checking the validation of the second other character on the command
                short value; // Var for saving the value aplied from the command line
                short board_pos; // Var for mapping the board position which is going to change 
                auto solution_board = m_total_boards[m_board_position].getSolutionBoard();  // Var for comparing with solution    
                auto player_board = m_total_boards[m_board_position].getPlayerBoard(); // Var for getting values from current board
                short aux; // Var for using on number methods
                


                // Determines that user tried a command
                m_progress = true;
                if(size >= 3){
                    digit1 = std::toupper(comands[1][0]);
                    digit2 = (comands[2][0] - '0') - 1;
                    aux = digit1 - 'A';
                    board_pos = aux*SB_SIZE + digit2;
                }

                // Checks if a valid place command was written
                if(
                        comands[0][0] == 'p' &&
                        size == 4)
                {
                    value =  comands[3][0] - '0';
                    if(
                        digit1 >= 65 && 
                        digit1 <= 74 &&
                        digit2 >= 1 &&
                        digit2 <= 9 &&
                        value >= 1 &&
                        value <= 9 && 
                        solution_board[board_pos] < 0 )
                    {                    
                        
                        // Checks if value is correct
                        if(value == std::abs(solution_board[board_pos])){
                            // Applies the correct prefix and updates board
                            value += 10;
                            m_total_boards[m_board_position].updateBoardPotition( board_pos, value);
                        }

                        // Checks if value is valid
                        else{
                            // Applies the incorrect prefix and updates board
                            value += 20;
                            m_total_boards[m_board_position].updateBoardPotition( board_pos, value);
                        }

                        // Adds to the log
                        value = value % 10; // Updates value for the log
                        // digit2++; // Updates digit2 for the log
                        m_curr_play = Play(aux, digit2, value); // Updates Current Play
                        Command cAux(Command::type_e::PLACE,m_curr_play); // Var for adding to the undo_log
                        undo_log.push_back(cAux); // Adds to the vector
                        update_avaliable();

                        if(std::all_of(m_avaliable.begin(), m_avaliable.end(), [](bool e){return e==false;})){
                            m_game_state = game_state_e::FINISHED_PUZZLE;
                            m_curr_msg = "Congratulations! you finished the puzzle! Press enter to continue";
                        }
                        
                    }
                    else{
                        m_curr_msg = "Please Insert a Valid Place Command";
                    }
                }

                else if(comands[0][0] == 'r'){ 
                    
                    if(
                    digit1 >= 65 && 
                    digit1 <= 74 &&
                    digit2 >= 1 &&
                    digit2 <= 9 &&
                    solution_board[board_pos] < 0 &&
                    size == 3)
                    {
                        // Resets the board position to default value
                        value = 0;
                        m_total_boards[m_board_position].updateBoardPotition( board_pos, value);

                        // Adds to the log
                        value = player_board[board_pos] % 10; // Updates value for the log
                        // digit2++; // Updates digit2 for the log
                        m_curr_play = Play(aux, digit2, value); // Updates Current Play
                        Command cAux(Command::type_e::REMOVE,m_curr_play); // Var for adding to the undo_log
                        undo_log.push_back(cAux); // Adds to the vector
                        update_avaliable();
                    }
                    else{
                        m_curr_msg = "Please Insert a Valid Remove Command";
                    }
                }
                else if(comands[0][0] == 'u' &&
                        size == 1)
                {
                    m_command_line.clear();    
                    if(!undo_log.empty()){                
                        Command undo = undo_log.back();                    
                        char param1 = undo.data.row + 'A';
                        char param2 = undo.data.col + '1';
                        char param3 = undo.data.value + '0';  
                        
                        if(undo.action == Command::type_e::PLACE){                        
                            std::cout << "action place" << "\nrow " << param1 << "\ncol " << param2 << "\nvalue " << param3;                   
                            m_command_line = "r ";
                            m_command_line+= param1;
                            m_command_line+= " ";
                            m_command_line+= param2; 
                        }
                        else if(undo.action == Command::type_e::REMOVE){
                            std::cout << "action remove" << "\nrow " << param1 << "\ncol " << param2 << "\nvalue " << param3;                   
                            m_command_line = "p ";
                            m_command_line+= param1;
                            m_command_line+= " ";
                            m_command_line+= param2;
                            m_command_line+= " ";
                            m_command_line+= param3; 
                            
                        }
                        std::cout << "\n\n" << m_command_line << "\n\n";
                        m_game_state = game_state_e::UNDOING_PLAY;
                    }
                    else m_curr_msg = "There's No Valid Command to Undo";
                }

                else if(comands[0][0] == 'c' &&
                        size == 1 &&
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
                else if(m_command_line[0] == 'n' || m_command_line[0] == 'N') m_game_state = game_state_e::READING_MAIN_OPT;
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
            m_total_boards[m_board_position].printBoard(false,0);
            std::cout << Color::tcolor("  MSG : [ " + m_curr_msg + " ]\n\n",Color::BRIGHT_YELLOW);
            
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
                
                short aux = (m_curr_play.row*10)+m_curr_play.col;
                m_total_boards[m_board_position].printBoard(m_checking_board,aux);
                
                // Printing Current Game Info
                std::cout << Color::tcolor("  Checks Left: [ " + checks + " ]\n",Color::BRIGHT_YELLOW);
                std::cout << Color::tcolor("  Digits Left: [ ",Color::BRIGHT_YELLOW);
                for(size_t i{0}; i < m_avaliable.size();i++){
                    string number = std::to_string(i+1);
                    if(m_avaliable[i] == true) std::cout << Color::tcolor(number + " ",Color::BRIGHT_YELLOW);
                    else std::cout << " ";
                }
                std::cout << Color::tcolor("]\n",Color::BRIGHT_YELLOW);
                std::cout << Color::tcolor("  MSG : [ " + m_curr_msg + " ]\n\n",Color::BRIGHT_YELLOW);     
                
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

    void SudokuGame::update_avaliable(){
        auto solution_board = m_total_boards[m_board_position].getSolutionBoard();
        auto player_board = m_total_boards[m_board_position].getPlayerBoard();
        m_avaliable = {false,false,false,false,false,false,false,false,false};
        short aux;
        for(short i{0}; i < SB_SIZE*SB_SIZE;i++){
            aux = std::abs(solution_board[i]);
            if(solution_board[i] < 0 && (player_board[i]%10) != aux){
                m_avaliable[aux-1] = true;
            }
        }
    }

    /// Splits the input string based on `delimiter` into a list of substrings.
    std::vector<std::string> SudokuGame::split(const std::string & input_str, char delimiter){
        // Store the tokens.
        std::vector<std::string> tokens;
        // read tokens from a string buffer.
        std::istringstream iss;
        iss.str(input_str);
        // This will hold a single token temporarily.
        std::string token;
        while (std::getline(iss >> std::ws, token, delimiter))
            tokens.emplace_back(token);
        return tokens;
    }

}
