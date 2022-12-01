#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

using std::vector;

#define EMPTY short(0)
#define SIZE 9

void print( short b[SIZE][SIZE] )
{
    char letter = 65;
    std::cout << "   1 2 3   4 5 6   7 8 9\n";  
    for(short row{0}; row < SIZE;row++){  
        if(row%3==0){
            std::cout << " +-------+-------+-------+\n";
        }
        std::cout << letter++; 
        for(short col{0}; col < SIZE;col++){
            if(col%3==0){
                std::cout << "| ";
            }
            std::cout<< b[row][col] << " ";
        }
        std::cout << "|\n";
        
    }
    std::cout << " +-------+-------+-------+\n";
}

bool validate(const vector<short> b){
    bool numbers[SIZE];
    std::fill(numbers, numbers+SIZE, false);
    for(auto x : b){
        auto n=std::abs(x);
        // Check if we've got a number outside the valid range.
        if(n<1 or n>9) return false;
        numbers[n-1] = true;
    }
    return std::all_of(numbers, numbers+SIZE, [](bool e){return e==true;});
}

bool is_valid( short b[SIZE][SIZE] )
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
}


int main(void)
{
    short board1[SIZE][SIZE]={
        { 1, 3, 4, 6, 7, 8, 5, 9, 2 },
        { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
        { 5, 9, 8, 3, 4, 2, 1, 6, 7 },
        { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
        { 4, 2, 6, 8, 5, 3, 9, 7, 1 },
        { 7, 1, 3, 4, 2, 9, 8, 5, 6 },
        { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
        { 2, 8, 7, 9, 1, 4, 6, 3, 5 },
        { 3, 4, 5, 2, 8, 6, 7, 1, 9 } };

    short board2[SIZE][SIZE]={
        { 1, 6, 2, 8, 5, 7, 4, 9, 3 },
        { 5, 3, 4, 1, 2, 9, 6, 7, 8 },
        { 7, 8, 9, 6, 4, 3, 5, 2, 1 },
        { 4, 7, 5, 3, 1, 2, 9, 8, 6 },
        { 9, 1, 3, 5, 8, 6, 7, 4, 2 },
        { 6, 2, 8, 7, 9, 4, 1, 3, 5 },
        { 3, 5, 6, 4, 7, 8, 2, 1, 9 },
        { 2, 4, 1, 9, 3, 5, 8, 6, 7 },
        { 8, 9, 7, 2, 6, 1, 3, 5, 4 } };

    short board3[SIZE][SIZE]={
        { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
        { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
        { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
        { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
        { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
        { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
        { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
        { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
        { 3, 4, 5, 2, 8, 6, 1, 7, 9 } };


    // Problem
    short board4[SIZE][SIZE]={
        { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
        { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
        { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
        { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
        { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
        { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
        { 7, 3, 9, 2, 4, 1, 8, 5, 6 },
        { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
        { 3, 5, 2, 8, 6, 4, 1, 7, 9 } };

    // Problem
    short board5[SIZE][SIZE]={
        { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
        { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
        { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
        { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
        { 4, 6, 8, 5, 3, 2, 5, 9, 1 },
        { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
        { 7, 3, 9, 2, 4, 1, 8, 5, 6 },
        { 9, 3, 5, 3, 7, 6, 2, 8, 4 },
        { 3, 5, 2, 8, 6, 4, 1, 7, 9 } };

    // Problem
    short board6[SIZE][SIZE]={
        { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
        { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
        { 1, 8, 3, 4, 2, 19, 5, 6, 7 },
        { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
        { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
        { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
        { 7, -3, 9, 2, 4, 1, 8, 5, 6 },
        { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
        { 3, 5, 2, 8, 6, 4, 1, 7, 9 } };

    // Problem
    short board7[SIZE][SIZE]={
        { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
        { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
        { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
        { 8, 9, 7, 6, 1, 5, 4, 2, 3 },
        { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
        { 5, 4, 6, 7, 8, 3, 9, 1, 2 },
        { 7, 3, 9, 2, 4, 1, 0, 5, 6 },
        { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
        { 3, 5, 2, 8, 6, 4, 1, 7, 9 } };

    // Problem
    short board8[SIZE][SIZE]={
        { 6, 2, 1, 9, 5, 7, 3, 4, 8 },
        { 2, 7, 4, 1, 9, 8, 6, 3, 5 },
        { 1, 8, 3, 4, 2, 9, 5, 6, 7 },
        { 8, 9, 7, 3, 1, 5, 4, 2, 3 },
        { 4, 6, 8, 5, 3, 2, 7, 9, 1 },
        { 5, 4, 6, 7, 8, 6, 9, 1, 2 },
        { 7, 3, 9, 2, 4, 1, 8, 5, 6 },
        { 9, 1, 5, 3, 7, 6, 2, 8, 4 },
        { 3, 5, 2, 8, 6, 4, 1, 7, 9 } };

    std::cout << "Board: \n";
    print( board1 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board1 ) << std::endl;
    std::cout << "\n";

    std::cout << "Board: \n";
    print( board2 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board2 ) << std::endl;
    std::cout << "\n";


    std::cout << "Board: \n";
    print( board3 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board3 ) << std::endl;
    std::cout << "\n";


    std::cout << "Board: \n";
    print( board4 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board4 ) << std::endl;
    std::cout << "\n";


    std::cout << "Board: \n";
    print( board5 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board5 ) << std::endl;
    std::cout << "\n";


    std::cout << "Board: \n";
    print( board6 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board6 ) << std::endl;
    std::cout << "\n";


    std::cout << "Board: \n";
    print( board7 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board7 ) << std::endl;
    std::cout << "\n";


    std::cout << "Board: \n";
    print( board8 );
    std::cout << "Is valid? " << std::boolalpha << is_valid( board8 ) << std::endl;
    std::cout << "\n";

    /* TODO: Make the code below work, instead of the ugly code above.

    int n_boards{8}; // Number of boards...
    for ( int i{0}; i < n_boards ; ++i )
    {
        std::cout << "Board #" << (i+1) << ": \n";
        print( boards[i] );
        std::cout << "Is valid? " << std::boolalpha << is_valid( board[i] ) << std::endl;
        std::cout << "\n";
    }

    */

    return 0;
}

