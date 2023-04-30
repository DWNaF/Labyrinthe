#include <iostream>

using namespace std;

#include "types.hpp"
#include "matrices.hpp"
#include "parcours.hpp"
#include "svg.hpp"
#include "laby.hpp"


// --------------------------------------------------------------------
// programme principal
// --------------------------------------------------------------------

int main(int argc, char *argv[]){
  // analyse des paramètres pour déterminer la taille du labyrinthe
  int largeur, hauteur;
  
  if(argc==1){
    // dimensions par défaut
    largeur = LARGEUR;
    hauteur = HAUTEUR;
  } else if(argc==3){
    // lecture des dimensions dans les paramètres
    largeur = atoi(argv[1]);
    hauteur = atoi(argv[2]);
  } else {
    cerr << "syntaxe : " << argv[0] << " [largeur hauteur]" << endl;
    return 0;
  }
  
  // création du labyrinthe
  labyrinthe laby;
  initialiserLabyrinthe(laby, largeur, hauteur);

  // génération du labyrinthe
  genererLabyrinthe(laby);

  // dessin du labyrinthe
  dessinerLabyrinthe(laby,"laby.svg");

  // création de la matrice
  MatriceAdjacence m = {0,0,nullptr};
  remplirMatrice(m, laby);
  afficherMatrice(m);
  dessinerMatrice(m, laby, "graphe.svg");

  // Calcule chemin
  coordonnee deb, fin;
  chemin path;
  saisirCoordonnees(deb, fin, laby.largeur, laby.hauteur);
  path = calculerChemin(m, deb, fin);

  dessinerSolution(laby, path, "solution.svg");
  
  // suppression du labyrinthe
  effacerLabyrinthe(laby);
  // suppression de la matrice
  effacerMatrice(m);

  return 1;
}
