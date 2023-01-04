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
    srand(time(nullptr));
    #if defined( _WIN32) || defined(_WIN64)
// enabling buffering and utf8 characters for windows only
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
    Sudoku::Board board(9, 2);
    clock_t duration;
    int compte = 0;
    int &compteref = compte;    

    std::cout << board.checkGridIsGood() << std::endl;
    board.display();
    board.fillGrid();
    std::cout << board.checkGridIsGood() << std::endl;
    board.display();
    board.makeGridEasier();
    board.display();
    duration = clock();
    board.backtracking(0, compteref);
    duration = clock() - duration;

    board.display();
    std::cout << "La durée est de : " << duration/CLOCKS_PER_SEC << " secondes" << std::endl;
    std::cout << "Le nombre d'itérations: " << compteref << std::endl;



}