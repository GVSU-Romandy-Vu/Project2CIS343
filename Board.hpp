#ifndef			__HPP_BOARD__
#define			__HPP_BOARD__

#include "BoardValues.hpp"
#include <iostream>

#define HEIGHT 10
#define WIDTH 10

/***************************************************
 * 
 * Interface for StudentGame.cpp
 *  
 **************************************************/
class Board {

	public:
		/*****************************************
		* 
		The Board default constructor.
		* Used to get an empty board.
		* Called at the start of game.
		******************************************/
		Board();

		/******************************************
		 * 
		 * The Board copy constructor.
		 * Needs to be overwritten since it contains
		 * a pointer (grid).
		 * 
		 * @param other The board copied from.
		 * @return A Board object.
		 ******************************************/
		Board(const Board &other);

		/******************************************
		 * 
		 * The Board Copy operator
		 * Not a method, but expression that sets an
		 * existing object equal to another existing
		 * object of the same type.
		 * 
		 * Copy and swap (copy data from copy)
		 * Code duplication bad.
		 ******************************************/
		Board& operator=(const Board& other);


		/******************************************
		 * 
		 * Most likely used to count grid data to
		 * determine "lives" left for victory/defeat
		 * condition.
		 * 
		 ******************************************/
		int count() const;

		/*******************************************
		 *
		 * The board comparator
		 * Not a method, but expression to compare
		 * boards, most likely used to compare
		 * ships' integrity between computer and player.
		 ******************************************/
		bool operator< (const Board& other);

		/*******************************************
		 * Board destructor
		 * Used to free data from heap.
		 * Should be called when game ends.
		 *******************************************/ 
		~Board();

		/*******************************************
		 * 
		 * Setter method of board to set visibility.
		 * Should be called with parameter true when
		 * player places all ships.
		 * 
		 * @param v A bool to change visibility of
		 * a board.
		 *******************************************/
		void setVisible(bool v);

		
		/**********************************************
		 * Class inside of Board, helps with modifying
		 * the reference of grid.
		 *
		 **********************************************/ 
		class Internal {
			public:
			/*******************************************
			 * Constructor
			 * 
			 * @param _g array that is being copied.
			 *******************************************/
			Internal(int* _g) {
				_grid = _g;
			}
			/*******************************************
			 * Not a method but expression to get array
			 * index.
			 ********************************************/
			int& operator[](int index);

			private:
				int* _grid;
		};


		Internal operator[](int index);

	private:
		/**The data where the ships, hits, misses are stored.*/
		int* grid;

		/**Determines if board should be visible.*/
		bool visible;
	
	friend std::ostream& operator<<(std::ostream& os, Board const& b);

};


#endif
