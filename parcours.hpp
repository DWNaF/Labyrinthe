/*
-----------------------------------------------------------------
#################### Fonctions pour les FIFO ####################
-----------------------------------------------------------------
*/
void initialiserFifo(Fifo &file); // initialise une file à vide
bool estVide(Fifo file); // renvoie true si la file est vide, false sinon
void ajouter(Fifo &file, int v); // ajoute un maillon ayant pour valeur "v" dans la file.
int retirer(Fifo &file); // défile la file et reenvoi la valeur du maillon défilé.

/*
-----------------------------------------------------------------
################# Fonctions parcours en largeur #################
-----------------------------------------------------------------
*/

/**
 * @brief Reenvoi l'indice du sommet ayant pour ligne @param l et pour colonne @param c.
 * @return int : indice du sommet dans le labyrinthe et/ou la matrice d'adjacence.
 */
int getIndice(MatriceAdjacence mat,
    int l, // ligne du sommet 
    int c); // Colonne du sommet

/**
    * Construit récursivement le chemin minimal depuis le sommet de départ vers le sommet final
    * stocke le chemin de parcours dans @param path passé en adresse  
*/ 
void fillPath(MatriceAdjacence mat, 
    int sf,  // Sommet finale
    int *parent, // tableau des parents
    chemin &path, // chemin à complèter 
    int length); // variable utilisée comme indice de tableau car la fonction est récursive (=longueur du chemin)

/**
 * @brief calcule le chemin minimum entre le sommet de départ ayant pour coordonnées @param deb 
    et le sommet fin @param fin grâce au parcours en largeur
 * @return chemin : chemin minimal à parcourir depuis le sommet de départ pour atteindre le sommet final
 */
chemin calculerChemin(const MatriceAdjacence &mat, 
    coordonnee deb, // coordoonnes du sommet de départ
    coordonnee fin); // coordoonnes du sommet à atteindre 