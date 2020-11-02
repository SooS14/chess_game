#include "game.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>
#include <string.h>

using namespace std;



/**
 * @brief constructor of the class "Chessboard"
 *
 * The atribute c_board is an 2 dimensions dynamically allocated array
 * of pointees on "Piece" classes representing the pieces of a chess game.
 * The empty squares of the board are represented by a pointee on NULL.
 */
Chessboard::Chessboard()
{
	int id = 0;

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece * empty = nullptr;
			c_board[i][j] = empty;
		}
	}


//definition of the white team (pieces)
	c_board[0][0] = new Rook("\u2656", 111, 'w', true, false);
	c_board[0][1] = new Knight("\u2658", 121, 'w', true, false);
	c_board[0][2] = new Bishop("\u2657", 131, 'w', true, false);
	c_board[0][3] = new Queen("\u2655", 140, 'w', true, false);
	c_board[0][4] = new King("\u2654", 150, 'w', true, false);
	c_board[0][5] = new Bishop("\u2657", 132, 'w', true, false);
	c_board[0][6] = new Knight("\u2658", 122, 'w', true, false);
	c_board[0][7] = new Rook("\u2656", 112, 'w', true, false);


//definition of the white team (pawns)
	for (int i = 0; i < 8; i++)
	{
		id = 161 + i;
		c_board[1][i] = new Pawn("\u2659", id, 'w', true, false);
	}
	

//definition of the black team (pieces)
	c_board[7][0] = new Rook("\u265C", 211, 'b', true, false);
	c_board[7][1] = new Knight("\u265E", 221, 'b', true, false);
	c_board[7][2] = new Bishop("\u265D", 231, 'b', true, false);
	c_board[7][3] = new Queen("\u265B", 240, 'b', true, false);
	c_board[7][4] = new King("\u265A", 250, 'b', true, false);
	c_board[7][5] = new Bishop("\u265D", 232, 'b', true, false);
	c_board[7][6] = new Knight("\u265E", 222, 'b', true, false);
	c_board[7][7] = new Rook("\u265C", 212, 'b', true, false);


//definition of the black team (pawns)
	for (int i = 0; i < 8; i++)
	{
		id = 261 + i;
		c_board[6][i] = new Pawn("\u265F", id, 'b', true, false);
	}
}


/**
 * @brief destructor of the "Chessboard" class
 *
 * All the memory that can be deallocated with the pointees contained in
 * c_board is deleted. Beware that it is not the case of the pieces that were 
 * destroyed during the game since their pointees have been lost.
 * 
 */
Chessboard::~Chessboard() 
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete c_board[i][j];
		}
	}
}



/**
 * @brief prints the board in the standart output.
 */
void Chessboard::print_board()
{
	cout << "  ";
	for (int i = 0; i < 8; i++)
	{
		char tmp = 97 + i;
		cout << "    " << tmp;
	}
	cout << "\n";
	
	cout << "   +";
	for (int i = 0; i < 8; i++)
	{
		cout << "----+";
	}
	cout << "\n";
	
	for (int i = 0; i < 8; i++)
	{
		cout << i + 1;
		for (int j = 0; j < 8; j++)
		{
			if (c_board[i][j] == nullptr)
			{
				cout << "  | " << " ";
			} else {
				cout << "  | " << c_board[i][j]->get_name();
			}
		}
		cout << "  |\n";
		cout << "   +";
		for (int k = 0; k < 8; k++)
		{
			cout << "----+";
		}
		cout << "\n";
	}
	
}


/**
 * @brief test if a command is legal
 *
 * First the function checks if the characters in move_user are contained in :
 * [a, h] or [1, 8]. Then it transforms these characters in int and puts them
 * in an array given by the user : move_grid. Eventually, the function checks 
 * if the movement within the chessoard is correct. It also handles the castle * movement by filling the array "move_user" with a special code : the location
 * of the king and the position of the tower.
 * 
 * @param move_user a command of the user
 * @param move_grid an int array created by the user to contain the coordinates * 				   of the movement
 * @param color of the one who is playing
 * 
 * @result is a bool 
 */
bool Chessboard::is_that_legal(const char * move_user, 
									int * move_grid, 
									char color)
{		

	//Queenside black castle

	if ((strncmp(move_user, "RRRR", 4) == 0) && (color == 'b'))
	{

		if ((c_board[7][0] != NULL) &&
			(c_board[7][4] != NULL) &&
			(c_board[7][1] == NULL) && 
			(c_board[7][2] == NULL) && 
			(c_board[7][3] == NULL))
		{
			if ((c_board[7][0]->get_id() == 211) &&
				(c_board[7][4]->get_id() == 250))
			{
				move_grid[0] = 7;
				move_grid[1] = 0;
				move_grid[2] = 9;
				move_grid[3] = 9;

				return true;
			}
		}

		cerr << "You can't castle the king, the conditions are not adequate\n";
		return false;
	}

	//Queenside white castle

	if ((strncmp(move_user, "RRRR", 4) == 0) && (color == 'w'))
	{

		if ((c_board[0][0] != NULL) &&
			(c_board[0][4] != NULL) &&
			(c_board[0][1] == NULL) && 
			(c_board[0][2] == NULL) && 
			(c_board[0][3] == NULL))
		{
			if ((c_board[0][0]->get_id() == 111) &&
				(c_board[0][4]->get_id() == 150))
			{
				move_grid[0] = 0;
				move_grid[1] = 0;
				move_grid[2] = 9;
				move_grid[3] = 9;

				return true;
			}
		}

		cerr << "You can't castle the king, the conditions are not adequate\n";
		return false;
	}


	//Kinside black castle

	if ((strncmp(move_user, "rrrr", 4) == 0) && (color == 'b'))
	{

		if ((c_board[7][7] != NULL) &&
			(c_board[7][4] != NULL) &&
			(c_board[7][5] == NULL) && 
			(c_board[7][6] == NULL))
		{
			if ((c_board[7][0]->get_id() == 211) &&
				(c_board[7][4]->get_id() == 250))
			{
				move_grid[0] = 7;
				move_grid[1] = 7;
				move_grid[2] = 9;
				move_grid[3] = 9;

				return true;
			}
		}

		cerr << "You can't castle the king, the conditions are not adequate\n";
		return false;
	}


	//Kingside white castle

	if ((strncmp(move_user, "rrrr", 4) == 0) && (color == 'w'))
	{

		if ((c_board[0][4] != NULL) &&
			(c_board[0][7] != NULL) &&
			(c_board[0][5] == NULL) && 
			(c_board[0][6] == NULL))
		{
			if ((c_board[0][0]->get_id() == 111) &&
				(c_board[0][4]->get_id() == 150))
			{
				move_grid[0] = 0;
				move_grid[1] = 7;
				move_grid[2] = 9;
				move_grid[3] = 9;

				return true;
			}
		}

		cerr << "You can't castle the king, the conditions are not adequate\n";
		return false;
	}

	
	if ((move_user[0] < 97) || (move_user[0] > 104))
	{
		cerr << "That move is not legal.\n";
		return false;
	}
	if ((move_user[1] < 49) || (move_user[1] > 56))
	{
		cerr << "That move is not legal.\n";
		return false;
	}
	if ((move_user[2] < 97) || (move_user[2] > 104))
	{
		cerr << "That move is not legal.\n";
		return false;
	}
	if ((move_user[3] < 49) || (move_user[3] > 56))
	{
		cerr << "That move is not legal.\n";
		return false;
	}
	
	//ligne1 -> move_grid[0], colonne1 -> move_grid[1]
	//ligne2 -> move_grid[2], colonne2 -> move_grid[3]

	move_grid[0] = move_user[1] - 49;
	move_grid[1] = move_user[0] - 97;
	move_grid[2] = move_user[3] - 49;
	move_grid[3] = move_user[2] - 97;

	
	
	if (c_board[move_grid[0]][move_grid[1]] == NULL)
	{
		cerr << "There's nothing here.\n";
		return false;
	}

	if (c_board[move_grid[0]][move_grid[1]]->get_color() != color)
	{
		cerr << "Don't try it, this piece belongs to the other player\n";
		return false;
	}

	if ((move_grid[0] == move_grid[2]) && (move_grid[1] == move_grid[3]))
	{
		cerr << "You can't pass your turn.\n";
		return false;
	}
	
	if (c_board[move_grid[2]][move_grid[3]] != NULL)
	{
		if (c_board[move_grid[2]][move_grid[3]]->get_color() == color)
		{
		cerr << "There's one of yours on this square. It's treason then !\n";
		return false;
		}
	}
	
	return true;

}



/**
 * @brief Handles the movement of pieces
 *
 * This method creates a save of the game's state and give it to "move", a 
 * virtual method specific to each pieces. It checks if the movement is valid.
 * Then move_pieces checks if the king's moving team is in danger. If it is the * case the movement is invalid. It also checks if the king of the opposing 
 * team is in danger.
 *  
 * This is done by creating a "fake" movement. Indeed, each concerned pieces is 
 * given a pointee and the arrival pointee is replaced by the starting piece's 
 * pointee. However until everything has been checked no memory is freed.
 * 
 * If the movement is correct then all the memory that needs to be destroyed
 * is freed thanks to the pointees created previously. If not, then the game can
 * be restored thanks to those pointees and an error is sent to the concerned
 * player.
 * 
 * 
 * @param move_grid contains the coordinates of the movement
 * @result a bool to know if the movement have been realised
 */
bool Chessboard::move_pieces(int * move_grid)
{

	//These tests handles the castle move

	if (move_grid[2] == 9)
	{
		if (c_board[move_grid[0]][4]->get_first_move())
		{
			//Queenside white castle
			if ((move_grid[0] == 0) && (move_grid[1] == 0))
			{
				Piece * rook_ptr = c_board[0][0];
				Piece * king_ptr = c_board[0][4];				
				c_board[0][0] = NULL;
				c_board[0][4] = NULL;
				c_board[0][3] = rook_ptr;
				c_board[0][2] = king_ptr;

				king_ptr->p_first_move = false;
				rook_ptr->p_first_move = false;
			}

			//Queenside black castle
			if ((move_grid[0] == 7) && (move_grid[1] == 0))
			{
				Piece * rook_ptr = c_board[7][0];
				Piece * king_ptr = c_board[7][4];				
				c_board[7][0] = NULL;
				c_board[7][4] = NULL;
				c_board[7][3] = rook_ptr;
				c_board[7][2] = king_ptr;

				king_ptr->p_first_move = false;
				rook_ptr->p_first_move = false;				
			}

			//Kingside white castle
			if ((move_grid[0] == 0) && (move_grid[1] == 7))
			{
				Piece * rook_ptr = c_board[0][7];
				Piece * king_ptr = c_board[0][4];				
				c_board[0][7] = NULL;
				c_board[0][4] = NULL;
				c_board[0][5] = rook_ptr;
				c_board[0][6] = king_ptr;

				king_ptr->p_first_move = false;
				rook_ptr->p_first_move = false;
			}

			//Kingside black castle
			if ((move_grid[0] == 7) && (move_grid[1] == 7))
			{
				Piece * rook_ptr = c_board[7][7];
				Piece * king_ptr = c_board[7][4];				
				c_board[7][7] = NULL;
				c_board[7][4] = NULL;
				c_board[7][5] = rook_ptr;
				c_board[7][6] = king_ptr;

				king_ptr->p_first_move = false;
				rook_ptr->p_first_move = false;
			}			
		}
		else
		{
			cerr << "One of the pieces you are trying to castle has already moved\n";
			return false;
		}
		

		return true;
	}
	


	//game_state is an array to save the position of black and white pieces
	char game_state[8][8];
	char * game_state2[8];

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (c_board[i][j] == NULL)
			{
				game_state[i][j] = 'n';
			}
			else
			{

				if (c_board[i][j]->get_color() == 'b')
				{
					game_state[i][j] = 'b';
				}

				if (c_board[i][j]->get_color() == 'w')
				{
					game_state[i][j] = 'w';
				}
			}
	
		}
		
	}


	for (int i = 0; i < 8 + 1; i++)
	{	
		game_state2[i] = & (game_state[i][0]);
	}


	//the move function checks if the moving piece can be placed on the new location
	if (c_board[move_grid[0]][move_grid[1]]->move(move_grid, game_state2, true) == true)
	{
		char color;
		char cast;
		bool en_passant_test = false;

		color = c_board[move_grid[0]][move_grid[1]]->get_color();


		//a "false" movement is executed
		Piece * src_ptr = c_board[move_grid[0]][move_grid[1]];
		Piece * dest_ptr = c_board[move_grid[2]][move_grid[3]];
		Piece * en_passant_ptr = c_board[move_grid[0]][move_grid[3]];


		//if it is a en passant move a pawn must be destroyed
		if ((c_board[move_grid[0]][move_grid[3]] != NULL) &&
			(c_board[move_grid[0]][move_grid[1]]->get_color() != 
				c_board[move_grid[0]][move_grid[3]]->get_color()))
		{
			if ((c_board[move_grid[0]][move_grid[1]]->get_id() < 169) &&
				(c_board[move_grid[0]][move_grid[1]]->get_id() > 160) &&
				(c_board[move_grid[0]][move_grid[3]]->get_id() < 269) &&
				(c_board[move_grid[0]][move_grid[3]]->get_id() > 260))
			{
				if (c_board[move_grid[0]][move_grid[3]]->p_en_passant == true)
				{
					c_board[move_grid[0]][move_grid[3]] = NULL;
					en_passant_test = true;
				}
				else
				{
					cerr << "you can't realise an attack en passant\n";
					return false;
				}
			}

			if ((c_board[move_grid[0]][move_grid[1]]->get_id() < 269) &&
				(c_board[move_grid[0]][move_grid[1]]->get_id() > 260) &&
				(c_board[move_grid[0]][move_grid[3]]->get_id() < 169) &&
				(c_board[move_grid[0]][move_grid[3]]->get_id() > 160))
			{
				if (c_board[move_grid[0]][move_grid[3]]->p_en_passant == true)
				{
					c_board[move_grid[0]][move_grid[3]] = NULL;
					en_passant_test = true;
				}
				else
				{
					cerr << "you can't realise an attack en passant\n";
					return false;
				}
			}			
		}

		c_board[move_grid[2]][move_grid[3]] = src_ptr;
		c_board[move_grid[0]][move_grid[1]] = NULL; 
		


		//tmpc and tmpl are the coordinates of the king
		int tmpl = 0;
		int tmpc = 0;

		//here we seek the king of the moving team
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{	
				if ((c_board[i][j] != NULL) && 
					(c_board[i][j]->get_color() == color))
				{
					if ((c_board[i][j]->get_id() == 150) || 
						(c_board[i][j]->get_id() == 250))
					{
						tmpl = i;
						tmpc = j;
					}
				
				}
			
			}
		}

		//here we make a new save of the game.
		for (int k = 0; k < 8; k++)
		{
			for (int l = 0; l < 8; l++)
			{
				if (c_board[k][l] == NULL)
				{
					game_state[k][l] = 'n';
				}
				else
				{
					if (c_board[k][l]->get_color() == 'b')
					{
						game_state[k][l] = 'b';
					}

					if (c_board[k][l]->get_color() == 'w')
					{
						game_state[k][l] = 'w';
					}
				}
			}
		}

		for (int k = 0; k < 8 + 1; k++)
		{	
			game_state2[k] = & (game_state[k][0]);
		}



		//here we seek the enemy pieces, and we move them one by one on the king's location. if it is possible then the king is in danger and the movement is invalid :
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((c_board[i][j] != NULL) &&
					(c_board[i][j]->get_color() != color))
				{
					
					int move_tmp[4] = {i,j,tmpl,tmpc};

					if (c_board[i][j]->move(move_tmp,
										 	game_state2,
										 	false) == true)
					{
			
						c_board[move_grid[0]][move_grid[1]] = src_ptr;
						c_board[move_grid[2]][move_grid[3]] = dest_ptr;

						if (en_passant_test)
						{
							c_board[move_grid[0]][move_grid[3]] = 				en_passant_ptr;
						}

						cast = j + 97;
						cerr << "your king is in danger due to the piece in : " << i + 1 << ", " << cast << "\n";
						return false;
					}
					
				}
				
			}
			
		}
		

		//here the movement is completed by freing the allocated space on the destination square.
		delete dest_ptr;
		if (en_passant_test)
		{
			delete en_passant_ptr;
		}
		
		return true;
	}
	else
	{
		return false;
	}
	
}


/**
 * @brief To realise a move "en passant", the concerned piece needs
 * to be in a certain "state". This function handles this state for the
 * white team
 */
void Chessboard::deactivate_en_passant_white()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if ((c_board[i][j] != NULL) && 
				(c_board[i][j]->get_id() < 169) &&
				(c_board[i][j]->get_id() > 160))
			{
				c_board[i][j]->p_en_passant = false;
			}
			
		}
		
	}
	
}


/**
 * @brief To realise a move "en passant", the concerned piece needs
 * to be in a certain "state". This function handles this state for the
 * black team
 */
void Chessboard::deactivate_en_passant_black()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if ((c_board[i][j] != NULL) && 
				(c_board[i][j]->get_id() < 269) &&
				(c_board[i][j]->get_id() > 260))
			{
				c_board[i][j]->p_en_passant = false;
			}
			
		}
		
	}
	
}

