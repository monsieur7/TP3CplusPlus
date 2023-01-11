#include <iostream>
#include <vector>
#include "Board.h"
#include <ctime>
#include <chrono>

#define SIZE 30
#ifdef _WIN64 
#include <windows.h>
#endif
#ifdef _WIN32 
#include <windows.h>
#endif
// TODO : NUMBERS OF ITERATIONS IN backtracking
int main(void){
    srand(time(nullptr));
    #if defined( _WIN32) || defined(_WIN64)
// enabling buffering and utf8 characters for windows only
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
    Sudoku::Board board(SIZE, 5);
    int compte = 0;
    int &compteref = compte;
    std::cout <<  "sudoku of size " << SIZE << "*" << SIZE << std::endl;
    std::cout << board.checkGridIsGood() << std::endl;
    board.display();
    auto start = std::chrono::high_resolution_clock::now();
    board.fillGrid();
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << board.checkGridIsGood() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() / 1000 << "s" << std::endl;
    board.display();
    board.makeGridEasier();
    board.display();
    start = std::chrono::high_resolution_clock::now();
    board.backtracking(0);
    stop = std::chrono::high_resolution_clock::now();
    auto time_backtrack =  std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    board.display();

    board.display();
    std::cout << "La durée est de : " << time_backtrack.count() << " ms" << std::endl;
    std::cout << "Le nombre d'itérations: " << compteref << std::endl;



}