#include <vector>
#include <algorithm>
#include <iostream>

#pragma once

class Board {
    private:
        std::vector<int> _board;
        int _size;
        bool checkGridIsGood();
        //TODO : IMPORTANT
        bool checkCase(int case_x, int case_y); 

    public:
        Board(int size);
        void display();
        void fillGrid();



};