#include "Board.h"
#include <cmath>
#include <time.h>

namespace Sudoku {
Board::Board(int size, int difficulty){
    _size = size;
    if(difficulty < 0 || difficulty > 5) {
        throw std::runtime_error("difficulty must be between 1 and 5");
    }
    else {
    _difficulty =difficulty;

    }
    float perfect_square = (int)sqrt(_size*_size);
    if((perfect_square * perfect_square) == _size){
        throw std::runtime_error("the size need to be a perfect square");
    }
    _board.resize(_size*_size);
    for(int i = 0; i < _board.size(); i++){
        _board.at(i) = 0;
    }
}
void Board::display(){ //
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

 bool Board::fillGrid(int x, int y){
    //std::cout << " x " << x << " y " << y << std::endl;
    std::vector<int> already_done;
        do {

         int number_to_place;
        do { // selecting a number that we have not already used
                number_to_place = rand()  % _size + 1;
         }while(std::find(already_done.begin(), already_done.end(), number_to_place) != already_done.end());

        _board.at(y*_size+x) = number_to_place;
        already_done.push_back(number_to_place);

        while(!checkGridIsGood()){
            
            if(already_done.size() == _size){   // we have tried everything
            if(y != _size - 1 && x != _size - 1){
                _board.at(y*_size+x+1) = 0; // for backtracking
                // it enables us to search faster for valid solutions

            }
                //display(); 
                //std::cout << "going back -1" << " x " << x << " y " << y << std::endl;

                return false;
        } // we can try another number
        do {
            number_to_place = rand()  % _size + 1;
         }while(std::find(already_done.begin(), already_done.end(), number_to_place) != already_done.end());
            _board.at(y*_size+x) = number_to_place; // testing it
        }

        if(x == _size-1){
            if(y == _size-1){
                return true; // we are at the end
            }
            if(fillGrid(0, y+1)) return true; // we are at the end of a line
        }
        else{
            if(fillGrid(x+1, y)) return true;
        }
        std::cout << "backtracked x " << x << " y " << y << " count " << already_done.size() << std::endl;
        // we backtracked !
        //display();
        }while(true);

    return false;
 }
  bool Board::checkGridIsGood(){ 
     for(int y = 0; y < _size; y++){ // check horizontal lines
        for(int i = 1; i <= _size; i++ ){
            int sum = 0;
            for(int x = 0; x < _size; x++){ // check lines
                    if(_board.at(x+y*_size) == i){
                        sum++;
                    }
                    if(sum > 1) return false;
            }


        }
    }

    for(int x = 0; x < _size; x++){ // check vertical lines
        for(int i = 1; i <= _size; i++ ){
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
    for(int y = 0; y < _size; y+= sqrt(_size)){ // check each subcase
        for(int x = 0; x < _size; x+= sqrt(_size)){
            if(!this->checkCase(x, y)){
                return false;
            }
        }
    }
    return true;
}

bool Board::checkCase(int case_x, int case_y) {
    const int size = sqrt(_size*_size);
    int sum = 0;
    for(int i = 1; i <= _size; i++){
        sum = 0;
        for(int y = 0; y < size; y++){
            for(int x = 0; x < size; x++){
                int x_coords = case_x*size + x; // *sqrt(_size*_size) because each subgrid is a sqrt(_size*_size)*sqrt(_size*_size) (3*3 if we are on a 9*9 grid)
                int y_coords = case_y*size + y;
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
return in;
}

bool Board::backtracking(int position){
    if(position == (int) _board.size()){
                return true;
    }
    int i = (position % _size) , j = std::round(position / _size); // convert linear to x /y coordinates

    if(_board.at(i + j * _size) != 0){ // this case is already filled => skip it
        return backtracking(position + 1);

    }

    for (int k=1; k <= _size; k++) // testing every possibility
    {
         _board.at(position) = k;

        if (checkGridIsGood()) // check is valid
        {

            if (backtracking(position+1)){
                return true; // we propagate the "good news" that "everything" is valid 
            }
        }
        else {
                _board.at(position) = 0; // what we did is wrong => clearing the case
        }
    }

    return false;
}
bool Board::makeGridEasier(){
    srand(time(nullptr));
for(int i = 0; i < _difficulty * 10 ; i++){
   int pos = rand() % (_size*_size); // erasing a case at random
    _board.at(pos) = 0;
}

}

}

