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
	ships.insert(Ship(5, "CARRIER", 'C', ));
	ships.insert(Ship(4, "BATTLESHIP", 'B'));
	ships.insert(Ship(3, "DESTROYER", 'D'));
	ships.insert(Ship(3, "SUBMARINE", "S"));
	ships.insert(Ship(2,"PATROL BOAT", P));
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
	std::cout<<"Enter "
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){
	int x;
	int y;
	Direction direction;
	Ship current;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> (distribution(0,WIDTH));
	while(!ships.empty()){
		current = ships.front();
		x = distribution(generator);
		y = distribution(generator);
		direction = (x + y) % 2;
		
		if(0 == direction){
			while (x + current.getSpaces() >= WIDTH){
				x = distribution(generator);
			}
		}
		if(1 == direction){
			while (y + current.getSpaces() >= HEIGHT){
				y = distribution(generator);
			}
		}

		if(place(x,y,direction, current, computer)){
			ships.erase(0);
			std::cout<<current.getName()<<" Has been removed"<<endl;
		}
	}

	ships.insert(Ship(5, "CARRIER", 'C', ));
	ships.insert(Ship(4, "BATTLESHIP", 'B'));
	ships.insert(Ship(3, "DESTROYER", 'D'));
	ships.insert(Ship(3, "SUBMARINE", "S"));
	ships.insert(Ship(2,"PATROL BOAT", P));
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
			int row = std::stoi(row_data);
			int col = std::stoi(col_data);
			
			int result = computer[row][col];
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