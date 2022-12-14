#include <algorithm>
#include "sudoku_board.h"

namespace sdkg {
    SBoard::SBoard()
    {
        // Empty board.
        std::fill( &board[0], &board[SB_SIZE*SB_SIZE], 0 );
    }

    SBoard& SBoard::operator=(SBoard & target){        
        for(short i{0}; i < SB_SIZE*SB_SIZE;i++) board[i] = target.board[i];
        return *this;
    }

    bool SBoard::validate(const vector<short>b){
             bool numbers[SB_SIZE];
            std::fill(numbers, numbers+SB_SIZE, false);
            for(auto x : b){
                auto n=std::abs(x);
                // Check if we've got a number outside the valid range.
                if(n<1 or n>9) return false;
                numbers[n-1] = true;
            }
            return std::all_of(numbers, numbers+SB_SIZE, [](bool e){return e==true;});
    }

    bool SBoard::is_valid(const short b[SB_SIZE*SB_SIZE])
    {
        vector<short> t;
        bool numbers[SB_SIZE];
        std::fill(numbers, numbers+SB_SIZE, false);

        // Testando cada linha.
        for(short row{0}; row<SB_SIZE; row++){
            t.clear();
            for (short col{0}; col<SB_SIZE; col++){
                t.push_back(b[row*SB_SIZE+col]);
            }
            if(!SBoard::validate(t))return false;
            
        }

        // Testando cada coluna.
        for(short col{0}; col<SB_SIZE; col++){
            t.clear();
            for (short row{0}; row<SB_SIZE; row++){
                t.push_back(b[row*SB_SIZE+col]);
            }
            if(!SBoard::validate(t)) return false;
            
        }

        // Testando cada quadrado
        for(short i{1}; i < 8;i+=3){
            t.clear();
            for(short aRow{-1};aRow <= 1;aRow++){
                for(short aCol{-1};aCol <= 1;aCol++){
                    t.push_back(b[(i+aRow)*SB_SIZE+(i+aCol)]);
                }
            }
            if(!SBoard::validate(t)) return false;
        }
        return true; 
    }

    PlayerBoard::PlayerBoard(const PlayerBoard & target){
        SBoard aux = target.getSolutionBoard();
        this->updateBoard(aux);
    }

    PlayerBoard & PlayerBoard::operator=(const PlayerBoard & target){     
        SBoard aux = target.getSolutionBoard();
        this->updateBoard(aux);   
        return *this;
    }

    ///Ctro
    PlayerBoard::PlayerBoard(SBoard &sb ){
       for(short i{0}; i < SB_SIZE*SB_SIZE;i++){
            m_solution[i] = sb[i];
            if(sb[i] < 0) m_player_moves[i] = 0;  
            else m_player_moves[i] = sb[i];                
        }
    }

    void PlayerBoard::updateBoard(SBoard &sb){
        for(short i{0}; i < SB_SIZE*SB_SIZE;i++){
            m_solution[i] = sb[i];
            if(sb[i] < 0) m_player_moves[i] = 0;  
            else m_player_moves[i] = sb[i];                
        }
    }

    void PlayerBoard::printBoard(bool checking){
        char letter = 65;
        string sLetter; 
        std::cout << Color::tcolor("      1 2 3   4 5 6   7 8 9\n",Color::BRIGHT_BLUE);  
        for(short row{0}; row < SB_SIZE;row++){  
            if(row%3==0){
                std::cout << "    +-------+-------+-------+\n";
            }
            sLetter = letter;
            std::cout << Color::tcolor("   " + sLetter + "",Color::BRIGHT_BLUE); 
            letter+=1;
            for(short col{0}; col < SB_SIZE;col++){
                if(col%3==0){
                    std::cout << "| ";
                }
                if(m_player_moves[row*SB_SIZE+col] != 0){ 
                    short aux = m_player_moves[row*SB_SIZE+col]/10;
                    std::string number = std::to_string(m_player_moves[row*SB_SIZE+col]%10);
                    if(checking){                        
                        if(aux == 1) std::cout << Color::tcolor(number+" ",Color::BRIGHT_GREEN);
                        else if(aux == 2) std::cout << Color::tcolor(number+" ",Color::BRIGHT_RED);
                        else if(aux == 3) std::cout << Color::tcolor(number+" ",Color::BRIGHT_YELLOW);
                        else std::cout << number << " ";
                    }
                    else if(m_solution[row*SB_SIZE+col] > 0) std::cout << number << " ";
                    else std::cout << Color::tcolor(number+" ",Color::BRIGHT_BLUE);
                    }
                else std::cout << "  "; 
            }
            std::cout << "|\n";
            
        }
        std::cout << "    +-------+-------+-------+\n";
    }

    void PlayerBoard::updateBoardPotition(short & pos, short & value){
        m_player_moves[pos] = value;
    }

    void PlayerBoard::resetBoard(){
        for(short i{0}; i < SB_SIZE*SB_SIZE;i++){
            if(m_solution[i] < 0) m_player_moves[i] = 0;            
        }
    }
}
