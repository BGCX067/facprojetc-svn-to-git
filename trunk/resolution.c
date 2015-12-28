/*
    Fichier : resolution.c
    Objectif : effectuer la resolution 
    Date de creation : 13/04/2009
    Auteurs : C & F & A
*/

#include <stdio.h>
#include <stdlib.h>
#include "matriceCreuse.h"
#include "chargement.h"
#include "resolution.h"
#include "traitementNeutre.h"

/*
    Nom Fonction : clausesSatisfaites
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
        * retourne 0 si au moins une clause n'est pas satisfaite
        * retourne 1 si toutes les clauses sont satisfaites
*/
int clausesSatisfaites(matriceCreuse *mc)
{
	/* Parcours du tableau de clause afin de 
	   verifier que toutes les clauses sont satisfaites */
	return (mc->nbSat == mc->tailleClause);
}


/*
    Nom Fonction : clauseFalsifiee
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
        * retourne 0 si aucune clause n'est falsifiee
    	* retourne 1 si au moins une clause est falsifiee
*/
int clauseFalsifiee(matriceCreuse *mc)
{
	/* Parcours du tableau de clause afin de 
	   verifier qu'une clause est falsifiee */    
	return (mc->nbFals > 0);	
}


/*
    Nom Fonction : simplifie
    Parametres entree :
    	* mc : la matrice creuse
	    * xi : la variable venant d'etre modifiee
    Parametre retourne :
    	* retourne la matrice creuse mise a  jour
    Description : 
    	Comme une nouvelle valeur a  ete affectee a  une variable
    	il y a une serie de changement a  effectuer.		
*/
void simplifie (matriceCreuse *mc, int xi, int ordreReso)
{
	valeur val;
	int numCl;
	litteral *x;
	/* On ne parcourera ici que les clauses correspondant au
	   litteraux changes apres modification de variable */
    x   = mc->var[xi].listeLit;
    val = mc->var[xi].valVar;
    
	while (x != NULL)
	{   
		/* On recupere le numero de la clause du litteral traite */
    	numCl = x->numClause;
		
		/* Suppression de la liste dans tous les cas */
		
		if (mc->cl[numCl].e == SATISFAIT)
        {
        	/* Si au moins un litteral valide, on supprime
        	   la clause de la "liste" des clauses ayant 0 neutres */
        	suppressionN(mc, numCl, 0);
        }
        else
        {
        	suppressionN(mc, numCl, mc->cl[numCl].nbLitNeutres);
        }
        
        /* Traitement des différentes possibilités */
        
		if (val == VRAI) 
		{	
			/* Transition neutre -> vrai */
			if (ordreReso == 1)
			{
				if (mc->cl[numCl].e == INCHANGE)
		  		{
		  			mc->nbInch--;
		  		}
		  		else if(mc->cl[numCl].e == RACCOURCIS)
		  		{
		  			mc->nbRac--;
		  		}
		        if(x->s == PLUS)
		        {
	                /* On mets a jour le nombre de litteraux qui satisfont la clause
	                   avant de passer a vrai, l'etat du litteral etait neutre
	                   On incremente donc le nb de litteraux qui satisfont la clause */
		        	mc->cl[numCl].nbLitValides++;
		        	if (mc->cl[numCl].e != SATISFAIT)
				  	{
			           	mc->cl[numCl].e = SATISFAIT;
			           	mc->nbSat++;
				  	}
		        }
				/* Comme avant de passer a vrai	l'etat du litteral etait neutre,
				le nombre de litteraux neutre se voit reduit de 1 */
				mc->cl[numCl].nbLitNeutres--;
			}
			else 
			{
				/* ordreReso != 1 */
				/* Transition faux -> vrai */
				if(x->s == PLUS)
		        {
					/* Signe negatif => litteral valide.
					On incremente donc le nb de litteraux qui satisfont la clause */	
					mc->cl[numCl].nbLitValides++;
					
					if (mc->cl[numCl].e != SATISFAIT)
					{
						if (mc->cl[numCl].e == FALSIFIE)
						{
							// La clause ne sera plus falsifiee
							mc->nbFals--;
						}
						else if(mc->cl[numCl].e == RACCOURCIS)
				  		{
				  			mc->nbRac--;
				  		}
						mc->cl[numCl].e = SATISFAIT;
						mc->nbSat++;
					}
		        }
		        else 
		        {
		        	/* (x->s == MOINS) */
		        	/* Signe positif => litteral invalide.
	                On decremente donc le nb de litteraux qui satisfont la clause */
	                if (mc->cl[numCl].nbLitValides == 1)
	                {
	                	// Le dernier litteral qui satisfaisait la clause va s'invalider
	                	mc->nbSat--;
	                }
	
	            	mc->cl[numCl].nbLitValides--;
		        }
			}
		}
		else if (val == FAUX) 
        {
        	if (ordreReso == 1)
			{
				/* Transition vrai -> faux */
	
		        /* On mets à jour le nombre de litteraux qui satisfont la clause
		       	   avant de passer a faux, l'etat du litteral etait vrai
		       	   donc deux cas possible : */
	            if (x->s == MOINS)
	            {
	                /* Signe negatif => litteral valide.
	                   On incremente donc le nb de litteraux qui satisfont la clause */	
	                mc->cl[numCl].nbLitValides++;
	
	                if (mc->cl[numCl].e != SATISFAIT)
				  	{
				  		if (mc->cl[numCl].e == FALSIFIE)
						{
							// La clause ne sera plus falsifiee
							mc->nbFals--;
						}
						else
				  		{
				  			mc->nbRac--;
				  		}
						mc->cl[numCl].e = SATISFAIT;
				        mc->nbSat++;
				  	}
	            }
	            else     /* (x->s == PLUS) */
	            {
	                /* Signe positif => litteral invalide.
	                On decremente donc le nb de litteraux qui satisfont la clause */
	                if (mc->cl[numCl].nbLitValides == 1)
	                {
	                	// Le dernier litteral qui satisfaisait la clause va s'invalider
	                	mc->nbSat--;
	                }
	
	            	mc->cl[numCl].nbLitValides--;
	            }
			}
			else
			{
				/* ordreReso != 1 */
				/* Transition neutre -> faux */
				if (mc->cl[numCl].e == INCHANGE)
		  		{
		  			mc->nbInch--;
		  		}
		  		else if(mc->cl[numCl].e == RACCOURCIS)
		  		{
		  			mc->nbRac--;
		  		}
				if(x->s == MOINS)
		        {
	                /* On mets a jour le nombre de litteraux qui satisfont la clause
	                   avant de passer a vrai, l'etat du litteral etait neutre
	                   On incremente donc le nb de litteraux qui satisfont la clause */
		        	mc->cl[numCl].nbLitValides++;
		        	if (mc->cl[numCl].e != SATISFAIT)
				  	{
						mc->cl[numCl].e = SATISFAIT;
						mc->nbSat++;
				  	}
		        }
				mc->cl[numCl].nbLitNeutres--;
			}
        }
        
        else 
        {
	        if (ordreReso == 1)
			{
	        	/* (val == neutre) Transition faux -> neutre */
	            if (x->s == MOINS)
	            {
	            	if (mc->cl[numCl].nbLitValides == 1)
	                {
	                	/* Le dernier litteral qui satisfaisait la clause va s'invalider */
	                	mc->nbSat--;
	                }
	            	/* On mets a jour le nombre de litteraux qui satisfont la clause
		       	       avant de passer a neutre, l'etat du litteral etait faux
		               On decremente donc le nb de litteraux qui satisfont la clause */
	                mc->cl[numCl].nbLitValides--;
	            }
	            else
	            {
	            	if (mc->cl[numCl].e == FALSIFIE)
				   	{
				    	/* Un litteral au moins sera neutre */
				    	mc->nbFals--;
				    }
				    else if(mc->cl[numCl].e == RACCOURCIS)
			  		{
			  			mc->nbRac--;
			  		}
	            }
	            mc->cl[numCl].nbLitNeutres++;
			}
			else
			{
				/* ordreReso != 1 */
				/* Transition vrai -> neutre */
	            if (x->s == PLUS)
	            {
	            	if (mc->cl[numCl].nbLitValides == 1)
	                {
	                	/* Le dernier litteral qui satisfaisait la clause va s'invalider */
	                	mc->nbSat--;
	                }
	            	/* On mets a jour le nombre de litteraux qui satisfont la clause
		       	       avant de passer a neutre, l'etat du litteral etait faux
		               On decremente donc le nb de litteraux qui satisfont la clause */
	                mc->cl[numCl].nbLitValides--;
	            }
	            else
	            {
	            	if (mc->cl[numCl].e == FALSIFIE)
				   	{
				    	/* Un litteral au moins sera neutre */
				    	mc->nbFals--;
				    }
				    else if(mc->cl[numCl].e == RACCOURCIS)
			  		{
			  			mc->nbRac--;
			  		}
	            }
	            mc->cl[numCl].nbLitNeutres++;
			}
        }
        
        
        /* Traitement de mise a jour, dans tous les cas */
        
        if(mc->cl[numCl].nbLitValides > 0)
    	{
       		ajoutN(mc, numCl, 0);
    	}
    	else
    	{
    		if (mc->cl[numCl].nbLitNeutres == 0)
    		{
    			mc->cl[numCl].e = FALSIFIE;
    			mc->nbFals++;
    		}
    		else
    		{
    			mc->cl[numCl].e = RACCOURCIS;
    			mc->nbRac++;
    		}
    		ajoutN(mc, numCl, mc->cl[numCl].nbLitNeutres);
    	}
	   x = x->suivClause;
	}
}

/*
    Nom Fonction : choisirXi
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
    	* variable a mettre a jour
    Description : 
	    Choix de la variable a  laquelle on affectera la valeur vrai ou faux		
*/
int choisirXi(matriceCreuse *mc)
{
    int i=1;
    litteral *pLit;

    while (mc->tabN[i] == -1)
    {
		i++;
    }

    pLit = mc->cl[mc->tabN[i]].listeLit;

    while (mc->var[pLit->numVar].valVar != NEUTRE)
    {
    	pLit = pLit->suivVar;
    } 
    return pLit->numVar;
}


/*
    Nom Fonction : choisirValXi
    Parametres entree :
    	* mc : la matrice creuse
	    * xi : la variable venant d'etre modifiee
    Parametre retourne :
    	* retourne la matrice creuse mise a  jour
    Description : 
        Choix de la valeur affectee a xi		
*/
void choisirValXi(matriceCreuse *mc, int xi, int ordreReso)
{
    if (mc->var[xi].valVar == NEUTRE)
    {
    	/* Selon choix de résolution */
    	if(ordreReso == 1)
    	{
			/* Si la variable etait neutre elle devient vraie */
	        mc->var[xi].valVar = VRAI;
	        mc->nbVrai++;
	        mc->nbNeutre--;
    	}
    	else
    	{
    		/* Si la variable etait neutre elle devient fausse */
    		mc->var[xi].valVar = FAUX;
    		mc->nbFaux++;
	        mc->nbNeutre--;
    	}	
    }
    else if (mc->var[xi].valVar == VRAI)
    {
    	if(ordreReso == 1)
    	{
			/* Si la variable etait vraie, elle passe à faux */
	        mc->var[xi].valVar = FAUX;
	        mc->nbFaux++;
	        mc->nbVrai--;
    	}
    	else
    	{
    		/* Si la variable etait vraie, elle passe à neutre */
	        mc->var[xi].valVar = NEUTRE;
	        mc->nbNeutre++;
	        mc->nbVrai--;
    	}
    }
    else /* mc->var[xi].valVar == FAUX */
    { 
    	if(ordreReso == 1)
    	{
			/* Dans le dernier cas, elle revient à neutre */
	        mc->var[xi].valVar = NEUTRE;
	        mc->nbNeutre++;
	        mc->nbFaux--;
	        
    	}
        else
        {
			/* Si la variable etait fausse elle devient vraie */
	        mc->var[xi].valVar = VRAI;
	        mc->nbVrai++;
	        mc->nbFaux--;
    	}
    }
}


/*
    Nom Fonction : resoudre
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
    	* retourne 1 s'il y a une solution
    	* retourne 0 sinon
    Description : 
	    Algorithme de resolution		
*/
int resoudre(matriceCreuse *mc, int ordreReso)
{
    int xi;
	if (clausesSatisfaites(mc))
	{	
    	return 1;
	}
	else if (clauseFalsifiee(mc))
    {
        return 0;
    }
	else
	{   
		//afficherTabN(mc);
		xi = choisirXi(mc);
        choisirValXi(mc, xi, ordreReso);
        simplifie(mc, xi, ordreReso);
       	/*printf("%d\n",xi);
        printf("%d\n",mc->var[xi].valVar); 
	    printf("%d\n",mc->nbSat);
		printf("%d\n",mc->nbFals);
		getchar();*/
        if (resoudre(mc,ordreReso))
        {
            return 1;
        }
        else
        {
        	//afficherTabN(mc);
            choisirValXi(mc, xi, ordreReso);
            simplifie(mc, xi, ordreReso);
            /*printf("%d\n",xi);
            printf("%d\n",mc->var[xi].valVar);  
		    printf("%d\n",mc->nbSat);
			printf("%d\n",mc->nbFals);
			getchar();*/
            if (resoudre(mc,ordreReso))
            {
                return 1;
            }
            else
            {
            	//afficherTabN(mc);
                choisirValXi(mc, xi, ordreReso);
                simplifie(mc, xi, ordreReso);
                return 0;
            }
		}
	} 
}


/*
    Nom Fonction : afficherClause
    Parametre entree :
    	* mc : la matrice creuse
    Description : 
        Affichage des etats des clauses 
        (satisfaite, inchangee, falsifiee, raccourcie)		
*/
void afficherClause(matriceCreuse *mc)
{
	int i;  /* Effectue le parcours de toutes les clauses */
	
	for (i = 1; i <= mc->tailleClause; i++)
	{
        /* A chaque clause correspond un etat */  
		switch (mc->cl[i].e) 
		{
			case SATISFAIT :
				printf("La clause %d est satisfaite \n", i);
				break;

			case INCHANGE :
				printf("La clause %d est inchangee \n", i);
				break;

			case FALSIFIE :
				printf("La clause %d est falsifiee \n", i);
				break;

			case RACCOURCIS :
				printf("La clause %d est raccourcie \n", i);
				break;

			default: ;
		}
	}
}


/*
    Nom Fonction : afficherVar
    Parametre entree :
    	* mc : la matrice creuse
    Description : 
	    Affichage des valeurs des variables
        (vrai, fausse ou neutre)		
*/
void afficherVar(matriceCreuse *mc)
{
	int i;  /* Effectue le parcours de toutes les variables */
	
	for (i = 1; i <= mc->tailleVar; i++)
	{
        /* A chaque clause correspond une valeur */  
		switch (mc->var[i].valVar) 
		{
			case FAUX :
				printf("La variable %d est fausse \n", i);
				break;

			case VRAI :
				printf("La variable %d est vraie \n", i);
				break;

			case NEUTRE :
				printf("La variable %d est neutre \n", i);
				break;

			default: ;
		}
	}
}
