#include "game.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <stdlib.h>

#define SIZE 10
#define SIZE_C 2048
#define SIZE_CPY 5

using namespace std;






/**
 * @brief read the file where the commands are stored
 *
 * The file needs to be well formated; a 4 coordonates command per line,
 * for instance : a1b3. The last command is /quit. The commands are stored
 * in a dinamically allocated array given by the user (no need to allocate the
 * subs array of the matrix). To castle the king you can use the O-O for the 
 * kingside and O-O-O for the queenside.
 * 
 * @param argv the name of the file containing the commands
 * @param command an array that needs t be dynamically allocated by the user
 * @result the number of line read in the file as an int
 */
int read_file(const char * argv, char ** command)
{
	FILE * in = fopen(argv, "r");
	char buffer[SIZE];
	int count = 0;

	while (fgets(buffer,SIZE,in) != NULL)
	{		
		buffer[5] = '\0';

		
		command[count] = (char *)malloc(sizeof(**command) * SIZE);

		if (strncmp(buffer,"O-O-O",5) == 0)
		{
			strncpy(command[count], "RRRR", SIZE_CPY);
		}
		else if (strncmp(buffer,"O-O",3) == 0)
		{
			strncpy(command[count], "rrrr", SIZE_CPY);
		}
		else
		{
			strncpy(command[count], buffer, SIZE_CPY);
			command[count][4] = '\0';
		}

		count++;
	}

	fclose(in);

	return count;
}






/**
 * @brief main function of the program
 *
 * If an argument is given it needs to be the name of the file containing the
 * command lines. Then the function read the file an execute each command in
 * order. If a command is invalid, it is skipped.
 * If there is no argument, then the function will require a command from
 * both players, starting with the white one. If a command is invalid, it is
 * ignored an a new command is required from the user (that was mistaken) until
 * a valid command is given.
 * 
 * @param argc the number of arguments given when launching the executable
 * @param argv the array containing the arguments as strings
 * @result if everything went well 0 is returned
 */
int main(int argc, char const *argv[])
{
	bool legal1 = false;
	bool legal2 = false;

	int count = 0;
	int num_command = 0;
	int who_play = 0;

	int tab[4] = {-999,-999,-999,-999};

	char buffer[SIZE];
	char ** command = (char **)malloc(sizeof(*command) * SIZE_C);

/*
	Player player_test_b = Player('b', "Anakin", 1);
	Player player_test_w = Player('w', "Obi Wan", 2);
	*/
	Chessboard board_test = Chessboard();


	if (argc > 2)
	{
		cerr << "too many arguments\n";
		exit(EXIT_FAILURE);
	}


	if (argc == 2)
	{

		num_command = read_file(argv[1], command);
		
		board_test.print_board();



		while (count < num_command)
		{

			cout << "######################### move number : " << count << "\n";
			cout << command[count] << "\n";

			if (strncmp(command[count],"/qui",4) == 0)
			{
				if (who_play == 0)
				{
					cout << "The white player surrendered,"
						<< "the black player is victorious\n";
					return 0;
				}

				if (who_play == 1)
				{
					cout << "The black player surrendered,"
						<< "the white player is victorious\n";
					return 0;
				}
				
			}
			

			if (who_play == 0)
			{

				if (board_test.is_that_legal(command[count], tab, 'w'))
				{
					if (board_test.move_pieces(tab))
					{
						who_play = 1;
					}
				}

				board_test.deactivate_en_passant_black();
			}
			else
			{

				if (board_test.is_that_legal(command[count], tab, 'b'))
				{
					if (board_test.move_pieces(tab))
					{
						who_play = 0;
					}
				}

				board_test.deactivate_en_passant_white();
			}

			board_test.print_board();

			count++;
				
		}
	

		for (int i = 0; i < num_command; i++)
		{
			free(command[i]);
		}

		//The purpose here is to allow the user to continue the game if the entire file has been read.
		argc = 1;
		
	}
	






	if (argc == 1)	
	{

		board_test.print_board();

		while (true)
		{
			int end = 0;

			if (who_play == 0)
			{			

			cout << "################ tour : " << count << "\n";
			cout << "the white player needs to give a command\n";


			legal1 = false;
			legal2 = false;
			
			while (legal1 == false || legal2 == false)
			{
			
				if (fgets(buffer, SIZE, stdin) != NULL)
				{
					end = 0;
					while (buffer[end] != '\n')
					{
						end++;
					}
					buffer[end] = '\0';

					if (strncmp(buffer, "/quit", SIZE) == 0)
					{
						cout << "the white player surrendered \n";
						exit(EXIT_SUCCESS);
					}

					//These conditions are here to check if the player wants to castle his king.

					if (strncmp(buffer, "O-O", SIZE) == 0)
					{
						buffer[0] = 'r';
						buffer[1] = 'r';
						buffer[2] = 'r';
						buffer[3] = 'r';
					}
					
					if (strncmp(buffer, "O-O-O", SIZE) == 0)
					{
						buffer[0] = 'R';
						buffer[1] = 'R';
						buffer[2] = 'R';
						buffer[3] = 'R';
					}											
				

					legal1 = board_test.is_that_legal(buffer, tab, 'w');
					if (legal1 == true)
					{
						legal2 = board_test.move_pieces(tab);
					}
					board_test.print_board();	

				}
				else
				{
					fprintf(stderr,"error fgets, white player\n");
					exit(EXIT_FAILURE);
				}

				if (legal1 == false || legal2 == false)
				{
					cerr << "Wrong command, give a new one.\n";
				}

			}

			who_play = 1;

			}


			
			if (who_play == 1)
			{			

			cout << "################ tour : " << count << "\n";
			cout << "the black player needs to give a command\n";


			legal1 = false;
			legal2 = false;

			while (legal1 == false || legal2 == false)
			{

				end = 0;
				if (fgets(buffer, SIZE, stdin) != NULL)
				{

					while (buffer[end] != '\n')
					{
						end++;
					}
					buffer[end] = '\0';

					if (strncmp(buffer, "/quit", SIZE) == 0)
					{
						cout << "the black player surrendered \n";
						exit(EXIT_SUCCESS);
					}
				
					//These conditions are here to check if the player wants to castle his king.

					if (strncmp(buffer, "O-O", SIZE) == 0)
					{
						buffer[0] = 'r';
						buffer[1] = 'r';
						buffer[2] = 'r';
						buffer[3] = 'r';
					}	

					if (strncmp(buffer, "O-O-O", SIZE) == 0)
					{
						buffer[0] = 'R';
						buffer[1] = 'R';
						buffer[2] = 'R';
						buffer[3] = 'R';
					}	

					legal1 = board_test.is_that_legal(buffer, tab, 'b');
					if (legal1 == true)
					{
						legal2 = board_test.move_pieces(tab);
					}
					board_test.print_board();	

				}
				else
				{
					fprintf(stderr,"error fgets, black player\n");
					exit(EXIT_FAILURE);
				}


				if (legal1 == false || legal2 == false)
				{
					cerr << "Wrong command, give a new one.\n";
				}

			}

			who_play = 0;

			}
			
		}
		
	}
	
	
	free(command);

	return 0;
}




