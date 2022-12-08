#include <algorithm>
#include "sudoku_board.h"

namespace sdkg {
    SBoard::SBoard()
    {
        // Empty board.
        std::fill( &board[0], &board[SB_SIZE*SB_SIZE], 0 );
    }

    SBoard& SBoard::operator=(SBoard & target){
        if(is_valid(target.board))
        for(short i{0}; i < SB_SIZE*SB_SIZE;i++) board[i] = target.board[i];
    }

    bool validate(const vector<short>b){
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

    bool is_valid(const short b[SB_SIZE*SB_SIZE] )
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
            if(!validate(t))return false;
            
        }

        // Testando cada coluna.
        for(short col{0}; col<SB_SIZE; col++){
            t.clear();
            for (short row{0}; row<SB_SIZE; row++){
                t.push_back(b[row*SB_SIZE+col]);
            }
            if(!validate(t)) return false;
            
        }

        // Testando cada quadrado
        for(short i{1}; i < 8;i+=3){
            t.clear();
            for(short aRow{-1};aRow <= 1;aRow++){
                for(short aCol{-1};aCol <= 1;aCol++){
                    t.push_back(b[(i+aRow)*SB_SIZE+(i+aCol)]);
                }
            }
            if(!validate(t)) return false;
        }
        return true; 
    }

    ///Ctro
    PlayerBoard::PlayerBoard( SBoard &sb ){
        m_solution = sb;
        m_player_moves = sb;
        for(short i{0}; i < SB_SIZE*SB_SIZE;i++){
            if(sb[i] < 0) m_player_moves[i] = 0;                  
        }
        
    }

    void PlayerBoard::updateBoard( const SBoard &sb){
        PlayerBoard(sb);
    }

    void PlayerBoard::printBoard(){
        char letter = 65;
        std::cout << "   1 2 3   4 5 6   7 8 9\n";  
        for(short row{0}; row < SB_SIZE;row++){  
            if(row%3==0){
                std::cout << " +-------+-------+-------+\n";
            }
            std::cout << letter++; 
            for(short col{0}; col < SB_SIZE;col++){
                if(col%3==0){
                    std::cout << "| ";
                }
                std::cout<< m_player_moves[row*SB_SIZE+col] << " ";
            }
            std::cout << "|\n";
            
        }
        std::cout << " +-------+-------+-------+\n";
    }

}
