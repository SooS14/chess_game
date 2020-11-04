# chess_game

done in 2019-2020

rules :

compile the program using make where Makefile is located
launch the binary file in /bin   (a filename can be given to start a game which was saved)

The white player starts the game by entering the coordinates of a position on the grid (example : a2a4 to move a white pawn) 
Then the black player needs to play

O-O    : to castle kingside (short)
O-O-O  : to castle queenside (long)
/quit  : to surrender
mate   : if the current player can't move it's king it can use "mate". The game checks if the king is trapped, if that's the case, the game ends. Else, a possible position if given


1.	The program is separated into different folders (src for .c files; include for .h ...). To launch the compilation, stay in the main directory and run the "make" command in the terminal. A "bin" directory is created in which the "chess" executable is located. There is no checkmate.


2. 	The files piece.h and piece.cpp contain all the classes and methods related to the mechanics of the parts. A generic class named "Piece" has been created. It has a virtual method "move" which is used with a different implementation by each of the parts.
	 The files game.h and game.cpp define the methods that work on the chessboard in a general way. The 2 most important functions are: "is_that_legal" and "move_pieces" which are in charge of checking the validity of a move and proceeding to its realization.
	The chess file chess.cpp contains the functions "hand" which manages the game in a general way as well as functions necessary to the management of the file containing the commands.


3.	It is good to know that the program accepts commands passed through a text file (formatted according to the examples given in the topic), but if the /quit command is not given, the user can continue the game by entering the commands into the terminal.



##########################################



# Jeu d'échecs

fait en 2019-2020

1.	Le programme est séparé en différent dossiers (src pour les fichiers .c ; include pour les .h ...). Pour lancer la compilation, se rester dans le répertoire général et lancer dans le terminal la commande "make". Un répertoire "bin" est créé dans lequel se trouve l'éxécutable "chess". L'échecs et mat n'a pas été implémenté.

2. 	Les fichiers piece.h et piece.cpp contiennent toutes les classes et methodes relatives aux mécaniques des pieces. Une classe générique dénommé "Piece" a été créée. Elle possède une méthode virtuelle "move" qui est utilisée avec une implémentation différente par chacune des pièces.
	 Les fichiers game.h et game.cpp quant à eux définissent des méthodes dont le fonctionnement concerne l'échiquier de manière générale. Les 2 fonctions les plus importantes sont : "is_that_legal" et "move_pieces" qui sont chargées de vérifier la validité d'un mouvement et de procéder à sa réalisation.
	Le fichier chess.cpp contient la fonctions "main" qui gère le jeu de manière générale ainsi que des fonctions nécessaires à la gestion du fichier contenant les commandes.

3.	Il est bon de savoir que le programme accepte les commandes passés par un fichiers texte (formatées selon les exemples donnés dans le sujet), mais si la commande /quit n'est pas donnée, l'utilisateur peut continuer la partie en rentrant les commandes dans le terminal.




###### à faire : checkmate - fichier pour sauvegarder une partie en cours - meilleur readme

###### à voir
	J'ai essayé tous les fichiers donnés en test et le programme donne bien le résultat attendu. Néanmoins, lorsque j'utilise le script shell "test-level.sh" j'ai l'impression que le script utilise un autre éxécutable "chess" que celui désiré. Je n'ai pas trouvé l'origine du problème même en faisant attention aux chemin relatifs. Ainsi, "test-level.sh" est à utiliser avec précaution puisqu'il donne les résultats relatif à une ancienne version de mon programme (qui avait des problème avec la grande roque notamment). Je ne vois pas d'où est venu le problème.
