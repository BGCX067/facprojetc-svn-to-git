/*
    Fichier : chargement.h
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


/* 
		PROTOTYPES DE FONCTIONS 
*/

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
void charger(char *nomFichier, matriceCreuse *mc);


/*
    Nom Fonction : afficherMc
    Parametre entree :
    	* mc : la matrice creuse
    Description :
         Affiche la matrice creuse entièrement suivant les
         clauses et suivant les variables
*/
void afficherMc(matriceCreuse *mc);
