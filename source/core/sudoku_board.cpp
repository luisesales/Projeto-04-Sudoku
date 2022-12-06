#include <algorithm>
#include "sudoku_board.h"

namespace sdkg {
    SBoard::SBoard()
    {
        // Empty board.
        std::fill( &board[0], &board[SB_SIZE*SB_SIZE], 0 );
    }

    SBoard& SBoard::operator=(const SBoard & target){
        std::copy(&target,&target+SB_SIZE*SB_SIZE,&board);
    }

}
