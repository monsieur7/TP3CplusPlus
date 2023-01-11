#include "Board.h"
#include <cmath>
#include <time.h>

namespace Sudoku {
Board::Board(int size, int difficulty){
    srand(time(nullptr));
    _size = size;
    if(difficulty < 0 || difficulty > 5) {
        throw std::runtime_error("difficulty must be between 1 and 5");
    }
    else {
    _difficulty =difficulty;

    }
    int test=floor(sqrt(_size));
    if( test*test != _size){
        throw std::runtime_error("it need to be a perfect square number !");
    }
    _board.resize(_size*_size);
    for(int i = 0; i < _board.size(); i++){
        _board.at(i) = 0;
    }
    _cache.resize(_size*_size);

}
void Board::display(){ //
    for(int y = 0; y < _size; y++){
        std::cout << "  ";// in order to align everything
        for(int x = 0; x < _size; x++){ // nice horizontal lne
        if(_size > 9){
            std::cout << "─────";
        }else {
            std::cout << "────";
        }
        }std::cout << std::endl;

        for(int x = 0; x < _size; x++){
            std::cout << " │ " << _board.at(y*_size + x);
            if(_board.at(y*_size+x) < 9 && _size > 9){
                std::cout << " ";
            }
            if(x == _size - 1){
                std::cout << " │";
            }
        }

        std::cout << std::endl;
        if(y == _size - 1){ // nice horizontal line for the last line
             std::cout << "  "; // in order to align everything
            for(int x = 0; x < _size; x++){
                if(_size > 9){
                    std::cout << "─────";
                }else {
                    std::cout << "────";
                }        
            }std::cout << std::endl;
        }
    }
}

 bool Board::fillGrid(int x, int y){
    int i = 0;
    int number_to_place;
    //std::cout << " x " << x << " y " << y << std::endl;
        do {

        do { // try until the grid is valid
            if(_cache[(x+y*_size)].size() == _size){   // we have tried everything
            //std::cout << "going back -1" << " x " << x << " y " << y << std::endl;
            //display(); 
            _board[(y*_size+x+1)] = 0; // for backtracking beacuse the next case is wrong => it goes faster
            _cache[(x+y*_size)].clear();        
            return false;
        } // we can try another number
        else {
        do {
            number_to_place = (rand() % _size) + 1;
         }while(std::find(_cache[(x+y*_size)].begin(), _cache[(x+y*_size)].end(), number_to_place) != _cache[(x+y*_size)].end());
         _cache[(x+y*_size)].push_back(number_to_place);
        _board[(y*_size+x)] = number_to_place; // testing it
        }
        }while(!checkGridIsGood());

       // display();
        if(x == _size-1){
            if(y == _size-1){
                return true; // we are at the end
            }
            if(fillGrid(0, y+1)) return true; // we are at the end of a line
        }
        else{
            if(fillGrid(x+1, y)) return true;
        }
        std::cout << "backtrack at x " << x << " y " << y << " size " << _cache[(x+y*_size)].size() << std::endl;            
        // we backtracked !
        //display();
       // _cache[(x+y*_size)].clear();         
        }while(true);

    return false;
 }
  bool Board::checkGridIsGood(){ 
     for(int y = 0; y < _size; y++){ // check horizontal lines
        for(int i = 1; i <= _size; i++ ){
            int sum = 0;
            for(int x = 0; x < _size; x++){ // check lines
                    if(_board[(x+y*_size)] == i){
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
                if(_board[(y*_size+x)] == i){
                    sum += 1;
                }
            }
            if(sum > 1){
                return false;
            }
            }
    }
    for(int y = 0; y < _size; y+= sqrt(_size)){ // check each subcase
        for(int x = 0; x < _size; x+=sqrt(_size)){
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
        for(int y = 0; y < (int)sqrt(_size); y++){
            for(int x = 0; x < (int)sqrt(_size); x++){
                int x_coords = case_x + x; // *3 because each subgrid is 3*3
                int y_coords = case_y + y;
                if(_board[(x_coords + y_coords*_size)] == i){
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
            if(board._size > 9){
                in << "──────";
            }else {
                in << "───";
            }
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
            if(board._size > 9){
                in << "──────";
            }else {
                in << "───";
            }
        }in << std::endl;
        }
        return in;
    }        
return in;
}

bool Board::backtracking(int position, int & comptref){
    ++comptref;
    if(position == (int) _board.size()){
                return true;
    }
    int i = (position % _size) , j = std::round(position / _size); // convert linear to x /y coordinates

    if(_board.at(i + j * _size) != 0){ // this case is already filled => skip it
        return backtracking(position + 1, comptref);

    }

    for (int k=1; k <= _size; k++) // testing every possibility
    {
         _board.at(position) = k;

        if (checkGridIsGood()) // check is valid
        {

            if (backtracking(position+1, comptref)){
                return true; // we propagate the "good news" that "everything" is valid 
            }
        }
        else {
                _board.at(position) = 0; // what we did is wrong => clearing the case
        }
    }

    return false;
}
bool __attribute__((optimize("O0"))) Board::makeGridEasier(){ //COMPILER : DO NOT OPTIMIZE THIS
    srand(time(nullptr));
    int i;
    float difficulty = _difficulty/20.0f;
for(i = 0; i <(int) (_size*_size * difficulty); i++){
   int pos = rand() % (_size*_size); // erasing a case at random
    _board.at(pos) = 0;

}
return true;
}
bool Board::fillGrid2(int pos){
    //for(y = 0; y < _size; y++)
    //backtracking(0, null);
    display();
}
}