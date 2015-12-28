/* testListe.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "matriceCreuse.h"
#include "chargement.h"
#include "resolution.h"
#include "traitementNeutre.h"


int main(int argc,char *argv[])
{
	pid_t pid;
	int ordreReso;
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
		pid = fork();
		if(pid == 0)
		{
			ordreReso = 1;
		}
		else if (pid >0)
		{
			ordreReso = 0;
		}
		else
		{
			perror("erreur fork");
			exit(1);
		}
		rslt = resoudre(&mc,ordreReso);
	    if (rslt)
	    {
	        printf("Satisfaisable\n");
	        afficherVar(&mc);
	    }
	    else 
	    {
	        printf("Insatisfaisable\n");
	    }
	    affichageSynthese(&mc);
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
	
	if(pid == 0)
	{ 
		// On est dans le fils
		kill(getppid(),9); // kill le pere
	}
	else
	{
		//On est dans le pere
		kill(pid,9); // On kill le fils
	}
	
	return 0;
	       
}

