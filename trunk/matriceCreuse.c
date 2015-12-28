/*
    Fichier : matriceCreuse.c
    Objectif : Fonctions d'ajout dans la matrice creuses
    Fonction :
    * ajouterlitteral
    Date de création : 08/04/2009
    Auteurs : C & F & A
*/

#include <stdio.h>
#include <stdlib.h>
#include "matriceCreuse.h"


/*
    Nom Fonction : ajouterLitteral
    Parametres entree :
    	* numC : le numero de la clause
    	* numV : le numero de la variable
        * s : le signe du litteral
        * mc : la matrice creuse       
    Description :
        Chargement d'un element dans la matrice creuse
        et realisation du double chainage suivant la clause et la variable
*/
void ajouterLitteral(int numC, int numV, signe s, matriceCreuse *mc)
{
	litteral *newEl, *ptrVar, *ptrCl, *pVar, *pCl;

	/* Initialisation des champs du nouveau litteral */
	newEl = (litteral*) malloc(sizeof(litteral));
	newEl->numClause  = numC;
	newEl->numVar     = numV;
	newEl->s	      = s;
	newEl->suivClause = NULL;
	newEl->suivVar    = NULL;

	/* Ajout depuis la liste des clauses */
	ptrVar = mc->cl[numC].listeLit;
	
	if (ptrVar == NULL || numV < ptrVar->numVar) 
	{
		/* Ajout en début */
		newEl->suivVar		  = ptrVar;
		mc->cl[numC].listeLit = newEl;
	}
	else 
	{
		/* Parcours de la liste pour trouver l'emplacement */	
		pVar = ptrVar->suivVar;
		while (pVar != NULL && pVar->numVar < numV)
		{
			ptrVar = pVar;
			pVar   = pVar->suivVar;
		}
		newEl->suivVar  = ptrVar->suivVar;
		ptrVar->suivVar = newEl;
	}

	/* Ajout depuis la liste des variables */	
	ptrCl = mc->var[numV].listeLit;
	
	if (ptrCl == NULL || numC == 1) 
	{ 
		/* Ajout en début */
		newEl->suivClause = ptrCl;
		mc->var[numV].listeLit = newEl;
	}
	else 
	{ 
		/* Parcours de la liste pour trouver l'emplacement */
		pCl = ptrCl->suivClause;
		while (pCl != NULL && pCl->numClause < numC)
		{
			ptrCl = pCl;
			pCl = pCl->suivClause;
		}

		newEl->suivClause = ptrCl->suivClause;
		ptrCl->suivClause = newEl;
	}  
}

void affichageSynthese(matriceCreuse *mc)
{
	printf("Nombre de variables vraies : %d\n", mc->nbVrai);
	printf("Nombre de variables fausses : %d\n", mc->nbFaux);
	printf("Nombre de variables neutres : %d\n", mc->nbNeutre);
	printf("Nombre de clauses satisfaites : %d\n", mc->nbSat);
	printf("Nombre de clauses falsifiees : %d\n", mc->nbFals);
	printf("Nombre de clauses raccourcies : %d\n", mc->nbRac);
	printf("Nombre de clauses inchangees : %d\n", mc->nbInch);
		
}

void affichageCourant (matriceCreuse *mc)
{
     litteral *x;
     int i;
	/* Parcours de la matrice creuse par clauses */
	for(i = 1; i <= mc->tailleClause; i++)
	{
        
		if (mc->cl[i].listeLit != NULL)
		{
			/* Recuperation du pointeur vers le premier litteral 
			   de la clause */                               
			x = mc->cl[i].listeLit;

			/* affichage de la clause*/
			printf("Clause %d \n",i);

			/* affichage de la variable*/
			while (x != NULL)
			{
				printf("        Variable %d ",x->numVar );

				/* affichage du signe */
				if (x->s == MOINS)
					printf("signe moins\n");
				else
					printf("signe plus\n");

				/* On se rend a la variable suivante */ 
				x = x->suivVar;
			}
		}
	}           
}
