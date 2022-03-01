#include "Board.hpp"
#include "BoardValues.hpp"
#include <algorithm>
#include <iostream>

/*************************************************************
* @author Romandy Vu
*************************************************************/

//keyword "new" always returns a pointer (dynamically created)
//symbol "::" signifies where function is defined
//DO NOT CREATE A REFERENCE INSIDE A FUNCTION

Board::Board(){
    //allocate memory for grid (grid is a pointer).
    grid = new int[WIDTH * HEIGHT];
    
    //set visibilty to false.
    visible = false;

    for(int i = 0; i < WIDTH * HEIGHT; i++){
    	grid[i] = 0;
    }
}

Board::Board(const Board& other){

    //Copy data from source.
    this->visible = other.visible;

    /*Initalize new memory so it is a deep copy
    *instead of shallow */
    this->grid = new int[WIDTH * HEIGHT];

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            this->grid[(i * 10) + j] = other.grid[(i * 10) + j];
        }
    }

}

/**Set the reference/memory address of this board to "other board"
 * and return that reference.
 * Other is constant, so we can't swap it. */
Board& Board::operator=(Board other){

    this->visible = other.visible;

    /*Might not work
    this->grid = other.grid;
    return *this; */

    std::swap(grid, other.grid);
	    
   return *this;

}

Board::~Board(){
    delete[] grid;
}

void Board::setVisible(bool v){
    this->visible = v;
}

int& Board::Internal::operator[](int index){
    //Size check.
    if(index >= WIDTH){
        throw std::out_of_range(std::to_string(index) + " is greater than or equal to width of " + std::to_string(WIDTH));
    }
    return _grid[index];
}

Board::Internal Board::operator[](int index){
    //Index check.
    if(index >= HEIGHT){
        throw std::out_of_range(std::to_string(index) + " is greater than or equal to grid height of " + std::to_string(HEIGHT));
    }
        return Board::Internal(grid+(index * WIDTH));
}

/**Print out the board data*/

std::ostream& operator<<(std::ostream& os, Board const& b){
    //Used to display value of grid coordinate.
    char ch;

    /*Use a copy operator to get index value from b.
    Cannot access certain b values since b is a constant
    and no operation defined to get index value.*/ 
    Board data = b;

    //Print row labels.
    for (int row = 0; row < HEIGHT; row++){
        std::cout<<"\t"<<row;
    }
    std::cout<<std::endl;

    //Print row border.
    std::cout<<"\t---------------------------------------------------------------------------------"<<std::endl;
    for (int row = 0; row < HEIGHT; row++){
        
        //Print column labels and border.
        std::cout<<row<<"|\t";
        
        //Prints grid coordinate of board.
        for (int col = 0; col < WIDTH; col++){
            ch = data[row][col];

            //Used to hide ship location of computer.
            if(!data.visible && (ch == CARRIER || ch == BATTLESHIP || ch == DESTROYER || ch == SUBMARINE || ch == PATROLBOAT)){
                //ch = EMPTY;
            }
            //Print value of grid coordinates, unless hidden.
            std::cout<<ch<<"\t";
        }

        std::cout<<std::endl;

    }
    
    return os;
}

int Board::count() const{
    //Helpful to retrieve values of Board.
    Board data = *this;

    //Return value.
    int hits = 0;
    
    //Checks each coordinate if it is HIT and increment it.
    for(int row = 0; row < WIDTH; row++){
        for(int col = 0; col < HEIGHT; col++){
            if(data[row][col] == HIT){
                hits++;
            }
        }
    }

    return hits;
    
}

bool Board::operator< (const Board& other){
    //If less than, the variable holding "this" is winning.
    return this->count() < other.count(); 
}
