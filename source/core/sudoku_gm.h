#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

/*!
 *  SUdoku game class header.
 */

#include <fstream>
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

#include "../lib/messages.h"
#include "../lib/text_color.h"
#include "sudoku_board.h"

namespace sdkg {

    /// Game class representing a Life Game simulation manager.
    class SudokuGame
    {
        private:
            //=== Structs

            //!< Possible game states.
            enum class game_state_e : uint {
                STARTING=0,             //!< Beginning the game.
                //====================================================
                READING_MAIN_OPT,       //!< Reading main menu option.
                //----------------------------------------------------
                HELPING,                //!< Displaying game rules (main menu)
                QUITTING,               //!< Game is quiting either because user requested (main menu).
                //====================================================
                PLAYING_MODE,           //!< Reading user command (Play sub-menu).
                //----------------------------------------------------
                REQUESTING_NEW_GAME,    //!< User wants to start a new game.
                CONFIRMING_QUITTING_MATCH,    //!< User has already started a match. We need to confimr s/he wants to bail out.
                VALIDATING_PLAY,        //!< User wants to place a number on the board.
                REMOVING_PLAY,          //!< User wants to remove a number from the board.
                CHECKING_MOVES,         //!< User wants to check whether his previous moves are correct.
                UNDOING_PLAY,           //!< User wants to undo a previous move he did.
                // ====================================================
                FINISHED_PUZZLE         //!< User has completed a puzzle. 
            };


            /// Internal game options
            struct Options {
                std::string input_filename; //!< Input cfg file.
                short total_checks;        //!< # of checks user has left.
            };

            /// Options from the main menu.
            enum class main_menu_opt_e : uint {
                PLAY=0,        //!< Play option.
                NEW_GAME,      //!< New puzzle option.
                QUIT,          //!< Quit option.
                HELP,          //!< Print help option.
                N_OPTIONS,     //!< Total number of options.
                INVALID        //!< Invalid option.
            };

            /// Represents a user move.
            struct Play {
                short row;    //!< row selected by the user.
                short col;    //!< col selected by the user.
                short value;  //!< value to play selected by the user.
                /// Constructor.
                Play( short r=-1, short c=-1, short v=1 ) : row{r}, col{c}, value{v}{/*empty*/}
            };

            /// Represents a command issued during a match (UNDO command).
            struct Command {
                enum class type_e : uint {
                    PLACE=0, //!< Place command.
                    REMOVE   //!< Remove command.
                } action ;
                Play data; //!< Play data.

                Command( type_e a, Play p ) : action{a}, data{p}
                { /* empty */ }
            };


            //=== Data members

            Options m_opt;                          //!< Overall game Options to set up the game configuration.
            game_state_e m_game_state;              //!< Current game state.
            std::string m_curr_msg;                 //!< Current message to display on screen.
            Play m_curr_play;                       //!< Current user play.
            bool m_quitting_match;                  //!< Flag that indicates whether the user wants to end an ongoing game.
            short m_checks_left;                    //!< Current # of checks user can request.
            main_menu_opt_e m_curr_main_menu_opt;   //!< Current main menu option.
            std::vector< Command > undo_log;        //!< Log of commands to support undoing.

        public:
            SudokuGame();
            ~SudokuGame();

            void usage(std::string)const;
            void update();
            void process_events();
            void render();

    }; // SudokuGame class.
}
#endif
