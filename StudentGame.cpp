#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>

//Included: (Do I need this though? Already defined elsewhere.)
#include <vector>
#include <string>

/*************************************************************
* @author Romandy Vu
*************************************************************/


/*************************************************************************
 * The Constructor that will create the ships vector and add ships to it.
 *************************************************************************/
Game::Game(){
	player = Board();
	player.setVisible(true);
	computer = Board();
	//Fill list with all possible ships.
	ships = {Ship(5, "CARRIER", 'C'), Ship(4, "BATTLESHIP", 'B'), Ship(3, "DESTROYER", 'D'),
	 Ship(3, "SUBMARINE", 'S'), Ship(2,"PATROL BOAT", 'P')};
}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame(){
	//Prints message.
	hello();
	
	//Place ships for computer
	placeShipsPC();
	
	//Allow for player ship placement
	placeShips();
	
	//Cycle between player and computer hit placement.
	run();
}

/**
 * Handle the human placing ships.
 */
void Game::placeShips(){
	
	//Determines if a ship needs to be placed again.
	bool valid = false;

	//1st safeguard to ensure entry is numeric.
	std::string row_data;
	std::string col_data;
	std::string dir_data;

	//Conditions that must be met so valid is true.
	bool row_valid;
	bool col_valid;
	bool dir_valid;

	//For the place direction parameter.
	Direction d;

	//Done so all the ships are placed.
	while (!ships.empty()){
		//Prints player board of ships they already placed, if any.
		std::cout<<player<<std::endl;

		//Retrieve 1st ship in current list.
		Ship current = ships.front();

		std::cout<<"Enter coordinates for "<<current<<std::endl;
		
		/*Set to false everytime as the previous ship placement is valid
		* but current ship placement will not be.*/
		valid = false;
		
		//Done so each ship placement is valid.
		while (!valid){

			/*Set to false for the same reason why "valid" is false. */
			row_valid = false;
			col_valid = false;
			dir_valid = false;

			//Retrieve inputs
			std::cout<<"Enter Row number: \n"<<std::endl;
			std::cin>>row_data;
			std::cout<<"Enter Column number: \n"<<std::endl;
			std::cin>>col_data;
			std::cout<<"Enter direction (0 for horizontal, 1 for Vertical)\n"<<std::endl;
			std::cin>>dir_data;


			//Checks if input is valid.
			if (row_data.length() == 1 && isdigit(row_data[0])){
				row_valid = true;
			}
			if(col_data.length() == 1 && isdigit(col_data[0])){
				col_valid = true;
			}
			//Determines what direction input is.
			if("0" == dir_data || "1" == dir_data){
				dir_valid = true;
				if("0" == dir_data){
					d = HORIZONTAL;

				}
				else{
					d = VERTICAL;
				}
			}

			//Condition if all inputs are valid.
			if (row_valid && col_valid && dir_valid){
				valid = true;
				//Removes the ship placed from list.
				if(place(std::stoi(row_data), std::stoi(col_data), d, current, player)){
					ships.erase(ships.begin());
				}

			}

			//Prompts message if ship is invalid.
			if(!valid){
				std::cout<<"Invalid coordinates: both coordinates not 0-9 or direction not 0 or 1. \n"<<std::endl;
			}
		}
	
	}
	//Add all the ships so that once the player sinks a ship, a message is prompted.
	ships = {Ship(5, "CARRIER", 'C'), Ship(4, "BATTLESHIP", 'B'), Ship(3, "DESTROYER", 'D'),
         Ship(3, "SUBMARINE", 'S'), Ship(2,"PATROL BOAT", 'P')};



}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){
	//Used for parameters for place.
	int x;
	int y;
	Direction direction;

	//Calculates direction, currently modulo which makes it all vertical.
	int calcDir;
	
	//The random number generation.
	std::default_random_engine generator;
	//ADDED: -1 to WIDTH. The range that the computer can choose for ship placement.
	std::uniform_int_distribution<int> distribution(0, WIDTH - 1);
	
	//Loop until all ship is placed.
	while(!ships.empty()){
		//Get ship first in current list
		Ship current = ships.front();

		//Generate random values and find direction.
		x = distribution(generator);
		y = distribution(generator);
		int calcDir = (x + y) % 2;

		//Set direction to something for place parameter.
		if(0 == calcDir){
			direction = HORIZONTAL;
		}
		else{
			direction = VERTICAL;
		}
		
		//Ensure that any ship part is not out of bounds.
		while(x + current.getSpaces() >= WIDTH || y + current.getSpaces() >= HEIGHT){
			x = distribution(generator);
			y = distribution(generator);

		}

		//Place ship into board and remove ship from list if successful.
		if(place(x,y,direction, current, computer)){
			ships.erase(ships.begin());
		}
	}
	
	//Adds all ships back to list to help method of player ship placement.
	ships = {Ship(5, "CARRIER", 'C'), Ship(4, "BATTLESHIP", 'B'), Ship(3, "DESTROYER", 'D'),
	 Ship(3, "SUBMARINE", 'S'), Ship(2,"PATROL BOAT", 'P')};

}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
	/*Determines if message of placing should appear.
	Done so, so player won't see invalid ship placement of computer. */
	bool prompt = true;

	//Checks if it is computer that is placing the ship.
	if (&b == &computer){
			prompt = false;
	}
	//Try-Catch since exception is thrown in retrieval of indexes (Board[][]).
	try{
		//Checks if any coordinates are taken.
		if (HORIZONTAL == d){
			for(int i = y;  i < y + s.getSpaces(); i++){
				if(EMPTY != b[x][i]){
					//Throws invalid argument unless, exception is thrown from index retrieval.
					throw std::invalid_argument("");
				}
			}
			//If exception is thrown, fill the check spots with the ship character representation.
			for(int i = y; i < y + s.getSpaces(); i++){
				b[x][i] = s.getChr();
			}
		}
		//Checks if any coordinates are taken vertically.
		else{
			for(int i = y; i < y + s.getSpaces(); i++){
				if(EMPTY != b[i][y]){

					throw std::invalid_argument("");
				}
			}

			for(int i = x; i < x + s.getSpaces(); i++){
				b[i][y] = s.getChr();
			}
		}
		//If ship placement is successful.
		return true;
	}
	catch(std::out_of_range& e){
		if(prompt){
			std::cout<<"Invalid coordinates: Coordinates out of range."<<std::endl;
			
		}
		//If ship placement is unsuccessful from invalid coordinates.
		return false;
	}
	catch(std::invalid_argument& a){
		if(prompt){
			std::cout<<"Invalid coordinates: Placement of ship overlaps with another."<<std::endl;
		}
		//If ship placement is unsuccessful from overlapping ships.
		return false;
	}
}


void Game::run(){
	/* 17 is the number of total ship parts of the default pieces of the Battleship game. 
	* If 17 is reached, it means that all the ships sunk of whoever board it is.
	*/
	while (!(player.count() == 17)){
		//Allow player to place hit.
		humanTurn();

		//Done so that player might hit all computer's ship before the computer's turn.
		if(computer.count() == 17){
			std::cout<<"You win!"<<std::endl;
			break;
		}

		//Allow computer to place hit.
		computerTurn();

		
		//Prompt whoever is winning.
		if (computer < player){
			std::cout<<"The computer is winning!"<<std::endl;
		}
		else{
			std::cout<<"You are winning!"<<std::endl;
		}
	}

	//Run if loop doesn't break.
	if(player.count() == 17){
		std::cout<<"You lose."<<std::endl;
	}
}

void Game::humanTurn(){
	bool valid = false;
	std::string row_data;
	std::string col_data;
	bool row_valid;
	bool col_valid;
	try{
		while (!valid){
			std::cout<<"Your board:\n"<<player<<"\n Computer board:\n"<<computer<<std::endl;
			row_valid = false;
			col_valid = false;

			std::cout<<"Enter Row coordinate to attack:"<<std::endl;
			std::cin>>row_data;
			std::cout<<"Enter Column coordinate to attack:"<<std::endl;
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
						std::cout<<"You hit a ship!\n"<<std::endl;
						ship.addHit();
						computer[row][col] = HIT;
						std::cout<<"ship size: "<<ship.getSpaces()<<" Ship hits "<<ship.getHits()<<std::endl;
						if(ship.getSpaces() == ship.getHits()){
							std::cout<<"You sunk a "<<ship.getName()<<std::endl;
						}
					}
				}
				if(EMPTY == result){
					std::cout<<"You missed."<<std::endl;
					computer[row][col] = MISS;
				}
				else if (HIT == result || MISS == result){
					std::cout<<"You already enter that spot, but you lost your turn."<<std::endl;
				}

			}

			if(!valid){
			std::cout<<"Invalid coordinates, try again.\n"<<std::endl;
			}
		}
		std::cout<<"Did not caught ship exception"<<std::endl;
	}
	catch(std::out_of_range& e){
		std::cerr<<e.what()<<std::endl;
		humanTurn();
	}
	catch(SunkShipException& w){
		std::cout<<"Caught ship exception"<<std::endl;
		std::cerr<<w.what()<<std::endl;
	}
}

void Game::computerTurn(){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, WIDTH - 1);
	int x;
	int y;
	bool valid = false;
	int target;
	do{
		x = distribution(generator);
		y = distribution(generator);
		target = player[x][y];

	} while( MISS == target ||  HIT == target);

	if(EMPTY == target){
		player[x][y] = MISS;
		std::cout<<"Computer missed."<<std::endl;
	}
	else{
		player[x][y] = HIT;
		std::cout<<"Computer hit a ship."<<std::endl;
		
	}
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
	Game g;
	g.beginGame();

	return 0;
}
