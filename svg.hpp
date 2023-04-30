// --------------------------------------------------------------------
// prédéfinition des fonctions liées à l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

// création du fichier et ouverture du flot d'écriture associé
// retourne false si le fichier n'a pas pu être ouvert.
bool ouvrirFichierSVG(const std::string &nomFichier,// nom du fichier à créer
		      std::ofstream &out,// flot d'écriture ouvert par la fonction
		      int largeur, // largeur de l'image en pixels
		      int hauteur);// hauteur de l'image en pixels

// fermeture du flot d'écriture et du fichier associé
void fermerFichierSVG(std::ofstream &out);// flot d'écriture à fermer par la fonction

// écriture d'une ligne dans le flot de sortie
void ligne(std::ofstream &out,// flot d'écriture dans lequel ajouter la ligne
	   int x1, int y1,// coordonnées du point de départ de la ligne
	   int x2, int y2,// coordonnées du point d'arrivée de la ligne
	   const std::string& color,// couleur de tracé de la ligne
	   int width);// épaisseur de tracé de la ligne

// écriture d'un rectangle dans le flot de sortie
void rect(std::ofstream &out,// flot d'écriture dans lequel ajouter le rectangle
	  int x, int y,// coordonnées du point supérieur gauche du rectangle
	  int width,// largeur du rectangle en pixels
	  int height,// hauteur du rectangle en pixels
	  const std::string &color);// couleur de tracé du rectangle

// écriture d'un texte dans le flot de sortie
void text(std::ofstream &out,// flot d'écriture dans lequel ajouter le texte
	  int x, int y,// coordonnées du point auquel placer le texte
	               // le texte est centré par rapport à ce point
	  int size,// hauteur des caractères du texte en pixels
	  const std::string &txt,// le texte à ajouter
	  const std::string &color);// la couleur de tracé du texte

// Template du labyrinthe à vide (afin de ne pas réecrire le même code sur toutes les fonctions dessiner)
void labTemplate(labyrinthe &laby, const std::string &nomFichier, std::ofstream &out);

// dessine le labyrinthe à vide.
void dessinerLabyrinthe(labyrinthe &laby, const std::string &nomFichier);

// dessine le parcours du graphe dans un svg 
void dessinerMatrice(const MatriceAdjacence &mat, // matrice d'adjacence
	const labyrinthe &lab, // labyrinthe
	const std::string &nom); // nom du fichier de sortie

void dessinerSolution(const labyrinthe &laby, // labyrinthe
	const chemin &ch, // chemin min depuis le sommet de départ vers le sommet final
	const std::string &nomFichier); // nom du fichier de sortie


