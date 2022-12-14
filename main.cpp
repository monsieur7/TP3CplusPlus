#include <iostream>
#include <vector>
#include "Board.h"

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
    std::cout << board.checkGridIsGood() << std::endl;
    board.display();
    board.fillGrid();
    board.display();
    board.checkGridIsGood();
}