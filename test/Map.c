// Include .h
#include "Prototype.h"

// Pointeur de la structure map en global pour l'utilis� de toutes les fonctions qui se trouve dans ce .C
// Global
Map map;

/***********************************************************************
* BUT : Initialisation de la map
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Sert � charger une image pour initialis� la SDL
***********************************************************************/
void initMaps(void)
{
	// Charge l'image du fond (background)
	map.background = loadImage("./image/background.png");

	// On initialise le timer
	map.tileSetNumber = 0;
}

/***********************************************************************************
* BUT : retourner le background
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : renvoie simplement la texture du background.
Elle sera pratique pour pouvoir r�cup�rer cette variable depuis un autre fichier
*
************************************************************************************/
SDL_Texture* getBackground()
{
	// Retourne le champs de la texture map
	return map.background;
}

/****************************************************************************************************************
* BUT : Nettoie la map
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : fait le m�nage � la fin du programme en supprimant de la m�moire notre fichier map.background
****************************************************************************************************************/
void cleanMaps(void)
{
	// Lib�re la texture du background
	if (map.background != NULL)
	{
		// D�truit la texture si elle est charg�
		SDL_DestroyTexture(map.background);

		// Remet en NULL le pointeur
		map.background = NULL;
	}

	// Lib�re les textures des tilesets
	if (map.tileSet != NULL)
	{
		// D�truit les tileset si elle est charg�
		SDL_DestroyTexture(map.tileSet);

		// Remet en NULL le pointeur
		map.tileSet = NULL;
	}
}

/****************************************************************************************
* BUT : Charg�e la map
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Cette fonction va charg� et lire la map venant d'un fichier externe.
* Une fois les tileset lu on les copie dans les tableaux afin de les dessine�es
****************************************************************************************/
void loadMap(char* name)
{
	int x, y;
	FILE* fp; // Interpr�teur de fichier
	errno_t err; // Erreur de fichier

	// Ouvre le fichier en lecture
	if ((err = fopen_s(&fp, name, "rb")) != 0)
	{
		printf("Le fichier map n'a pas pu etre ouvert.\n");
		exit(1);
	}

	// Lit les donn�es du fichier dans la map

	// Lit les coordonn�es de d�but du joueur
	fscanf_s(fp, "%d", &map.beginx);
	fscanf_s(fp, "%d", &map.beginy);

	// Lit le num�ro du tileset
	fscanf_s(fp, "%d", &map.tilesetAffiche);

	map.maxX = map.maxY = 0;


	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			// On lit le num�ro de la tile et on le copie dans notre tableau
			fscanf_s(fp, "%d", &map.tile[y][x]);

			// Permet de d�terminer la taille de la map
			if (map.tile[y][x] > 0)
			{
				if (x > map.maxX)
				{
					map.maxX = x;
				}

				if (y > map.maxY)
				{
					map.maxY = y;
				}
			}
		}
	}

	// Deuxi�me couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			// On lit le num�ro de la tile et on le copie dans notre tableau
			fscanf_s(fp, "%d", &map.tile2[y][x]);
		}
	}

	// Troisi�me couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			// On lit le num�ro de la tile et on le copie dans notre tableau
			fscanf_s(fp, "%d", &map.tile3[y][x]);
		}
	}

	/* maxX et maxY sont les coordonn�es de fin de la map.
	On les trouve d�s qu'il n'y a plus que des z�ros � la suite.
	Comme �a, on peut faire des maps de tailles diff�rentes avec la m�me
	structure de fichier. */
	map.maxX = (map.maxX + 1) * TILE_SIZE;
	map.maxY = (map.maxY + 1) * TILE_SIZE;

	// On referme le fichier
	fclose(fp);
}

/*******************************************************************************************
* BUT : Dessiner la map
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Une fois le fichier lu, on va dessiner ce qui se trouve dans le fichier
* afin de le dessiner sur la matrice
*******************************************************************************************/
void drawMap(int layer)
{

	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

	/* On initialise mapX � la 1�re colonne qu'on doit blitter.
	Celle-ci correspond au x de la map (en pixels) divis�s par la taille d'une tile (32)
	pour obtenir la bonne colonne de notre map
	Exemple : si x du d�but de la map = 1026, on fait 1026 / 32
	et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
	mapX = map.startX / TILE_SIZE;

	/* Coordonn�es de d�part pour l'affichage de la map : permet
	de d�terminer � quels coordonn�es blitter la 1�re colonne de tiles au pixel pr�s
	(par exemple, si la 1�re colonne n'est visible qu'en partie, on devra commencer � blitter
	hors �cran, donc avoir des coordonn�es n�gatives - d'o� le -1). */
	x1 = (map.startX % TILE_SIZE) * -1;

	/* Calcul des coordonn�es de la fin de la map : jusqu'o� doit-on blitter ?
	Logiquement, on doit aller � x1 (d�part) + SCREEN_WIDTH (la largeur de l'�cran).
	Mais si on a commenc� � blitter en dehors de l'�cran la premi�re colonne, il
	va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
	blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
	if(x1 != 0)
	x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forc�ment, c'est plus long ;)*/
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	/* On fait exactement pareil pour calculer y */
	mapY = map.startY / TILE_SIZE;
	y1 = (map.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


	//On met en place un timer pour animer la map (chapitre 19)
	if (map.mapTimer <= 0)
	{
		if (map.tileSetNumber == 0)
		{
			map.tileSetNumber = 1;
		}
		else
		{
			map.tileSetNumber = 0;
		}

	}
	else
		map.mapTimer--;


	/* Dessine la carte en commen�ant par startX et startY */

	/* On dessine ligne par ligne en commen�ant par y1 (0) jusqu'� y2 (480)
	A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
	de tile (qui fait 32 pixels de hauteur) */
	if (layer == 1)
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			/* A chaque d�but de ligne, on r�initialise mapX qui contient la colonne
			(0 au d�but puisqu'on ne scrolle pas) */
			mapX = map.startX / TILE_SIZE;

			/* A chaque colonne de tile, on dessine la bonne tile en allant
			de x = 0 � x = 640 */
			for (x = x1; x < x2; x += TILE_SIZE)
			{

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = map.tile[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (map.tileSetNumber == 0)
					drawTile(map.tileSet, x, y, xsource, ysource);
				else
					drawTile(map.tileSetB, x, y, xsource, ysource);

				mapX++;
			}

			mapY++;
		}
	}

	else if (layer == 2)
	{
		//Deuxi�me couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = map.startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE)
			{

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = map.tile2[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (map.tileSetNumber == 0)
					drawTile(map.tileSet, x, y, xsource, ysource);
				else
					drawTile(map.tileSetB, x, y, xsource, ysource);

				mapX++;
			}

			mapY++;
		}
	}

	else if (layer == 3)
	{
		//Troisi�me couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = map.startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE)
			{

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = map.tile3[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (map.tileSetNumber == 0)
					drawTile(map.tileSet, x, y, xsource, ysource);
				else
					drawTile(map.tileSetB, x, y, xsource, ysource);

				mapX++;
			}

			mapY++;
		}
	}


}

/*****************************************************************
* BUT : Change le niveau
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Affiche le tilemap
*****************************************************************/
void changeLevel(void)
{
	char file[200];

	/* Charge la map depuis le fichier */
	sprintf_s(file, sizeof(file), "./map/map%d.txt", getLevel());
	loadMap(file);

	//Charge le tileset
	if (map.tileSet != NULL)
	{
		SDL_DestroyTexture(map.tileSet);
	}
	if (map.tileSetB != NULL)
	{
		SDL_DestroyTexture(map.tileSetB);
	}

	sprintf_s(file, sizeof(file), "./image/tileset%d.png", map.tilesetAffiche);
	map.tileSet = loadImage(file);

	sprintf_s(file, sizeof(file), "./image/tileset%dB.png", map.tilesetAffiche);
	map.tileSetB = loadImage(file);
}