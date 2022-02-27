#ifndef			__HPP_BOARD__
#define			__HPP_BOARD__

#include "BoardValues.hpp"
#include <iostream>

#define HEIGHT 10
#define WIDTH 10


/*************************************************************************************
 * 
 * A basis for the board of a specific game. It allows the access to a specific index
 * through indexing.
 * 
 * @author + Romandy Vu (for commenting)
 * **********************************************************************************/
class Board {

	public:
		
		/****************************************
		 * 
		 * The default constructor for Board class
		 * **************************************/
		Board();
		
		/*****************************************
		 * 
		 * The copy constructor for Board class.
		 * ***************************************/
		Board(const Board &other);

		/*****************************************
		 * 
		 * The Copy operator for Board class.
		 * **************************************/
		Board& operator=(const Board& other);

		/*****************************************
		 * 
		 * Method to count certain data for a Board
		 * **************************************/
		int count() const;

		/*****************************************
		 * 
		 * Comparator operation to compare 2 
		 * different boards.
		 * ***************************************/
		bool operator< (const Board& other);

		/***************************************
		 * 
		 * Destructor for Board class.
		 * ************************************/
		~Board();

		/**************************************
		 * 
		 * Setter method for Board visbility
		 * 
		 * @param v bool value if board should
		 * be visible.
		 * ***********************************/
		void setVisible(bool v);

		/*************************************
		 * 
		 * Allows for the operation of Board[][]
		 * to get/set index values.
		 * ***********************************/
		class Internal {
			public:

			/**********************************
			 * 
			 * Constructor for Internal class
			 * @param _g the grid of the Board
			 * *******************************/
			Internal(int* _g) {
				_grid = _g;
			}

			/***********************************
			 * 
			 * Used to get column value of Board. 
			 * ********************************/
			int& operator[](int index);

			private:
				int* _grid;
		};
		/************************************** 
		 * 
		 * Used to get address of row.
		 * ************************************/
		Internal operator[](int index);

	private:
		/**An int pointer (holds an int) to navigate the coordinate's data.*/
		int* grid;

		/**Determines if board should be visible.*/
		bool visible;
	
	/**************************************
	 * 
	 * Allows for printing of board to terminal.
	 * ***********************************/
	friend std::ostream& operator<<(std::ostream& os, Board const& b);

};


#endif
