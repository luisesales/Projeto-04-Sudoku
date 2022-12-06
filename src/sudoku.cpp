#include "sudoku.h"

namespace sudoku {

    bool boardController::validate(const vector<short> b){
        bool numbers[SIZE];
        std::fill(numbers, numbers+SIZE, false);
        for(auto x : b){
            auto n=std::abs(x);
            // Check if we've got a number outside the valid range.
            if(n<1 or n>9) return false;
            numbers[n-1] = true;
        }
        return std::all_of(numbers, numbers+SIZE, [](bool e){return e==true;});
    };

    bool boardController::is_valid( vector<vector<short>> b )
    {
        vector<short> t;
        bool numbers[SIZE];
        std::fill(numbers, numbers+SIZE, false);

        // Testando cada linha.
        for(short row{0}; row<SIZE; row++){
            t.clear();
            for (short col{0}; col<SIZE; col++){
                t.push_back(b[row][col]);
            }
            if(!validate(t)) return false;
            
        }

        // Testando cada coluna.
        for(short col{0}; col<SIZE; col++){
            t.clear();
            for (short row{0}; row<SIZE; row++){
                t.push_back(b[row][col]);
            }
            if(!validate(t)) return false;
            
        }

        // Testando cada quadrado
        for(short i{1}; i < 8;i+=3){
            t.clear();
            for(short aRow{-1};aRow <= 1;aRow++){
                for(short aCol{-1};aCol <= 1;aCol++){
                    t.push_back(b[i+aRow][i+aCol]);
                }
            }
            if(!validate(t)) return false;
        }
        return true; 
    };
    bool isDirectory(char* name) {
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
        return true;
    }

    std::string strName = convertToString(name, 256);
    if (strName.find(".") != std::string::npos) {
        return false;
  }

  return true;

    bool gameConfig::ReadConfig(int argc, char* argv[]){
        if(argc < 3){
            for(size_t i{1}; i < argc;i++){
                if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i],"--help") == 0){
                    std::cout << "Usage: sudoku [<options>] [<input_puzzle_file>] \n   Game Options" << std::endl;
                    std::cout << "    --ncheck <num> Number of checks per game. Default = 3." << std::endl;
                    std::cout << "    --help         Print this help text." << std::endl;
                    return false;
                }
                if(strcmp)
            };
        }
        else{
            if(strcmp(argv[i],"--ncheck") == 0){
                    if()
                }
        }
    };
}