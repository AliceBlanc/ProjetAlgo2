#include "imagepng.hpp"
#include "quadtree.hpp"
#include <iostream>

using namespace std;

int main()
{
    string fichier;
    ImagePNG originale,compressee;
    QuadTree arbre;

    fichier = "i.png";
    originale.charger(fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Original :" << endl;
    arbre.importer(originale);
    arbre.afficher();

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Sans perte :" << endl;
    arbre.importer(originale);
    arbre.compressionDelta(0);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver("zip-d000-"+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Delta=128 :" << endl;
    arbre.importer(originale);
    arbre.compressionDelta(128);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver("zip-d128-"+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Phi=4 :" << endl;
    arbre.importer(originale);
    arbre.compressionPhi(4);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver("zip-p004-"+fichier);
}
