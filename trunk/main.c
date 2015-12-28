/* testListe.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriceCreuse.h"
#include "chargement.h"
#include "resolution.h"
#include "traitementNeutre.h"


int main(int argc,char *argv[])
{
	double tDeb,tFin;
	tDeb = clock();
	int rslt;
	matriceCreuse mc;
	char *nomFichier ;
	if(argc < 3)
	{
		if(argc == 1)
		{
			nomFichier = "test.txt";
		}
		else if(argc == 2)
		{
			nomFichier = argv[1];
		}
	
		charger(nomFichier,&mc);
		//afficherMc(&mc);
		//afficherTabN(&mc);
		printf ("\nRESOLUTION : \n");
		rslt = resoudre(&mc);
	    if (rslt)
	    {
	        printf("Satisfaisable\n");
	        afficherClause (&mc);
	        afficherVar(&mc);
	    }
	    else 
	    {
	        printf("Insatisfaisable\n");
	    }
	    /*free(nomFichier); ERREUR !!?? */
	    /* Liberation des espaces alloues. */
	    free(mc.cl);
	    free(mc.var);
	    tFin = clock();
	    fprintf(stderr, "\n\nTemps d'execution : %f secondes\n", (double)(tFin-tDeb) / (double) CLOCKS_PER_SEC); 
		
	}
	else
	{
		printf("Mauvais nombre d'arguments\n");
	}
	       
}

