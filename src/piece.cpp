#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>

using namespace std;

Piece::Piece(std::string name, int id, char color, bool first_move = true, 
					bool en_passant = false):
		p_name(name), p_id(id), p_color(color), p_first_move(first_move), 
		p_en_passant(en_passant)
	{}

Piece::~Piece() {}


int Piece::get_id() const
{
	return p_id;
}


char Piece::get_color() const
{
	return p_color;
}


std::string Piece::get_name() const
{
	return p_name;
}


bool Piece::get_first_move() const
{
	return p_first_move;
}




Pawn::Pawn(std::string name, int id, char color, bool first_move = true,
				bool en_passant = false):
		Piece(name, id, color, first_move, en_passant)
	{}

Pawn::~Pawn() {}


bool Pawn::move(int * move_grid, char ** game_state, bool err_report)
{	
	int tmp = 0;
	int tmpc = 0;
	tmp = move_grid[2] - move_grid[0];
	tmpc = move_grid[1] - move_grid[3];
	
	if (game_state[move_grid[0]][move_grid[1]] == 'w')
	{
		if (tmp < 0)
		{
			if (err_report)
			{
				cerr << "Pawns can't go back\n";
			}
			
			return false;
		}
	}

	if (game_state[move_grid[0]][move_grid[1]] == 'b')
	{
		if (tmp > 0)
		{
			if (err_report)
			{
				cerr << "Pawns can't go back\n";
			}
			
			return false;
		}
	}


	if ((abs(tmp) == 2) && (p_first_move == true))
	{
		if (move_grid[1] != move_grid[3])
		{
			if (err_report)
			{
				cerr << "Pawns can't change their column when they move 2 tiles\n";
			}
			
			return false;
		}


		if ((game_state[move_grid[2] - 1][move_grid[3]] != 'n') &&
				(game_state[move_grid[0]][move_grid[3]] == 'w'))
		{
			if (err_report)
			{
				cerr << "Pawns can't attack what is in front of them 1\n";
			}
			
			return false;
		}

		if ((game_state[move_grid[2] + 1][move_grid[3]] != 'n') &&
				(game_state[move_grid[0]][move_grid[3]] == 'b'))
		{
			if (err_report)
			{
				cerr << "Pawns can't attack what is in front of them 2\n";
			}
			
			return false;
		}


		if (game_state[move_grid[2]][move_grid[3]] != 'n')
		{
			if (err_report)
			{
				cerr << "Pawns can't attack what is in front of them 3\n";
			}
			
			return false;
		}
		
		p_en_passant = true;
		p_first_move = false;

		return true;
	}

	if ((abs(tmp) == 1))
	{

		if (tmpc != 0)
		{
			
			//here it may be possible that the user is trying to take a pawn en passant
			if ((abs(tmpc) == 1) && 
				(game_state[move_grid[2]][move_grid[3]] == 'n'))
			{

				if ((game_state[move_grid[0]][move_grid[3]] != 'n') &&
					(game_state[move_grid[0]][move_grid[3]] != 
						game_state[move_grid[0]][move_grid[1]]))
				{
					if ((game_state[move_grid[0]][move_grid[1]] == 'b') 
						&&
						(tmp == -1))
					{
						return true;
					}

					if ((game_state[move_grid[0]][move_grid[1]] == 'w') 
						&&
						(tmp == 1))
					{
						return true;
					}
					
				}

				if (err_report)
				{
					cerr << "Pawns can't change their column if they don't attack or try a en passant\n";
				}		
			}

			//here are the test for a regular pawn attack
			if ((abs(tmpc) == 1) && 
				(game_state[move_grid[2]][move_grid[3]] != 'n'))
			{
				return true;
			}

			if (err_report)
			{
				cerr << "Pawns can't change their column if they don't attack\n";
			}
			
			return false;
		}
		else
		{
			if (game_state[move_grid[2]][move_grid[3]] != 'n')
			{
				if (err_report)
				{
					cerr << "Pawns can't attack what is in front of them\n";
				}
				
				return false;
			}
		}

		p_first_move = false;

		return true;
	}

	if ((abs(tmp) == 2) && (p_first_move == false))
	{
		if (err_report)
		{
			cerr << "Pawns moves twice only during their first movement\n";
		}
		
		return false;
	}
	
	if (err_report)
	{
		cerr << "I don't know what you've done, but it is a wrong move\n";
	}
	
	return false;
}




Rook::Rook(std::string name, int id, char color, bool first_move = true,
					bool en_passant = true):
		Piece(name, id, color, first_move, en_passant)
	{}

Rook::~Rook() {}


bool Rook::move(int * move_grid,  char ** game_state, bool err_report)
{

	int i = 0;

	if ((move_grid[0] != move_grid[2]) && (move_grid[1] != move_grid[3]))
	{

		if (err_report)
		{
			cerr << "Wrong move, rook only moves in lines.\n";
		}	

		return false;
	} 
	else
	{

		if (move_grid[0] < move_grid[2])
		{
			i = move_grid[0] + 1;

			while (i < move_grid[2])
			{
				if (game_state[i][move_grid[1]] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}	
					
					return false;
				}
				i++;
			}
		}
		else
		{
			i = move_grid[0] - 1;

			while (i > move_grid[2])
			{
				if (game_state[i][move_grid[1]] != 'n')
				{

					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}	
					
					return false;
				}
				i--;
			}
		}
		

		if (move_grid[1] <= move_grid[3])
		{
			i = move_grid[1] + 1;

			while (i < move_grid[3])
			{
				if (game_state[move_grid[0]][i] != 'n')
				{

					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}	
					
					return false;
				}
				i++;
			}
		}
		else
		{
			i = move_grid[1] - 1;

			while (i > move_grid[3])
			{
				if (game_state[move_grid[0]][i] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}	

					
					return false;
				}
				i--;
			}
		}

	p_first_move = false;

	return true;	
		
	}
}



King::King(std::string name, int id, char color, bool first_move = true,
					bool en_passant = true):
		Piece(name, id, color, first_move, en_passant)
	{}

King::~King() {}


bool King::move(int * move_grid,  char ** game_state, bool err_report)
{
	int tmp1 = 0;
	int tmp2 = 0;

	tmp1 = move_grid[0] - move_grid[2];
	tmp2 = move_grid[1] - move_grid[3];
	if ((abs(tmp1) > 1) || (abs(tmp2) > 1))
	{
		if (err_report)
		{
			cerr << "Wong move, kings can move up to 1 tiles\n";
		}	
		
		return false;
	} 
	else
	{
		if (game_state[move_grid[0]][move_grid[1]] == 
				game_state[move_grid[2]][move_grid[3]])
		{

			if (err_report)
			{
				cerr << "you can't attack one of your pieces\n";
			}	
			
			return false;
		}
		
		p_first_move = false;

		return true;
	}
	
}




Queen::Queen(std::string name, int id, char color, bool first_move = true,
					bool en_passant = true):
		Piece(name, id, color, first_move, en_passant)
	{}

Queen::~Queen() {}

bool Queen::move(int * move_grid, char ** game_state, bool err_report)
{
	int tmp1 = 0;
	int tmp2 = 0;

	int i = 0;
	int j = 0;

	if (move_grid[1] == move_grid[3])
	{
		if (move_grid[0] < move_grid[2])
		{
			i = move_grid[0] + 1;

			while (i < move_grid[2])
			{
				if (game_state[i][move_grid[1]] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 1\n";
					}
					
					return false;
				}
				i++;
			}
		}
		else
		{
			i = move_grid[0] - 1;

			while (i > move_grid[2])
			{
				if (game_state[i][move_grid[1]] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 2\n";
					}
					
					return false;
				}

				i--;
			}
		}

		p_first_move = false;

		return true;
	}


	if (move_grid[0] == move_grid[2])
	{
		
		if (move_grid[1] < move_grid[3])
		{
			i = move_grid[1] + 1;

			while (i < move_grid[3])
			{
				if (game_state[move_grid[0]][i] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 3\n";
					}
					
					return false;
				}

				i++;
			}
		}
		else
		{
			i = move_grid[1] - 1;

			while (i > move_grid[3])
			{
				if (game_state[move_grid[0]][i] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 4\n";
					}
					
					return false;
				}

				i--;
			}
		}

		p_first_move = false;

		return true;
	}

	tmp1 = move_grid[0] - move_grid[2];
	tmp2 = move_grid[1] - move_grid[3];

	if (abs(tmp1) == abs(tmp2))
	{

		if ((move_grid[0] <= move_grid[2]) && (move_grid[1] <= move_grid[3]))
		{
			i = move_grid[0] + 1;
			j = move_grid[1] + 1;

			while ((i < move_grid[2]) && (j < move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 5\n";
					}
					
					return false;
				}
				i++;
				j++;
			}
		}


		if ((move_grid[0] > move_grid[2]) && (move_grid[1] <= move_grid[3]))
		{
			i = move_grid[0] - 1;
			j = move_grid[1] + 1;

			while ((i > move_grid[2]) && (j < move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{

					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 6\n";
					}
					
					return false;
				}
				i--;
				j++;
			}
		}


		if ((move_grid[0] <= move_grid[2]) && (move_grid[1] > move_grid[3]))
		{
			i = move_grid[0] + 1;
			j = move_grid[1] - 1;

			while ((i < move_grid[2]) && (j > move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 7\n";
					}
					
					return false;
				}
				i++;
				j--;
			}
		}


		if ((move_grid[0] > move_grid[2]) && (move_grid[1] > move_grid[3]))
		{
			i = move_grid[0] - 1;
			j = move_grid[1] - 1;

			while ((i > move_grid[2]) && (j > move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{

					if (err_report)
					{
						cerr << "this piece can't jump over other pieces 8\n";
					}
					
					return false;
				}
				i--;
				j--;
			}
		}

		p_first_move = false;

		return true;
	}

	if (err_report)
	{
		cerr << "I don't know what you've done but it's a wrong move.\n";
	}
	
	return false;
}



Bishop::Bishop(std::string name, int id, char color, bool first_move = true,
						bool en_passant = true):
		Piece(name, id, color, first_move, en_passant)
	{}

Bishop::~Bishop() {}

bool Bishop::move(int * move_grid, char ** game_state, bool err_report)
{

	int tmp1 = 0;
	int tmp2 = 0;

	int i = 0;
	int j = 0;


	tmp1 = move_grid[0] - move_grid[2];
	tmp2 = move_grid[1] - move_grid[3];


	if (abs(tmp1) != abs(tmp2))
	{
		if (err_report)
		{
			cerr << "Wrong move, bishops can only move diagonally.\n";
		}
		
		return false;
	}
	else
	{
		

		if ((move_grid[0] < move_grid[2]) && (move_grid[1] < move_grid[3]))
		{
			i = move_grid[0] + 1;
			j = move_grid[1] + 1;

			while ((i < move_grid[2]) && (j < move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}
					
					return false;
				}
				i++;
				j++;
			}
		}


		if ((move_grid[0] > move_grid[2]) && (move_grid[1] < move_grid[3]))
		{
			i = move_grid[0] - 1;
			j = move_grid[1] + 1;

			while ((i > move_grid[2]) && (j < move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}
					
					return false;
				}
				i--;
				j++;
			}
		}


		if ((move_grid[0] < move_grid[2]) && (move_grid[1] > move_grid[3]))
		{
			i = move_grid[0] + 1;
			j = move_grid[1] - 1;

			while ((i < move_grid[2]) && (j > move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}
					
					return false;
				}
				i++;
				j--;
			}
		}


		if ((move_grid[0] > move_grid[2]) && (move_grid[1] > move_grid[3]))
		{
			i = move_grid[0] - 1;
			j = move_grid[1] - 1;

			while ((i > move_grid[2]) && (j > move_grid[3]))
			{
				if (game_state[i][j] != 'n')
				{
					if (err_report)
					{
						cerr << "this piece can't jump over other pieces\n";
					}
					
					return false;
				}
				i--;
				j--;
			}
		}

		p_first_move = false;

		return true;
	}

	if (err_report)
	{
		cerr << "I don't know what you've done but it's a wrong move.\n";
	}
	
	return false;
}




Knight::Knight(std::string name, int id, char color, bool first_move = true,
					bool en_passant = true):
		Piece(name, id, color, first_move, en_passant)
	{}

Knight::~Knight(){}


bool Knight::move(int * move_grid, char ** game_state, bool err_report)
{
	int tmpl = 0;
	int tmpc = 0;


	tmpl = move_grid[0] - move_grid[2];
	tmpc = move_grid[1] - move_grid[3];


	switch (abs(tmpc))
	{
	case 1 :

		if (abs(tmpl) != 2)
		{
			if (err_report)
			{
				cerr << "Wrong move, a knight can only move in circle\n";
			}
			
			return false;
		}
	
		break;
	
	case 2 :

		if (abs(tmpl) != 1)
		{
			if (err_report)
			{
				cerr << "Wrong move, a knight can only move in circle\n";
			}
			
			return false;
		}

		break;
	
	default:

		if (err_report)
		{
			cerr << "I don't know what you've done but it is a wrong move\n";
		}
		
		return false;
	
	}


	if (game_state[move_grid[0]][move_grid[1]] == 
			game_state[move_grid[2]][move_grid[3]])
	{
		if (err_report)
		{
			cerr << "you can't attack one of your pieces\n";
		}
		
		return false;
	}

	p_first_move = false;
	
	return true;
}