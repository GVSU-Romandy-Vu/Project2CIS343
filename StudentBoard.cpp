#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>

//keyword "new" always returns a pointer (dynamically created)
//symbol "::" signifies where function is defined
//Cannot return a reference to an object created inside a function
//Remember the memory model we are constrained to use.
/**
 * Can't set a reference (ClassType& = ...) Won't always work
 * 
 */

Board::Board(){
}

Board::Board(const Board& other){
}

Board& Board::operator=(const Board& other){
}

Board::~Board(){
}

void Board::setVisible(bool v){
}

int& Board::Internal::operator[](int index){
}

Board::Internal Board::operator[](int index){
}

std::ostream& operator<<(std::ostream& os, Board const& b){
}

int Board::count() const{
}

bool Board::operator< (const Board& other){
}