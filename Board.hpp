#ifndef			__HPP_BOARD__
#define			__HPP_BOARD__

#include "BoardValues.hpp"
#include <iostream>

#define HEIGHT 10
#define WIDTH 10


class Board {

	public:
		
		Board();
		
		Board(const Board &other);

		Board& operator=(const Board& other);

		int count() const;

		bool operator< (const Board& other);

		~Board();

		void setVisible(bool v);

		/*Board Internal is a int* */
		class Internal {
			public:

			Internal(int* _g) {
				_grid = _g;
			}

			/**In the Internal class */
			int& operator[](int index);

			private:
				int* _grid;
		};
		/**In the Board class */
		Internal operator[](int index);

	private:
		/**An int pointer (holds an int) to navigate the coordinate's data.*/
		int* grid;

		/**Determines if board should be visible.*/
		bool visible;
	
	friend std::ostream& operator<<(std::ostream& os, Board const& b);

};


#endif
