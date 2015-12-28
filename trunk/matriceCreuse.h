/*
    Fichier : matriceCreuse.h
    Objectif : Definition des types, des structures et des fonctions
    Date de creation : 08/04/2009
    Auteurs : C & F & A
*/

/* Une variable est un litteral positif ou negatif represente par un numero de
   clause dans laquelle il est present ainsi que par son numero de variable
   (1 pour X1, 2 pour X2 etc...)
*/

typedef enum {MOINS, PLUS} signe;
/* "MOINS" pour la negation de la variable, "PLUS" sinon */

typedef struct litteral litteral;
struct litteral
{
	int numClause;
	int numVar;
	signe s;
	litteral *suivClause; /* Suivant de la liste de clauses */
	litteral *suivVar;    /* Suivant de la liste de variables */
}; 

typedef enum {INCHANGE, SATISFAIT, FALSIFIE, RACCOURCIS} etat;
typedef enum {FAUX, VRAI, NEUTRE} valeur;

typedef struct
{
	valeur valVar;       /* Contient la valeur affectee à la variable */
	litteral *listeLit;
}variable;

typedef struct
{
	etat e;
    int nbLitNeutres;
    int nbLitValides;
    int clausePrec; /* Donne l'indice de la clause precedente à analyser (selon tri) */
    int clauseSuiv; /* Donne l'indice de la clause suivante à analyser (selon tri) */
	litteral *listeLit;
}clause;

typedef struct
{
	variable *var;
	clause *cl;
	int *tabN;
	int tailleVar;    /* Nombre de variables */
	int tailleClause; /* Nombre de clauses */
	int tailleTabN;   /* Taille du tableau des neutres */
	int nbSat;        /* Contient le nombre de clauses satisfaites */
	int nbFals;		  /* Contient le nombre de clauses falsifiees */
	int nbRac;        /* Contient le nombre de clauses raccourcies */
	int nbInch;		  /* Contient le nombre de clauses inchangées */
	int nbVrai;		  /* Contient le nombre de variables misent a vrai */
	int nbFaux;		  /* Contient le nombre de variables misent a faux */
	int nbNeutre;	  /* Contient le nombre de variables misent a neutre */
}matriceCreuse;


/* 
		PROTOTYPES DE FONCTIONS 
*/


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
void ajouterLitteral(int numC, int numV, signe s, matriceCreuse *mc);

void affichageSynthese(matriceCreuse *mc);

void affichageCourant (matriceCreuse *mc);

