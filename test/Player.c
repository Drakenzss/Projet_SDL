// Include .h
#include "Prototype.h"

// Variable qui gère les niveaux
int level; 






/***************************************************************
BUT : Gérer les niveaux

ENTREE : /

SORTIE : /

DESCRIPTION : Cette fonction va gérer les différents niveaux
***************************************************************/
int getLevel(void) 
{
	return level;
}

/**********************************************************************
* BUT : Set le niveau
* 
* ENTREE : /
* 
* SORTIE : /
* 
* DESCRIPTION : Va servire à set les niveaux
**********************************************************************/
void SetValeurDuNiveau(int valeur)
{
	level = valeur;
}