#include <iostream>
#include <vector>
#include "Board.h"
#include <ctime>
#include <chrono>
#define SIZE 9
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
    auto start = std::chrono::high_resolution_clock::now();
    board.fillGrid();
    auto stop = std::chrono::high_resolution_clock::now();
    auto time =  std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "La durée est de : " << (float)time.count() << " ms" << std::endl;
    board.display();
    std::cout << board.checkGridIsGood() << std::endl;
    board.makeGridEasier();
    board.display();
    start = std::chrono::high_resolution_clock::now();

    board.backtracking(0, compteref);
    stop = std::chrono::high_resolution_clock::now();
    auto time_solve = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    board.display();

    std::cout << "La durée est de : " << time_solve.count() << " microseconds" << std::endl;
    std::cout << "Le nombre d'itérations: " << compteref << std::endl;



}