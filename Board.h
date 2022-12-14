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
        bool checkGridIsGood();
        //TODO : IMPORTANT
        bool checkCase(int case_x, int case_y); 

    public:
        Board(int size, int difficulty);
        void display();
        void fillGrid();
        friend std::ostream& operator<<(std::ostream& in,const Board& board);
        void backtracking();
};

}

