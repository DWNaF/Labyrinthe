#include <iostream>

#include "types.hpp"
#include "svg.hpp"

using namespace std;

void creerMatrice(MatriceAdjacence &m, int nbSommets)
{
  // initialisation du nombre de lignes/colonnes de la matrice
  m.ordre = nbSommets;
  // allocation mémoire du tableau de lignes
  m.lignes = new Maillon *[nbSommets];
  // initialisation de chaque ligne à "vide"
  for (int i = 0; i < nbSommets; i++)
    m.lignes[i] = nullptr;
}

void effacerMatrice(MatriceAdjacence &mat)
{
  for (int l = 0; l < mat.ordre; l++)
  { // effacer chaque ligne
    while (mat.lignes[l] != nullptr)
    { // tq la ligne n'est pas vide
      // effacer le premier élément qui s'y trouve
      Maillon *cour = mat.lignes[l]; // 1er élément de la liste
      mat.lignes[l] = cour->suiv;    // élément suivant éventuel
      delete cour;                   // effacer le 1er élement courant
    }
  }
  // effacer le tableau de lignes
  delete mat.lignes;
  // raz de la taille et largeur
  mat.ordre = 0;
  mat.largeur = 0;
}

void afficherMatrice(MatriceAdjacence &mat)
{
  int lig, col;
  for (int i = 0; i < mat.ordre; i++)
  {
    lig = int(i / mat.largeur);
    col = i % mat.largeur;
    printf("noeud %d (%d,%d) :", i, lig, col);

    Maillon *ptr = mat.lignes[i];
    while (ptr != nullptr)
    {
      printf(" (%d,%d) ", ptr->l, ptr->c);
      ptr = ptr->suiv;
    }
    cout << endl;
  }
}

void appendMaillon(MatriceAdjacence &mat, int curr, int voisin)
{
  if (mat.ordre == 0 || voisin >= mat.ordre || voisin < 0)
    return;

  // Création du voisin
  Maillon *vois = new Maillon;
  vois->l = int(voisin / mat.largeur);
  vois->c = voisin % mat.largeur;
  vois->suiv = nullptr;

  // On va jusqu'au dernier élément
  if (mat.lignes[curr] == nullptr)
    mat.lignes[curr] = vois;
  else
  {
    Maillon *ptr = mat.lignes[curr];
    while (ptr->suiv != nullptr)
    {
      ptr = ptr->suiv;
    }
    ptr->suiv = vois;
  }
}

void remplirMatrice(MatriceAdjacence &mat, const labyrinthe &lab)
{
  int nbCell = lab.largeur * lab.hauteur;

  creerMatrice(mat, nbCell);
  mat.largeur = lab.largeur;

  // On parcours chaque sommet (case de la grille / chaque 'lignes' de la matrice)
  for (int i = 0; i < mat.ordre; i++)
  {
    // On ajoute les voisins de chaque sommet
    if (!lab.mursH[i])
    { // pas de mur en haut de i, donc i et i-largeur sont voisins
      appendMaillon(mat, i, i - mat.largeur);
      appendMaillon(mat, i - mat.largeur, i);
    }

    if (!lab.mursV[i + 1])
    { // pas de mur à droite de i, donc i et i+1 sont voisins
      appendMaillon(mat, i, i + 1);
      appendMaillon(mat, i + 1, i);
    }
  }
}

