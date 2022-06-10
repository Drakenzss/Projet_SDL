#include "Prototype.h"

/*********************************************************************
* BUT : Affiche le jeu
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Affichage du jeu avec les layers
*********************************************************************/
void drawGame(void)
{
    // Affiche le fond (background) aux coordonnées (0,0)
    drawImage(getBackground(), 0, 0);

    // Affiche la map de tiles : layer 2 ( background )
    drawMap(2);

    // Affiche la map de tiles : layer 1 ( couche active : sol, etc )
    drawMap(1);

    // Affiche la map de tiles : layer 3 ( couche en foreground / devant )
   drawMap(3);

    // Affiche l'écran
    SDL_RenderPresent(getrenderer());
}

/********************************************************************
* BUT : Charge l'image
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : transforme l'image en surface puis en  texture 
********************************************************************/
SDL_Texture* loadImage(char* name)
{
    // Charge les images avec SDL Image dans une SDL_Surface

    SDL_Surface* loadedImage = NULL;
    SDL_Texture* texture = NULL;
    loadedImage = IMG_Load(name);

    if (loadedImage != NULL)
    {
        // Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);

        // On se débarrasse du pointeur vers une surface
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
    }
    else
        printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());

    return texture;

}

/*************************************************************************
* BUT : Dessiner l'image
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Placer l'image sur le découpage 
*************************************************************************/
void drawImage(SDL_Texture* image, int x, int y)
{
    SDL_Rect dest;

    // Règle le rectangle à dessiner selon la taille de l'image source
    dest.x = x;
    dest.y = y;

    // Dessine l'image entière sur l'écran aux coordonnées x et y
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(getrenderer(), image, NULL, &dest);
}

/*************************************************************************
* BUT : Dessiner les tiles
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Découpe les tiles pour les placées sur la matrice 
*************************************************************************/
void drawTile(SDL_Texture* image, int destx, int desty, int srcx, int srcy)
{
    // Rectangle de destination à dessiner
    SDL_Rect dest;

    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;

    // Rectangle source
    SDL_Rect src;

    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    // Dessine la tile choisie sur l'écran aux coordonnées x et y
    SDL_RenderCopy(getrenderer(), image, &src, &dest);
}