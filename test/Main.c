#include "Prototype.h"

int main(int argc, char* argv[])
{
	int go;

	// Initialisation de la SDL
	init("JEU DE PLATEFORME");

	// Chargement des ressources (graphismes, sons)
	loadGame();

	// Appelle la fonction cleanup à la fin du programme
	atexit(cleanup);

	go = 1;

	// Boucle infinie, principale, du jeu
	while (go == 1)
	{
		//On dessine tout
		drawGame();
	}

	// On quitte
	exit(0);

}