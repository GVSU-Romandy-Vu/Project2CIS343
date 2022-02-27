#ifndef				__HPP_GAME__
#define				__HPP_GAME__

#include "Board.hpp"
#include "Direction.hpp"
#include "Ship.hpp"
#include <vector>

/**********************************************************************************
 * 
 * Interface for StudentGame
 * 
 * @author + Romandy Vu (for commenting)
 **********************************************************************************/
class Game {
	public:
		/*************************************************************************
		 * 
		 * Default constructor to create the game session.
		 *************************************************************************/
		Game();
		
		/*************************************************************************
		 * 
		 * The starting prompt when the user first runs the game.
		 ************************************************************************/
		void hello();
		
		/*************************************************************************
		 *
		 * Method where the player would place their ships.
		 *************************************************************************/
		void placeShips();

		/**************************************************************************
		 * 
		 * Method where computer ships would be placed.
		 *************************************************************************/
		void placeShipsPC();

		/**************************************************************************
		* 
		* let's user and then computer setup boards then calls run()
		**************************************************************************/
		void beginGame();

		/**************************************************************************
		 * 
		 * Call human turn/computer turn until someone wins.
		 *************************************************************************/
		void run();

		/*************************************************************************
		 * 
		 * Method where user would place their hits.
		 * Probably print the board in this method.
		 ************************************************************************/
		void humanTurn();

		/*************************************************************************
		 * 
		 * Method where computer would place their hits.
		 ************************************************************************/
		void computerTurn();

		/*************************************************************************
		 * 
		 * Method that checks if ship placement is valid.
		 * 
		 * @param x the row coordinate that is being placed at.
		 * @param y the column coordinate that is being placed at.
		 * @param d the orientation of the ship.
		 * @param s the ship being placed.
		 * @param b the board being used to place ships.
		 ************************************************************************/
		bool place(const int& x, const int& y, Direction d, const Ship& s, Board& b);

	private:
		/**The board of the player to place ships and for the computer to place hits.*/
		Board player;
		/**The board of the computer to place ships and the player to place hits.*/
		Board computer;

		/**A list to store the different ships, used to help place ships for computer
		 * and player, and for prompting message if player sunk a ship.*/
		std::vector<Ship> ships;
};

#endif
