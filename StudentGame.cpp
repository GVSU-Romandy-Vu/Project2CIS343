#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>

//Included:
#include <vector>
#include <string>



/*************************************************************************
 * The Constructor that will create the ships vector and add ships to it.
 *************************************************************************/
Game::Game(){
	player = Board();
	computer = Board();
	ships = {Ship(5, "CARRIER", 'C'), Ship(4, "BATTLESHIP", 'B'), Ship(3, "DESTROYER", 'D'),
	 Ship(3, "SUBMARINE", 'S'), Ship(2,"PATROL BOAT", 'P')};
}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame(){
	hello();
	placeShipsPC();
	placeShips();
	run();
}

/**
 * Handle the human placing ships.
 */
void Game::placeShips(){
	
	bool valid = false;
	std::string row_data;
	std::string col_data;
	std::string dir_data;
	bool row_valid;
	bool col_valid;
	bool dir_valid;
	Direction d;

	while (!ships.empty()){
		Ship current = ships.front();
		std::cout<<"Enter coordinates for "<<current<<std::endl;
		valid = false;
		while (!valid){
			row_valid = false;
			col_valid = false;
			dir_valid = false;

			std::cout<<"Enter Row number: \n"<<std::endl;
			std::cin>>row_data;
			std::cout<<"Enter Column number: \n"<<std::endl;
			std::cin>>col_data;
			std::cout<<"Enter direction (0 for horizontal, 1 for Vertical)\n"<<std::endl;
			std::cin>>dir_data;


			if (row_data.length() == 1 && isdigit(row_data[0])){
				row_valid = true;
			}
			if(col_data.length() == 1 && isdigit(col_data[0])){
				col_valid = true;
			}
			if("0" == dir_data || "1" == dir_data){
				dir_valid = true;
				if("0" == dir_data){
					d = HORIZONTAL;

				}
				else{
					d = VERTICAL;
				}
			}

			if (row_valid && col_valid && dir_valid){
				valid = true;
				if(place(std::stoi(row_data), std::stoi(col_data), d, current, player)){
					ships.erase(ships.begin());
				}

			}

			if(!valid){
				std::cout<<"Invalid coordinates: both coordinates not 0-9 or direction not 0 or 1. \n"<<std::endl;
			}
			


		}
	}
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){
	int x;
	int y;
	Direction direction;
	int calcDir;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,WIDTH);
	while(!ships.empty()){
		Ship current = ships.front();
		x = distribution(generator);
		y = distribution(generator);
		int calcDir = (x + y) % 2;

		if(0 == calcDir){
			direction = HORIZONTAL;
		}
		else{
			direction = VERTICAL;
		}
		
		while(x + current.getSpaces() >= WIDTH || y + current.getSpaces() >= HEIGHT){
			x = distribution(generator);
			y = distribution(generator);
		}

		if(place(x,y,direction, current, computer)){
			ships.erase(ships.begin());
			std::cout<<current.getName()<<" Has been removed"<<std::endl;
		}
	}
	ships = {Ship(5, "CARRIER", 'C'), Ship(4, "BATTLESHIP", 'B'), Ship(3, "DESTROYER", 'D'),
	 Ship(3, "SUBMARINE", 'S'), Ship(2,"PATROL BOAT", 'P')};

}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
	bool prompt = true;
	if (&b == &computer){
			prompt = false;
	}
	try{
		if (HORIZONTAL == d){
			for(int i = x; i < WIDTH; i++){
				if(EMPTY != b[i][y]){
					throw std::invalid_argument("");
				}
			}
			for(int i = x; i < WIDTH; i++){
				b[i][y] == s.getChr();
			}
		}
		else{
			for(int i = y; i < HEIGHT; i++){
				if(EMPTY != b[x][i]){
					throw std::invalid_argument("");
				}
			}

			for(int i = y; i < HEIGHT; i++){
				b[x][i] == s.getChr();
			}
		}
		return true;
	}
	catch(std::out_of_range& e){
		if(prompt){
			std::cout<<"Invalid coordinates: Coordinates out of range."<<std::endl;
			
		}
		return false;
	}
	catch(std::invalid_argument& a){
		if(prompt){
			std::cout<<"Invalid coordinates: Placement of ship overlaps with another."<<std::endl;
		}
		return false;
	}
}


void Game::run(){
	while (!(computer.count() == 17)){
		humanTurn();

		if(player.count() == 17){
			std::cout<<"You win!"<<std::endl;
			break;
		}

		computerTurn();

		
		if (computer < player){
			std::cout<<"The computer is winning!"<<std::endl;
		}
		else{
			std::cout<<"You are winning!"<<std::endl;
		}
	}

	if(computer.count() == 17){
		std::cout<<"The computer wins!"<<std::endl;
	}
}

void Game::humanTurn(){
	bool valid = false;
	std::string row_data;
	std::string col_data;
	bool row_valid;
	bool col_valid;

	while (!valid){
		std::cout<<"Your board:\n"<<player<<"\n Computer board:\n"<<computer<<std::endl;
		row_valid = false;
		col_valid = false;

		std::cout<<"Enter Row coordinate to attack: \n"<<std::endl;
		std::cin>>row_data;
		std::cout<<"Enter Column coordinate to attack: \n"<<std::endl;
		std::cin>>col_data;

		if (row_data.length() == 1 && isdigit(row_data[0])){
			row_valid = true;
		}
		if(col_data.length() == 1 && isdigit(col_data[0])){
			col_valid = true;
		}

		if (row_valid && col_valid){
			valid = true;
			int row = std::stoi(row_data);
			int col = std::stoi(col_data);
			
			int result = computer[row][col];

			for (Ship ship: ships){
				if(ship.getChr() == result){
					ship.addHit();
					std::cout<<"You hit a ship!\n"<<std::endl;
				}
			}
			if(MISS == result){
				std::cout<<"You missed.\n"<<std::endl;
			}
			computer[row][col] == HIT;
		}

		if(!valid){
			std::cout<<"Invalid coordinates, try again.\n"<<std::endl;
		}
	}
}

void Game::computerTurn(){
}

void Game::hello(){
	std::cout<<"\tWELCOME TO BATTLESHIP"<<std::endl;

	std::cout<<"Begin by placing your ships, the pieces:\n"<<std::endl;
	std::cout<<"\tCarrier [5 spaces]"<<std::endl;
	std::cout<<"\tBattleship [4 spaces]"<<std::endl;
	std::cout<<"\tDestroyer [3 spaces]"<<std::endl;
	std::cout<<"\tSubmariner [3 spaces]"<<std::endl;
	std::cout<<"\tPatrol Boat [2 spaces]\n"<<std::endl;
}

/**
 * Create a game instance and start.
 */
int main(int argc, char** argv){
	(void)argc;
	(void)argv;
	//Added constructor "= Game()"
	Game g = Game();
	g.beginGame();

	return 0;
}