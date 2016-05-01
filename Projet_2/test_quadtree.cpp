#include "imagepng.hpp"
#include "quadtree.hpp"
#include <iostream>
#include <unistd.h>

#define IMAGEPATH string("/Users/alice/Desktop/ProjetAlgo2/pngs/")

using namespace std;

int main()
{
    string fichier;
    ImagePNG originale,compressee;
    QuadTree arbre;

    fichier = "64-tuxette.png";
    originale.charger(IMAGEPATH+fichier);

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
    compressee.sauver(IMAGEPATH+"zip-d000-"+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Delta=64 :" << endl;
    arbre.importer(originale);
    arbre.compressionDelta(64);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-d64-"+fichier);
    
    cout << endl << "-------------------------------------------------" << endl;
    cout << "Delta=128 :" << endl;
    arbre.importer(originale);
    arbre.compressionDelta(128);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-d128-"+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Phi=4 :" << endl;
    arbre.importer(originale);
    arbre.compressionPhi(4);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-p04-"+fichier);
    
    cout << endl << "-------------------------------------------------" << endl;
    cout << "Phi=750 :" << endl;
    arbre.importer(originale);
    arbre.compressionPhi(750);
    //arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-p750-"+fichier);
}
