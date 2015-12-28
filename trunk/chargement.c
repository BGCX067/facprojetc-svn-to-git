/*
    Fichier : chargement.c
    Objectif : lire le fichier texte et le charger dans la matrice creuse.
    Fonctions : 
     * Charger : permet de créer à partir du fichier texte la matrice creuse
     * AfficherMc : permet d'afficher la matrice creuse dans son ensemble
    Tests realises :
    * Ouverture d'un fichier dont le nom n'existe pas
    * Ouverture d'un fichier vide
    * Ouverture d'un fichier dans lequel les donnees sont erronees
    Date de creation : 08/04/2009
    Auteurs : C & F & A
*/

#include <stdio.h>
#include <stdlib.h>
#include "matriceCreuse.h"
#include "traitementNeutre.h"
#include "chargement.h"

/*
    Nom Fonction : charger
    Parametre entree :
    	* nomFichier : le nom du fichier à charger
    Parametre retourne :
        * mc : la matrice creuse
    Description :
        Permet, à partir d'un fichier texte, de creer et de
        remplir la matrice creuse 
*/
void charger(char *nomFichier, matriceCreuse *matCreuse)
{
	FILE* fichier = NULL; // fichier à ouvrir
	int valeurLue  = 0;   // donnée du fichier lues
	char c         = 0;	  // caractère lu
	int nbClauses  = 0;   // nombre de clauses à lire
	int nbVariables;	  // nombre de variables à lire
	int nbVarLues  = 0;	  // nombre de variables lues
	int ligne      = -1;  // numéro de ligne (les deux premières ne comptent pas)
	int ligneAvant = -2;  // numéro de ligne précédent
	int colonne    = 0;   // numéro de colonne
	int errnon     = 0;   // 1 pour données du fichier corrompues, 0 sinon
	int i;
	signe s;

	/* Ouverture du fichier */
	if ((fichier = fopen(nomFichier, "r")) != NULL)
	{
		printf ("Le fichier %s est bien ouvert\n", nomFichier);
		do
 	   	{
			/* Lecture du fichier par valeur */
			valeurLue = 0;
    		if (fscanf(fichier, "%d", &valeurLue) == 0)
			{
				/* les données sont erronées */
				printf("Les donnees sont erronees a la ligne %d", ligne+2);
				errnon = 1;
			}
			else
			{
				if (ligne == -1) /* 1ère ligne du fichier (nombre de variables) */
				{
					if (valeurLue <= 0)
					{
						printf("Nombre de variables incorrect");
						errnon = 1;
					}
					else 
					{
						/* création du tableau dynamique de variables
						   on n'utilise pas la case 0 pour eviter les 
						   conversions d'indice de tableau */
						matCreuse->var = (variable*) malloc((valeurLue+1) * sizeof(variable));

						/* stockage de la taille du tableau */
						matCreuse->tailleVar = valeurLue;

						/* mise à jour du nombre de variable lues */
						nbVariables = valeurLue;

						/* toutes les variables sont initialisées à neutre  
						   et les pointeur de littéraux à nul */
						for (i = 1; i <= valeurLue; i++)
						{
							matCreuse->var[i].valVar   = NEUTRE;
							matCreuse->var[i].listeLit = NULL;
						}
					}
				}
				else if (ligne == 0) /* 2ème ligne du fichier (nombre de clauses) */
				{
					if (valeurLue <= 0)
					{
						printf("Nombre de clauses incorrect");
						errnon = 1;
					}
					else 
					{
						/* création du tableau dynamique de clauses
						   on n'utilise pas la case 0 pour eviter les 
						   conversions d'indice de tableau */
						matCreuse->cl = (clause*) malloc((valeurLue+1) * sizeof(clause));
						
						/* stockage de la taille du tableau */
						matCreuse->tailleClause = valeurLue;

						/* mise à jour du nombre de clauses lues */
						nbClauses = valeurLue;

						/* Toutes les clauses sont initialisees à inchange 
						   et les pointeur de litteraux sont null 
						   le nombre de litteraux neutre et de clauses
						   valides est initialisé à zero */
						for (i = 1; i <= valeurLue; i++)
						{
							matCreuse->cl[i].e            = INCHANGE;
							matCreuse->cl[i].listeLit     = NULL;
							matCreuse->cl[i].nbLitNeutres = 0;
							matCreuse->cl[i].nbLitValides = 0;
						}
					}
				}
				else   /* ligne contenant les litteraux */
				{
					if (valeurLue == 0)
					{
						c = fgetc(fichier);
						if (c != EOF)
						{
							/* les données sont erronées */
							printf("Les donnees sont erronees a la ligne %d", ligne+2);
							errnon = 1;
						}
					}
					else if (valeurLue > nbVariables || valeurLue < -nbVariables)
					{
						/* numéro de la variable incorrect */
						printf("la valeur de la variable %d ligne %d est incorrecte", valeurLue, ligne+2);
						errnon = 1;
					}
					else
					{
						/* mise à jour du nombre de variables lues */
						if (ligneAvant != ligne)
							nbVarLues = 0;
						else
						{
							nbVarLues++;
							ligneAvant = ligne;
						}

						if (ligne <= nbClauses)
						{
							/* recupération du signe */
							if (valeurLue < 0)
							{
								s = MOINS;
								colonne = valeurLue * -1;
							}
							else
							{
								s = PLUS;
								colonne = valeurLue;
							}

							/* ajout du nouveau littéral dans la matrice creuse */
							ajouterLitteral(ligne, colonne, s, matCreuse);

							/* incrémentation du nombre de littéraux neutres de la clause */
							matCreuse->cl[ligne].nbLitNeutres++;
						}
						else
						{
							/* il y a trop de clauses */
							printf("Il ne devrait y avoir que %d clauses", nbClauses);
							errnon = 1;
						}
					}
				}
			}
			
			if (errnon == 0)
			{
				/* lecture du caractère suivant */
				c = fgetc(fichier);

				/* on ne comptabilise pas les espaces */
				while (c == ' ')
					c = fgetc(fichier);

				if (c == '\n')
				{
					/* ligne suivante */
					ligne++;
					ligneAvant++;
				}
				else if (c == EOF)
				{
					if (ligne < nbClauses)
					{
						/* il n'y a pas assez de clauses */
						printf("Il devrait y avoir %d clauses", nbClauses);
						errnon = 1;
					}
				}
				else if (c == ',' && ligne != -1 && ligne != -2)	
				{
					if (nbVarLues > nbVariables)
					{
						/* il y a trop de variables */
						printf("Il ne devrait y avoir que %d variables a la ligne %d ", nbVariables, ligne+2);
						errnon = 1;
					}
				}
				else
				{
					/* les données sont erronées */
					printf("Les donnees sont erronees a la ligne %d", ligne+2);
					errnon = 1;
				}
			}
    	}
		while (c != EOF && errnon == 0);

		if (errnon == 0)
		{
			/* creation du tableau des elements neutres */
			creationListeNeutre(matCreuse);

			/* remplissage du tableau a la situation initiale de la matrice creuse */
			initialisationListeNeutre(matCreuse);
			matCreuse->nbFals = 0;
			matCreuse->nbSat  = 0;
			matCreuse->nbRac  = 0;
			matCreuse->nbInch  = matCreuse->tailleClause;
			matCreuse->nbVrai  = 0;
			matCreuse->nbFaux  = 0;
			matCreuse->nbNeutre  = matCreuse->tailleVar;
			
		}

		/* fermeture du fichier */
		fclose(fichier);
	}
	else
	{
	    printf("Impossible d'ouvrir le fichier %s\n", nomFichier);
		errnon = 1;
	}

	if (errnon == 1)
		/* terminer le programme en echec
		   exit réalise la libération de la mémoire dynamique */
		exit(EXIT_FAILURE); 
}


/*
    Nom Fonction : afficherMc
    Paramètre entrée :
		* mc : la matrice creuse
    Description : 
	Affiche la matrice creuse mc sur l'entrée standard
*/
void afficherMc(matriceCreuse *mc)
{
	litteral *x;
	int i;
	
	/* Parcours de la matrice creuse par variable */
	for(i = 1; i <= mc->tailleVar; i++)
	{
		if (mc->var[i].listeLit != NULL)
		{
			/* Recuperation du pointeur vers le premier litteral 
			   de la variable */                   
			x = mc->var[i].listeLit;

			/* affichage de la variable*/
			printf("Variable %d \n", i);

			/* affichage de la clause*/
			while (x != NULL)
			{
				printf("        Clause %d Next ",x->numClause );

				/* Affichage du signe */
				if (x->s == MOINS) 
					printf("signe moins\n");
				else
					printf("signe plus\n");

				/* On se rend a la clause suivante */   
				x = x->suivClause;
			}
		}
	}
			
	/* Parcours de la matrice creuse par clauses */
	for(i = 1; i <= mc->tailleClause; i++)
	{
        if  (mc->cl[i].e != SATISFAIT)
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
                      if (mc->var[x->numVar].valVar == NEUTRE)
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
	}
}
