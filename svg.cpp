#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

#include "types.hpp"
#include "parcours.hpp"

// --------------------------------------------------------------------
// définition des fonctions liées à l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

bool ouvrirFichierSVG(const string &nomFichier, ofstream &out,
                      int largeur, int hauteur)
{
  out.open(nomFichier);

  if (!out.is_open())
  {
    cout << "erreur d'ouverture du fichier de dessin " << nomFichier << endl;
    return false;
  }

  // sortie de l'entête
  out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";
  out << "width=\"" << largeur << "\" height=\"" << hauteur << "\">" << endl;

  return true;
}

void fermerFichierSVG(ofstream &out)
{
  // fermeture de la balise svg
  out << "</svg>" << endl;

  out.close();
}

void text(ofstream &out, int x, int y, int size, const string &txt, const string &color)
{

  out << "<text x=\"" << x << "\" y=\"" << y << "\"";
  out << " font-family=\"Verdana\" font-size=\"" << size << "\"";
  out << " text-anchor=\"middle\" ";
  out << " dominant-baseline=\"middle\" ";
  out << "fill=\"" << color << "\" >" << endl;
  out << txt << endl;
  out << "</text>" << endl;
}

void ligne(ofstream &out, int x1, int y1, int x2, int y2, const string &color, int width)
{
  out << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\"";
  out << " x2=\"" << x2 << "\" y2=\"" << y2;
  out << "\" stroke=\"" << color << "\"";
  out << " stroke-width=\"" << width << "\""
      << " />" << endl;
}

void rect(ofstream &out, int x, int y, int width, int height, const string &color)
{
  out << "<rect width=\"" << width << "\" height=\"" << height << "\"";
  out << " x=\"" << x << "\" y=\"" << y << "\" fill=\"" << color << "\"";
  out << " />" << endl;
}

void labTemplate(labyrinthe &laby, const string &nomFichier, ofstream &out)
{
  // dessin du fond
  rect(out, 0, 0,
       laby.largeur * CELLSIZE + 2 * MARGE,
       laby.hauteur * CELLSIZE + 2 * MARGE, "white");

  // dessin des murs verticaux
  for (int c = 0; c < laby.largeur + 1; c++)
    for (int l = 0; l < laby.hauteur; l++)
      if (laby.mursV[c + l * laby.largeur])
      { // dessiner un mur vertical
        ligne(out,
              c * CELLSIZE + MARGE, l * CELLSIZE + MARGE,
              c * CELLSIZE + MARGE, (l + 1) * CELLSIZE + MARGE,
              "black", 3);
      }

  // dessin des murs horizontaux
  for (int c = 0; c < laby.largeur; c++)
    for (int l = 0; l < laby.hauteur + 1; l++)
      if (laby.mursH[c + l * laby.largeur])
      { // dessiner un mur horizontal
        ligne(out,
              c * CELLSIZE + MARGE, l * CELLSIZE + MARGE,
              (c + 1) * CELLSIZE + MARGE, l * CELLSIZE + MARGE,
              "black", 3);
      }
}

void dessinerLabyrinthe(labyrinthe &laby, const string &nomFichier)
{
  ofstream out;

  if (!ouvrirFichierSVG(nomFichier, out,
                          laby.largeur * CELLSIZE + 2 * MARGE,
                          laby.hauteur * CELLSIZE + 2 * MARGE))
      return;

  // dessin du labyrinthe à vide
  labTemplate(laby, nomFichier, out);

  fermerFichierSVG(out);
}


void dessinerMatrice(const MatriceAdjacence &mat, const labyrinthe &laby, const string &nom)
{
  ofstream out;

  if (!ouvrirFichierSVG(nom, out,
                        laby.largeur * CELLSIZE + 2 * MARGE,
                        laby.hauteur * CELLSIZE + 2 * MARGE))
    return;

  // dessin du labyrinthe à vide
  labTemplate(const_cast<labyrinthe &>(laby), nom, out);

  // dessin du graphe de parcours
  for (int i = 0; i < mat.ordre; i++)
  {

    // Cordonnées du sommet
    int l = int(i / mat.largeur);
    int c = i % mat.largeur;
    Maillon *ptr = mat.lignes[i];
    while (ptr != nullptr)
    {
      ligne(out,
            c * CELLSIZE + MARGE + CELLSIZE / 2, l * CELLSIZE + MARGE + CELLSIZE / 2,
            ptr->c * CELLSIZE + MARGE + CELLSIZE / 2, (ptr->l) * CELLSIZE + MARGE + CELLSIZE / 2,
            "blue", 1);
      ptr = ptr->suiv;
    }
  }

  fermerFichierSVG(out);
}

void dessinerSolution(const labyrinthe &laby, const chemin &ch, const string &nomFichier)
{
  if (ch.lg > 0)
  { // si il existe un chemin (par sécurité, mais ce n'est pas nécéssaire car les labs sont parfaits)
    ofstream out;

    if (!ouvrirFichierSVG(nomFichier, out,
                          laby.largeur * CELLSIZE + 2 * MARGE,
                          laby.hauteur * CELLSIZE + 2 * MARGE))
      return;

    // dessin du template du labyrinthe
    labTemplate(const_cast<labyrinthe &>(laby), nomFichier, out);

    // dessin du chemin
    for (int i = 1; i < ch.lg; i++)
    {
      // Cordonnées du sommet 1
      int l1 = ch.etape[i - 1].x;
      int c1 = ch.etape[i - 1].y;

      // Coordonnées du sommet 2
      int l2 = ch.etape[i].x;
      int c2 = ch.etape[i].y;

      ligne(out,
            c1 * CELLSIZE + MARGE + CELLSIZE / 2, l1 * CELLSIZE + MARGE + CELLSIZE / 2,
            c2 * CELLSIZE + MARGE + CELLSIZE / 2, l2 * CELLSIZE + MARGE + CELLSIZE / 2,
            "blue", 1);
    }

    fermerFichierSVG(out);
  }
}