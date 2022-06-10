#pragma once

// 
#ifndef DEF_STRUCTS
#define DEF_STRUCTS

// Include .h
#include "defs.h"

// Structure pour g�rer la map � afficher 
typedef struct Map
{
	SDL_Texture* background;
	SDL_Texture* tileSet, * tileSetB;

	//Num�ro du tileset � utiliser
	int tilesetAffiche;

	/* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
	int beginx, beginy;

	/* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonn�es max de fin de la map */
	int maxX, maxY;

	/* Tableau � double dimension repr�sentant la map de tiles */
	int tile[MAX_MAP_Y][MAX_MAP_X];

	//Deuxi�me couche de tiles
	int tile2[MAX_MAP_Y][MAX_MAP_X];

	//Troisi�me couche de tiles
	int tile3[MAX_MAP_Y][MAX_MAP_X];

	/* Timer et num�ro du tileset � afficher pour animer la map */
	int mapTimer, tileSetNumber;

} Map;

#endif