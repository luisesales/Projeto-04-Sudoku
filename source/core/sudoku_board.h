#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H


#include <fstream>
#include <string>
#include <thread>
#include <memory>
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::fill_n;
using std::all_of;
#include <vector>
using std::vector;
#include <iterator>
using std::back_inserter;
#include <sstream>
using std::ostringstream;
#include <numeric>
using std::accumulate;
#include <dirent.h>

/*!
 *  In this header file we have two classes: SBoard and SudokuPlayerBoard.
 *
 *  The former represents only the board data, as a matrix of short.
 *
 *  The latter represents the board and the actions necessary to support
 *  the player's moves and all the information associated with a
 *  Sudoku match. This involves enconding information regarding incorrect
 *  moves, invalid plays, correct play, original numbers, etc.
 *  These information is required to display the board with special colors
 *  representing all thesse different conditions.
 */

constexpr short SB_SIZE{9};
bool validate(const vector<short>b);

namespace sdkg {

    /// This class stores values for a 9x9 Sudoku board.
    class SBoard {
        private:
            short board[SB_SIZE*SB_SIZE];
        public:
        SBoard();
        SBoard & operator=(SBoard & target);
        short & operator[](size_t pos) {
            return board[pos];
        }

        /// Validator of a vector
        

        /// Validator of a hole board
        bool is_valid(const short b[SB_SIZE*SB_SIZE] );
    };


    /*!
     *  This class represents a Sudoku board as the player's makes his or her moves during a match.
     *  The moves in the board data set is coded as follows:
     *
     *  + Digits in range [1,9]: These are the original values already filled in when the match started.
     *  + 0: An empty location that may receive a value provided by the player.
     *  + prefix `1` as in 1[1,9]: We add this prefix if the player's value is correct, i.e. corresponds
     *    to the correct value stored in the solution elsewhere.
     *  + prefix `2` as in 2[1,9]: We add this prefix if the player's value is incorrect, i.e. it is
     *    a valid play but it differs from the solution.
     *  + prefix `3` as in 3[1,9]: We add this prefix if the player makes an invalid move, i.e. a move
     *    that breaks the Sudoku's basic rules.
     *
     *  Note that the player's moves are always stored, when it is applied to a location that does
     *  not contain an original value.
     *  This is important so we can color the number accordingly when we display the board.
     */
    class PlayerBoard {
        private:
            SBoard m_player_moves; //!< The Sudoku matrix where the user moves are stored.
            SBoard m_solution;     //!< The Sudoku matrix with the solution.

        public:
            /// Possible types associated with a location on the board druring a match.
            enum loc_type_e : short {
                EMPTY = 0,      //!< Empty cell.
                ORIGINAL,       //!< Original puzzle value, not mutable.
                CORRECT,        //!< Correct value.
                INCORRECT,      //!< Incorrect value.
                INVALID         //!< Invalid play.
            };

            /// Prefix we may add to a stored value to encode information.
            enum prefix_e : short {
                PRE_ORIGINAL = 0,
                PRE_CORRECT = 10,   //!< User has entered a correct value.
                PRE_INCORRECT = 20, //!< User has entered an incorrect value.
                PRE_INVALID = 30    //!< User has entered an invalid value.
            };

        public:
            //=== Regular methods.
            PlayerBoard(){/*empty*/}
            PlayerBoard( SBoard &sb );
            ~PlayerBoard(){/*empty*/}
            PlayerBoard & operator=( const PlayerBoard & target);
            PlayerBoard( const PlayerBoard & target);

            //=== Access methods.
            /// Method that returns the board correct solution
            SBoard getSolutionBoard(void) const{return m_solution;}

            ///Method that returns reference to current player board
            SBoard getPlayerBoard(void) const{return m_player_moves;}

            //=== Modifiers methods.
            ///Method that will print current board
            void printBoard(void);

            /// Method that updates player board
            void updateBoard(SBoard &sb);


    };
}
#endif
