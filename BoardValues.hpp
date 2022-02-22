#ifndef			__HPP_BOARD_VALUES__
#define			__HPP_BOARD_VALUES__
/**************************************************
 * Enumeration for board values from ASCII code to
 * character:
 * 
 * EMPTY = 'C'
 * BATTLESHIP ='B'
 * DESTROYER = "D"
 * SUBMARINE = 'S'
 * PATROLBOAT = 'P'
 * MISS = '_'
 * HIT = '*'
 *************************************************/
enum BoardValues {
	//No cruiser
	EMPTY = 0, CARRIER = 67, BATTLESHIP = 66, DESTROYER = 68, SUBMARINE = 83, PATROLBOAT = 80, MISS = 95, HIT = 42
};

#endif
