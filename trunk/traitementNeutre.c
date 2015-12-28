/*
    Fichier : traitementNeutre.c
    Objectif : Definition des types, des structures et des fonctions
    Date de creation : 08/04/2009
    Auteurs : C & F & A
*/

#include <stdio.h>
#include <stdlib.h>
#include "matriceCreuse.h"
#include "traitementNeutre.h"


/*
    Nom Fonction : creationListeNeutre
    Parametre entree :
        * la matrice creuse
    Parametre retourne:
        * la matrice creuse
    Description : 
		Creation du tableau des elements neutres
		et initialisation de toutes les cases a -1
*/
void creationListeNeutre (matriceCreuse *mc)
{
     int i;

     /* On souhaite déclarer le tableau du nombre de variable neutre par clause
     Ainsi ce tableau aura dans le pire des cas le nombre de variable à neutre,
     mais nous allons chercher combien de variable contient la clause la plus 
     grande afin de ne pas declarer inutilement un tableau trop grand */
     int max = mc->cl[1].nbLitNeutres;
     
	/* Parcours de la matrice creuse par clauses */
	for (i = 1; i <= mc->tailleClause; i++)
	{
        mc->cl[i].clauseSuiv = -1 ;
        mc->cl[i].clausePrec = -1 ;
		if ( mc->cl[i].nbLitNeutres > max )
		   max = mc->cl[i].nbLitNeutres;
	} 

    /* Allocation du tableau d'elements neutre au nombre maximum de variable
       plus 1 */
    mc->tabN = (int*) malloc((max+1) * sizeof(int));
    mc->tailleTabN = max;
}


/*
    Nom Fonction : initialisationListeNeutre
    Parametre entree :
         * la matrice creuse
    Parametre retourne:
         * la matrice creuse
    Description : 
         Chargement dans le tableau des elements neutres 
         des indices des clauses et chainages selon le 
         nombre de neutres       
*/
void initialisationListeNeutre (matriceCreuse *mc)
{
    int i;
     /* Toutes les cases du tableau des elements neutres est initialise a -1 */
    for (i = 0 ; i <= mc->tailleVar ; i++)
    {
    	mc->tabN[i] = -1;
    }
    /* On remplit le tableau a partir de la matrice creuse initiale */
	for (i = 1; i <= mc->tailleClause; i++)
	{
        ajoutN (mc, i, mc->cl[i].nbLitNeutres);       
	}         
}


/*
    Nom Fonction : suppressionN
    Parametres entree :
        * la matrice creuse
        * l'indice de la clause a supprimer
        * le nombre de litteraux neutres de cette clause (avant suppression)
    Parametre retourne :
        * la matrice creuse 
    Description :
        Suppression d'un element de la liste des elements neutres 
		
*/
void suppressionN(matriceCreuse *mc, int numClause, int nbLitNeutre)
{
	if(mc->cl[numClause].clausePrec == -1)
	{
		mc->tabN[nbLitNeutre] = mc->cl[numClause].clauseSuiv;
		if(mc->tabN[nbLitNeutre] != -1)
		{
			mc->cl[mc->tabN[nbLitNeutre]].clausePrec = -1;
		}
	}
	else
	{
        mc->cl[mc->cl[numClause].clausePrec].clauseSuiv = mc->cl[numClause].clauseSuiv;
        if(mc->cl[numClause].clauseSuiv != -1)
        {
        	mc->cl[mc->cl[numClause].clauseSuiv].clausePrec = mc->cl[numClause].clausePrec;
        }
	} 
}


/*
    Nom Fonction : ajoutN
    Parametres entree :
        * la matrice creuse
        * l'indice de la clause a ajouter
        * le nouveau nombre de litteraux neutres de cette clause 
    Parametre retourne :
        * la matrice creuse
    Description : 
        Ajoute un element dans la liste des elements neutres avec 
        le chainage necessaire        
		
*/
void ajoutN (matriceCreuse *mc, int numClause, int nbLitNeutre)
{
	/* On ajoute en tete, la clause qui vient d'etre chainee n'a pas de precedent*/
	mc->cl[numClause].clausePrec = -1;
	/* Le suivant de la clause que l'on vient d'ajouter est celui
	 qui etait dans la table des neutres jusqu'ici*/
    mc->cl[numClause].clauseSuiv = mc->tabN[nbLitNeutre];
    /* Le precedent de la clause qui va etre repoussee dans la liste est celui
	 que l'on va ajouter*/
	if (mc->tabN[nbLitNeutre]!=-1)
	    mc->cl[mc->tabN[nbLitNeutre]].clausePrec = numClause;
    /* On installe la nouveau début de liste a sa place*/
    mc->tabN[nbLitNeutre] = numClause;            
}

/*
    Nom Fonction : afficherTabN
    Parametre entree :
        * la matrice creuse
    Description : 
		Affichage du tableau des elements neutres
*/
void afficherTabN (matriceCreuse *mc)
{
    int i, j = 0;
    for (i = 0; i <= mc->tailleTabN; i++)
    {
          printf("NbLitNeutre %d\n", i);
          j = mc->tabN[i];
          while (j != -1)
          {
              printf("   %d \n", j);
              j = mc->cl[j].clauseSuiv;
          }
    }
}
