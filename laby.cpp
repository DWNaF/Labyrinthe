#include <iostream>


using namespace std;

#include "types.hpp"

// --------------------------------------------------------------------
// définition des fonctions liées à la gestion d'un labyrinthe
// --------------------------------------------------------------------

void initialiserLabyrinthe(labyrinthe &laby, int largeur, int hauteur){
  // initialisation des dimensions
  laby.largeur = largeur;
  laby.hauteur = hauteur;
  // allocation des zones mémoire
  laby.cell = new int[largeur*hauteur];
  laby.mursV = new bool[(largeur+1)*hauteur];
  laby.mursH = new bool[largeur*(hauteur+1)];
  // initialisation des zones mémoire
  // un identifiant différent par cellule
  for(int i=0; i<largeur*hauteur; i++) laby.cell[i] = i;
  // tous les murs verticaux sont présents
  for(int i=0; i<(largeur+1)*hauteur; i++) laby.mursV[i] = true;
  // tous les murs horizontaux sont présents
  for(int i=0; i<largeur*(hauteur+1); i++) laby.mursH[i] = true;
}

void effacerLabyrinthe(labyrinthe &laby){
  delete [] laby.cell;
  delete [] laby.mursV;
  delete [] laby.mursH;
}

void genererLabyrinthe(labyrinthe &laby){
  // calcul du nombre de murs à supprimer
  int nbm = laby.largeur*laby.hauteur-1;
  int nb=0;

  while(nb<nbm){
    // génération aléatoire d'une case de la grille
    // et d'une direction de suppression
    int c=rand()%laby.largeur;// dans [0,M-1]
    int l=rand()%laby.hauteur;// dans [0,N-1]
    int dir=rand()%4; // 0=droite, 1=haut, 2=gauche, 3=bas
    int oid, nid;// valeur de l'id (oid) à changer en nouvel id (nid)
    bool trouve;

    trouve=false;// on va vérifier que le mur peut être supprimé
    
    switch(dir){
    case 0:// suppression d'un mur droit
      if(c==laby.largeur-1) break;// colonne invalide
      if(!laby.mursV[(c+1)+l*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[(c+1)+l*laby.largeur]) break; // déjà connecté
      oid = laby.cell[(c+1)+l*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursV[(c+1)+l*laby.largeur]=false;
      trouve=true;
      break;
    case 2:// suppression d'un mur gauche
      if(c==0) break;// colonne invalide
      if(!laby.mursV[c+l*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[(c-1)+l*laby.largeur]) break; // déjà connecté
      oid = laby.cell[(c-1)+l*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursV[c+l*laby.largeur]=false;
      trouve=true;
      break;
    case 1:// suppression d'un mur haut
      if(l==0) break;// ligne invalide
      if(!laby.mursH[c+l*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[c+(l-1)*laby.largeur]) break; // déjà connecté
      oid = laby.cell[c+(l-1)*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursH[c+l*laby.largeur]=false;
      trouve=true;
      break;
    case 3:// suppression d'un mur bas
      if(l==laby.hauteur-1) break;// ligne invalide
      if(!laby.mursH[c+(l+1)*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[c+(l+1)*laby.largeur]) break; // déjà connecté
      oid = laby.cell[c+(l+1)*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursH[c+(l+1)*laby.largeur]=false;
      trouve=true;
      break;   
    }//switch
    
    if(!trouve) continue;

    // un mur a été supprimé - maj des id des cellules voisines
    // version basique de la màj par parcours de toutes les
    // cellules du labyrinthe
    nb++;
    for(int i=0; i<laby.largeur; i++)
      for(int j=0; j<laby.hauteur; j++)
	if(laby.cell[i+j*laby.largeur]==oid) laby.cell[i+j*laby.largeur]=nid;
  }
}


void saisirCoordonnees(coordonnee &deb, coordonnee &fin, int largeur, int hauteur){
  cout << "Coordonnees début :" << endl;
  cout << "\tcolonne = ";
  cin >> deb.x;
  while (deb.x >= largeur || deb.x < 0) {
    cout << "\tValeur non valide ! x = ";
    cin >> deb.x;
  }
  cout << "\tligne = ";
  cin >> deb.y;
  while (deb.y >= hauteur || deb.y < 0) {
    cout << "\tValeur non valide ! y = ";
    cin >> deb.y;
  }

  cout << "Coordonnees fin :" << endl;
  cout << "\tcolonne = ";
  cin >> fin.x;
  while (fin.x >= largeur || fin.x < 0){
    cout << "\tValeur non valide ! x = ";
    cin >> fin.x;
  }
  cout << "\tligne = ";
  cin >> fin.y;
  while (fin.y >= hauteur || fin.y < 0) {
    cout << "\tValeur non valide ! y = ";
    cin >> fin.y;
  }
}