#include <vector>
#include <algorithm>
#include <iostream>

#pragma once
namespace Sudoku {
class Board {
    private:
        std::vector<int> _board;
        int _size;
        int _difficulty;
        //TODO : IMPORTANT
        bool checkCase(int case_x, int case_y); 

    public:
        bool checkGridIsGood();
        Board(int size, int difficulty);
        void display();
        bool fillGrid(int x=0, int y=0);
        bool makeGridEasier();
        friend std::ostream& operator<<(std::ostream& in,const Board& board);
        bool backtracking(int position, int &compteref);
};

}

