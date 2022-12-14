#include "Board.h"
namespace Sudoku {
Board::Board(int size, int difficulty){
    _size = size;
    if(difficulty < 0 || difficulty > 5) {
        throw std::runtime_error("difficulty must be between 1 and 5");
    }
    else {
    _difficulty =difficulty;

    }
    _board.resize(_size*_size);
    for(int i = 0; i < _board.size(); i++){
        _board.at(i) = 0;
    }
}
void Board::display(){ //TODO display bigger lines outside 3*3 cases
    for(int y = 0; y < _size; y++){
        std::cout << "  ";// in order to align everything
        for(int x = 0; x < _size; x++){ // nice horizontal lne
            std::cout << "────";
        }std::cout << std::endl;

        for(int x = 0; x < _size; x++){
            std::cout << " │ " << _board.at(y*_size + x);
            if(x == _size - 1){
                std::cout << " │";
            }
        }

        std::cout << std::endl;
        if(y == _size - 1){ // nice horizontal line for the last line
             std::cout << "  "; // in order to align everything
            for(int x = 0; x < _size; x++){
            std::cout << "────";
        }std::cout << std::endl;
        }
    }
}

 void Board::fillGrid(){
    std::vector<int> already_done;
    for(int y = 0; y < _size; y++){
        for(int x = 0; x < _size; x++){
            do {
            int number_to_place;
            do {
                number_to_place = rand()  % 9 + 1;
            }while(std::find(already_done.begin(), already_done.end(), number_to_place) != already_done.end());

            
            _board.at(y*_size+x) = number_to_place;
            if(!checkGridIsGood()){
             _board.at(y*_size+x) = 0;
            }
            else {
                break;
            }
            }while(true);
            already_done.clear();
        }
    display();

    }
    //TODO : this
    // fill perfect grid first
    // then permutate

 }
  bool Board::checkGridIsGood(){ //TODO test this
     for(int y = 0; y < _size; y++){
        for(int i = 1; i < 10; i++ ){
            int sum = 0;
            for(int x = 0; x < _size; x++){
                    if(_board.at(x+y*_size) == i){
                        sum++;
                    }
                    if(sum > 1) return false;
            }  

                        
        }
    }

    for(int x = 0; x < _size; x++){ // check vertical lines
        for(int i = 1; i < 10; i++ ){
            //TODO : ask teacher : can we use std::count ? 
            //cant use count on vertical lines
            // doing it manually
            int sum=0;
            for(int y = 0; y < _size; y++){
                if(_board.at(y*_size+x) == i){
                    sum += 1;
                }
            }
            if(sum > 1){
                return false;
            }
            }
    }
    for(int y = 0; y < _size / 3; y++){ // check each subcase
        for(int x = 0; x < _size/3; x++){
            if(!this->checkCase(x, y)){
                return false;
            }
        }
    }
    return true;
}

bool Board::checkCase(int case_x, int case_y) {
    int sum = 0;
    for(int i = 1; i <= 9; i++){
        sum = 0;
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                int x_coords = case_x*3 + x; // *3 because each subgrid is 3*3
                int y_coords = case_y*3+ y;
                if(_board.at(x_coords + y_coords*_size) == i){
                    sum += 1;
                }
        }
        if(sum > 1){
            return false;
        }
    }
    }
    return true;
    //test
    
}
std::ostream& operator<<(std::ostream& in, const Board& board){
for(int y = 0; y < board._size; y++){
        in << "  ";// in order to align everything
        for(int x = 0; x < board._size; x++){ // nice horizontal lne
            in << "────";
        }in << std::endl;

        for(int x = 0; x < board._size; x++){
            in << " │ " << board._board.at(y*board._size + x);
            if(x == board._size - 1){
                in << " │";
            }
        }

        in << std::endl;
        if(y == board._size - 1){ // nice horizontal line for the last line
             in << "  "; // in order to align everything
            for(int x = 0; x < board._size; x++){
            in << "────";
        }in << std::endl;
        }
        return in;
    }        

}
}

