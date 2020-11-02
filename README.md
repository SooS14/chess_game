
1.	Le programme est séparé en différent dossiers (src pour les fichiers .c ; include pour les .h ...). Pour lancer la compilation, se placer dans le répertoire jeu_d_echec et lancer dans le terminal la commande "make". Un répertoire "bin" est créé dans lequel se trouve l'éxécutable "echecs". Dans le projet, tout le travail obligatoire a été réalisé (jusqu'au niveau 6).

2. 	Les fichiers piece.h et piece.cpp contiennent toutes les classes et methodes relatives aux mécaniques des pieces. Une classe générique dénommé "Piece" a été créée. Elle possède une méthode virtuelle "move" qui est utilisée avec une implémentation différente par chacune des pièces.
	 Les fichiers game.h et game.cpp quant à eux définissent des méthodes dont le fonctionnement concerne l'échiquier de manière générale. Les 2 fonctions les plus importantes sont : "is_that_legal" et "move_pieces" qui sont chargées de vérifier la validité d'un mouvement et de procéder à sa réalisation.
	Le fichier echecs.cpp contient la fonctions "main" qui gère le jeu de manière générale ainsi que des fonctions nécessaires à la gestion du fichier contenant les commandes.

3.	Il est bon de savoir que le programme accepte les commandes passés par un fichiers texte (formatées selon les exemples donnés dans le sujet), mais si la commande /quit n'est pas donnée, l'utilisateur peut continuer la partie en rentrant les commandes dans le terminal.
	J'ai essayé tous les fichiers donnés en test et le programme donne bien le résultat attendu. Néanmoins, lorsque j'utilise le script shell "test-level.sh" j'ai l'impression que le script utilise un autre éxécutable "echecs" que celui désiré. Je n'ai pas trouvé l'origine du problème même en faisant attention aux chemin relatifs. Ainsi, "test-level.sh" est à utiliser avec précaution puisqu'il donne les résultats relatif à une ancienne version de mon programme (qui avait des problème avec la grande roque notamment). Je ne vois pas d'où est venu le problème.
