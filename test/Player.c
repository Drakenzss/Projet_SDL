// Include .h
#include "Prototype.h"

// Variable qui g�re les niveaux
int level; 






/***************************************************************
BUT : G�rer les niveaux

ENTREE : /

SORTIE : /

DESCRIPTION : Cette fonction va g�rer les diff�rents niveaux
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
* DESCRIPTION : Va servire � set les niveaux
**********************************************************************/
void SetValeurDuNiveau(int valeur)
{
	level = valeur;
}