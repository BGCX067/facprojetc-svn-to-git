/*
    Fichier : traitementNeutre.h
    Objectif : Definition des types, des structures et des fonctions
    Date de creation : 08/04/2009
    Auteurs : C & F & A
*/


/* 
		PROTOTYPES DE FONCTIONS 
*/


/*
    Nom Fonction : creationListeNeutre
    Parametre entree :
        * la matrice creuse
    Parametre retourne :
        * la matrice creuse
    Description : 
		Creation du tableau des elements neutres
		et initialisation de toutes les cases a -1
*/
void creationListeNeutre(matriceCreuse *mc);


/*
    Nom Fonction : initialisationListeNeutre
    Parametre entree :
         * la matrice creuse
    Parametre retourne :
         * la matrice creuse
    Description : 
         Chargement dans le tableau des elements neutres 
         des indices des clauses et chainages selon le nombre de neutres      
*/
void initialisationListeNeutre(matriceCreuse *mc);


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
void suppressionN(matriceCreuse *mc, int numClause, int nbLitNeutre);


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
void ajoutN(matriceCreuse *mc, int numClause, int nbLitNeutre);


/*
    Nom Fonction : afficherTabN
    Parametre entree :
        * la matrice creuse
    Description : 
		Affichage du tableau des elements neutres
*/
void afficherTabN(matriceCreuse *mc);
