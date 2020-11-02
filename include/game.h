#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>


/** 
 * @brief the second most important class of the program
 * 
 * This class contains all the methods that are related to the changes that are
 * realised on the chessboard. It concerns the tasks that are not too specific
 * to one piece.
 * 
 */
class Chessboard
{
private:
	
	Piece * c_board[8][8];

public:
	
	Chessboard();
	~Chessboard();

	void print_board();
	bool is_that_legal(const char * move_user, int * move_grid, char color);
	bool move_pieces(int * move_grid);

	void deactivate_en_passant_white();
	void deactivate_en_passant_black();
};


#endif