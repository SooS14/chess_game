#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>



/** 
 * @brief most important class of the program
 * 
 * This class contains all the methods that are related to the various pieces
 * on the Chessboard. The virtual function "move" is declared here and has a
 * different implementation for each piece. The attributes "p_first_move" and 
 * "p_en_passant" are common for all pieces despite the fact that some pieces
 * don't need them (for instance the knight) but it makes the program clearer.
 * 
 */
class Piece 
{
	private:
		std::string p_name;
		int p_id;
		char p_color;
	
	public:
		bool p_first_move;
		bool p_en_passant;

		Piece(std::string name, int id, char color, bool first_move,
				bool en_passant);
		virtual ~Piece();
		int get_id() const;
		char get_color() const;
		bool get_first_move() const;
		std::string get_name() const;
		
		virtual bool move(int * move_grid,
							char ** game_state, 
							bool err_report) = 0;	

};



/** 
 * @brief There is one class for each piece and each has its own function "move"
 * 
 */

class Pawn : public Piece
{
public:

	Pawn(std::string name, int id, char color, bool firt_move, bool en_passant);
	~Pawn();

	bool move(int * move_grid, char ** game_state, bool err_report);
};




class Rook : public Piece
{
public:
	Rook(std::string name, int id, char color, bool first_move,
				bool en_passant);
	~Rook();
	bool move(int * move_grid, char ** game_state, bool err_report);
};



class Knight : public Piece
{
public:
	Knight(std::string name, int id, char color, bool first_move,
				bool en_passant);
	~Knight();
	bool move(int * move_grid, char ** game_state, bool err_report);
};


class Bishop : public Piece
{
public:
	Bishop(std::string name, int id, char color, bool first_move,
					bool en_passant);
	~Bishop();
	bool move(int * move_grid, char ** game_state, bool err_report);
};


class Queen : public Piece
{
public:
	Queen(std::string name, int id, char color, bool first_move, 
				bool en_passant);
	~Queen();
	bool move(int * move_grid, char ** game_state, bool err_report);
};


class King : public Piece
{
public:
	King(std::string name, int id, char color, bool first_move,
				bool en_passant);
	~King();
	bool move(int * move_grid, char ** game_state, bool err_report);
};




#endif