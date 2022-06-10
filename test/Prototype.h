#pragma once


#ifndef PROTOTYPES
#define PROTOTYPES

#include "Struct.h"

// Prototypes des fonctions

extern void changeLevel();
extern void cleanMaps();
extern void cleanup();
extern void drawGame();
extern void drawImage(SDL_Texture*, int, int);
extern void drawMap(int);
extern void drawTile(SDL_Texture* image, int destx, int desty, int srcx, int srcy);
extern SDL_Texture* getBackground();
extern int getLevel();
extern SDL_Renderer* getrenderer();
extern void init(char*);
extern void initMaps();
extern void loadGame();
extern SDL_Texture* loadImage(char* name);
extern void loadMap(char* name);
extern void SetValeurDuNiveau(int valeur);
void clean_ressources(SDL_Window*, SDL_Renderer*, SDL_Texture*);


#endif
