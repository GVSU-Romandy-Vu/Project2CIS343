#ifndef				__HPP_SHIP__
#define				__HPP_SHIP__

#include <exception>
#include <string>

/**************************************************
 * 
 * An Exception inherited from the standard exception
 * to throw a message if player sunk a ship.
 * 
 * @author + Romandy Vu (for commenting)
 * ***********************************************/
class SunkShipException : public std::exception {
	public:
		/*****************************************
		 * 
		 * Constructor to create exception and
		 * to prompt its message.
		 * 
		 * @param message The message prompted when
		 * catched.
		 * ***************************************/
		SunkShipException(const std::string& message) : _message(message){}
	private:
		/**The message that the exception holds. */
		std::string _message;
};

/****************************************************
 * 
 * The class to create a certain ship. Used to create
 * a ship from the Battleship game.
 * *************************************************/
class Ship {
	public:
		/********************************************
		 * Constructor of Ship class
		 * 
		 * @param _spaces The ship's size.
		 * @param _name The ship's name.
		 * @param _chr The ship's character representation
		 * that is printed to the board.
		 * *****************************************/
		Ship(int _spaces, std::string _name, int _chr) : spaces{_spaces}, name(_name), chr{_chr} { }
		
		/********************************************
		 * 
		 * Getter method of the ship's character 
		 * representation
		 * 
		 * @return The ship's character representation
		 * as an integer (ASCII).
		 * *****************************************/
		int getChr() const { return chr; }

		/********************************************
		 * 
		 * Getter method of ship's size.
		 * 
		 * @return size of ship it takes up in Board.
		 * *****************************************/
		int getSpaces() const { return spaces; }

		/*******************************************
		 * 
		 * Getter method of how many times the ship
		 * has been hit.
		 * 
		 * @return How many times the ship was hit.
		 * ****************************************/
		int getHits() const { return hits; }

		/*******************************************
		 * 
		 * Used to add a hit to the ship. If the
		 * number of hits equals the ship size,
		 * it throws an exception.
		 * ****************************************/
		void addHit() { hits++; if(hits == spaces){ throw SunkShipException("You sank a " + name + "!"); }}
		std::string getName() const { return name; }
	private:
		/**Field to hold ship size.*/
		int spaces;

		/**Field to hold how many times ship has been hit.*/
		int hits = 0;

		/**Field to hold the ship's name.*/
		std::string name;

		/**Field to hold the character representation of ship in Board.*/
		int chr;

		/*******************************************
		 * 
		 * Prints ship data in a specific format.
		 * ***************************************/
		friend std::ostream& operator<<(std::ostream& os, Ship const& s){
			os << s.name << " [" << s.spaces << " spaces]";
			return os;
		}
};

#endif
