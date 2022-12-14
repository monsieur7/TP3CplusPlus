#include <iostream>
#include <vector>
#include "Board.h"
#include <ctime>


#ifdef _WIN64 
#include <windows.h>
#endif
#ifdef _WIN32 
#include <windows.h>
#endif

int main(void){
    #if defined( _WIN32) || defined(_WIN64)
// enabling buffering and utf8 characters for windows only
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
    Sudoku::Board board(9, 1);
    clock_t duration;

    std::cout << board.checkGridIsGood() << std::endl;
    board.display();
    //board.fillGrid();

    duration = std::clock();
    if(board.backtracking(0) == true){
        std::cout << "Sudoku résolu" << std::endl;
    }
    else{
        std::cout << "Sudoku non résolu" << std::endl;

    }
    duration = std::clock() - duration;
    std::cout << "Durée de la fonction récursive: " << (float)duration/CLOCKS_PER_SEC << " secondes." << std::endl;
    


    board.display();
}