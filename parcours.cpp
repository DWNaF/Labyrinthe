#include <iostream>

using namespace std;

#include "types.hpp"

/* ----------------------------------------------------------------- 
 * Fonctions liés aux FIFO, nécéssaires pour le parcours en largeur.
 * -----------------------------------------------------------------
*/
void initialiserFifo(Fifo &file)
// Initialisation de la file
{
  file.in = nullptr;
  file.out = nullptr;
}

bool estVide(Fifo file)
// Reenvoi true si la file est vide, false sinon.
{
  return (file.in == nullptr && file.out == nullptr);
}

void ajouter(Fifo &file, int v)
// Ajoute un element à la file
{
  // On crée l'elt à ajouter
  MaillonEntier *nv = new MaillonEntier;
  nv->valeur = v;
  nv->suiv = nullptr;
  nv->prec = nullptr;

  // On ajoute l'elt au début si la file estVide, sinon à la fin.
  if (estVide(file))
  {
    file.in = nv;
  }
  else
  {
    (file.out)->suiv = nv;
    nv->prec = file.out;
  }
  file.out = nv;
}

int retirer(Fifo &file)
// Retire un elt de la file et reenvoi sa valeur
{
  int val;
  if (estVide(file))
    return INDEFINI;
  else
  {
    if (file.in == file.out)
    {
      val = file.in->valeur;
      initialiserFifo(file);
    }
    else
    {
      MaillonEntier *temp = file.in;
      val = temp->valeur; // On récupère la valeur de l'elt retiré
      file.in = temp->suiv;
      file.in->prec = nullptr;

      delete temp; // On supprime l'adresse de l'elt retiré
    }
    return val;
  }
}

/* ----------------------------------------------------------------- 
 * Fonctions de parcours.
 * -----------------------------------------------------------------
*/
void fillPath(MatriceAdjacence mat, int sf, int *parent, chemin &path, int length)
// Complète le chemin minimal.
{
  if (parent[sf] != INDEFINI){
    // indice = indice + 1;
    fillPath(mat, parent[sf], parent, path, length - 1);
  }
  coordonnee *sommet = new coordonnee;
  sommet->x = int(sf/ mat.largeur);
  sommet->y = sf% mat.largeur;
  path.etape[length] = *sommet;
}

int getIndice(MatriceAdjacence mat, int c, int l){
  int indice = l*mat.largeur+c; 
  printf("(%d,%d) -> indice = %d\n", l, c, indice);
  return (indice < mat.ordre && indice >= 0 ? indice: INDEFINI);
}

chemin calculerChemin(const MatriceAdjacence &mat, coordonnee deb, coordonnee fin){
  chemin path;
  path.lg = 0;
  path.etape = nullptr;

  Fifo file;
  initialiserFifo(file);

  // On crée et initialises les tableaux coul, dist et parents.
  Couleur* coul = new Couleur[mat.ordre];
  int* dist = new int[mat.ordre];
  int* parent = new int[mat.ordre];
  for (int i = 0; i < mat.ordre; i++){
    coul[i] = BLANC;
    dist[i] = INFINI;
    parent[i] = INDEFINI;
  }

  int sommetDep = getIndice(mat, deb.x, deb.y);
  int sommetFin = getIndice(mat, fin.x, fin.y);

  if (sommetDep == INDEFINI || sommetFin == INDEFINI) {
    cout << "Coordonnées éronnés ou inexistants" << endl;
    return path;
  }

  coul[sommetDep] = GRIS;
  dist[sommetDep] = 0;

  ajouter(file, sommetDep);

  while (!estVide(file)){
    int curr = retirer(file);

    Maillon* vois = mat.lignes[curr];

    while (vois != nullptr){

      int indiceVois = getIndice(mat, vois->c, vois->l);
      if (coul[indiceVois] == BLANC){
        coul[indiceVois] = GRIS;
        dist[indiceVois] = dist[curr] + 1;
        parent[indiceVois] = curr;

        ajouter(file, indiceVois);
      }

      vois = vois->suiv;
    }
    coul[curr] = NOIR;
  }

  // Calcul de la longueur minimale du chemin
  path.lg = dist[sommetFin]+1;
  path.etape = new coordonnee[path.lg];

  // On complète le chemin minimal
  fillPath(mat, sommetFin, parent, path, path.lg-1);

  return path;
}