#include "imagepng.hpp"
#include "quadtree.hpp"
#include <iostream>
#include <unistd.h>
#include <ctime> 	// time(), clock_t, clock(), CLOCKS_PER_SEC

#define IMAGEPATH string("/Users/alice/Desktop/ProjetAlgo2/pngs/")

using namespace std;


// -----------------------------------------
// Éléments de mesure de performance

/**
 * @var chronom
 * @brief chronomètre du programme
 **/
clock_t chronom;

/**
 * @def START
 * @brief démarre le chronomètre
 **/
#define START chronom=clock();

/**
 * @def STOP
 * @brief arrête le chronomètre
 **/
#define STOP chronom=clock()-chronom;

/**
 * @def TEMPS
 * @brief donne le temps du chronomètre (après arrêt)
 **/
#define TEMPS double(chronom)/CLOCKS_PER_SEC


void complexiteTemporelleDelta(ImagePNG originale){
    cout << "Fonction compression delta :" << endl;
    // Lexique
    unsigned int nb=10000;          	// nombres de répétitions pour l'analyse
    double smoy, addition;                 // indicateurs statistiques de performance
    
    smoy = 0.0;   	// temps moyen sur tous les tirages
    for(int delta=20;delta<500;delta++){
        QuadTree arbre;
        arbre.importer(originale);

    for (int i = 0; i < nb; i++){
        
                START;              	// démarrage du chronomètre
        arbre.compressionDelta(delta);
        STOP;               	// arrêt du chronomètre
        // Mise à jour de l'indicateur en fonction du résultat
        addition += TEMPS;
        //smoy = addition/nb;
    }
    }
    smoy=addition/nb;
    // Affichage des indicateurs statistiques calculés
    //cout << "Analyse statistique (sur " << nb << " recherches, avec un anneau de taille " << tailleAnneau << " ) : " << endl;
    cout << " - coût moyen   : " << smoy << "s pour " << endl;
}

int main()
{
    string fichier;
    ImagePNG originale,compressee;
    QuadTree arbre;

    fichier = "4.png";
    originale.charger(IMAGEPATH+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Original :" << endl;
    arbre.importer(originale);
    //arbre.afficher();

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Sans perte :" << endl;
    arbre.importer(originale);
    arbre.compressionDelta(0);
    arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-d000-"+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Delta :" << endl;
    arbre.importer(originale);
    complexiteTemporelleDelta(originale);
    //arbre.compressionDelta(64);
    //arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-d64-"+fichier);
    
    cout << endl << "-------------------------------------------------" << endl;
    cout << "Delta=3 :" << endl;
    arbre.importer(originale);
    arbre.compressionDelta(3);
    //arbre.afficher();
    compressee = arbre.exporter();
    compressee.sauver(IMAGEPATH+"zip-d128-"+fichier);

    cout << endl << "-------------------------------------------------" << endl;
    cout << "Phi=4 :" << endl;
    arbre.importer(originale);
    arbre.compressionPhi(4);
    //arbre.afficher();
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
