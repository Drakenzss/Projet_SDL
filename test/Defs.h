#pragma once

#ifndef DEF_DEFS
#define DEF_DEFS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



/* On inclut les libs suppl�mentaires */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Taille de la fen�tre : 800x480 pixels 
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480



/* Taille maxi de la map : 400 x 150 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 150

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32


#endif