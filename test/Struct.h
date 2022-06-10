#pragma once

// 
#ifndef DEF_STRUCTS
#define DEF_STRUCTS

// Include .h
#include "defs.h"

// Structure pour gérer la map à afficher 
typedef struct Map
{
	SDL_Texture* background;
	SDL_Texture* tileSet, * tileSetB;

	//Numéro du tileset à utiliser
	int tilesetAffiche;

	/* Coordonnées de départ du héros, lorsqu'il commence le niveau */
	int beginx, beginy;

	/* Coordonnées de début, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonnées max de fin de la map */
	int maxX, maxY;

	/* Tableau à double dimension représentant la map de tiles */
	int tile[MAX_MAP_Y][MAX_MAP_X];

	//Deuxième couche de tiles
	int tile2[MAX_MAP_Y][MAX_MAP_X];

	//Troisième couche de tiles
	int tile3[MAX_MAP_Y][MAX_MAP_X];

	/* Timer et numéro du tileset à afficher pour animer la map */
	int mapTimer, tileSetNumber;

} Map;

#endif