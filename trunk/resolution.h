/*
    Fichier : resolution.h
    Objectif : Fonctions de resolution
    Fonctions contenues :
	* clausesSatisfaites
	* clauseFalsifiee
	* verifFalsifie
	* simplifie
	* choisirXi
	* choisirValXi
	* resoudre
	* afficherClause
	* afficherVar
    Date de creation : 13/04/2009
    Auteurs : C & F & A
*/


/* 
		PROTOTYPES DE FONCTIONS 
*/

/*
    Nom Fonction : clausesSatisfaites
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
        * retourne 0 si au moins une clause n'est pas satisfaite
        * retourne 1 si toutes les clauses sont satisfaites
*/
int clausesSatisfaites(matriceCreuse *mc);


/*
    Nom Fonction : clauseFalsifiee
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
        * retourne 0 si aucune clause n'est falsifiee
    	* retourne 1 si au moins une clause est falsifiee
*/
int clauseFalsifiee(matriceCreuse *mc); 


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
void simplifie(matriceCreuse *mc, int xi, int ordreReso);


/*
    Nom Fonction : choisirXi
    Parametre entree :
    	* mc : la matrice creuse
    Parametre retourne :
    	* variable a mettre a jour
    Description : 
	    Choix de la variable a  laquelle on affectera la valeur vrai ou faux		
*/
int choisirXi(matriceCreuse *mc);


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
void choisirValXi(matriceCreuse *mc, int xi, int ordreReso);


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
int resoudre(matriceCreuse *mc, int ordreReso);


/*
    Nom Fonction : afficherClause
    Parametre entree :
    	* mc : la matrice creuse
    Description : 
        Affichage des etats des clauses 
        (satisfaite, inchangee, falsifiee, raccourcie)		
*/
void afficherClause(matriceCreuse *mc);


/*
    Nom Fonction : afficherVar
    Parametre entree :
    	* mc : la matrice creuse
    Description : 
	    Affichage des valeurs des variables
        (vrai, fausse ou neutre)		
*/
void afficherVar(matriceCreuse *mc);


