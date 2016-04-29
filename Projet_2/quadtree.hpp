#ifndef __QUADTREE_HPP__
#define __QUADTREE_HPP__
/**
 * @file quadtree.hpp
 * @author 
 * @since 
 * @brief Fichier définissant une classe QuadTree pour représenter, 
 * et compresser, des images bitmap
 * 
 * À COMPLÉTER
**/

#include <queue>
#include <vector>
#include <map>
#include <set>
#include "imagepng.hpp"

/**
 * @brief Classe QuadTree qui représente une image bitmap sous forme arborescente
 * 
 * À COMPLÉTER
**/

typedef std::map<int, std::set<unsigned>> MAP_LUMINESCENCE_TO_PATH ;
class QuadTree
{
    public:
        /** --------------------------------------------------------------------
         * @brief Constructeur d'un quadtree vide
         * 
         * @b Complexité À COMPLÉTER
        **/
        QuadTree();

        /** --------------------------------------------------------------------
         * @brief Destructeur d'un quadtree
         * 
         * @b Complexité À COMPLÉTER
        **/
        ~QuadTree();

        /** --------------------------------------------------------------------
         * @brief Affichage textuel préfixe indenté du Quadtree
         * @attention À fin de débogage
         * 
         * @b Complexité À COMPLÉTER
        **/
        void afficher() const;

        /** --------------------------------------------------------------------
         * @brief Encodage d'une image dans le QuadTree
         * @param img L'image à représenter
         * @pre L'image est de taille 2^n * 2^n, avec n>0
         * 
         * @b Complexité À COMPLÉTER
        **/
        void importer(const ImagePNG & img);

        /** --------------------------------------------------------------------
         * @brief Exportation d'une image depuis le QuadTree
         * @return l'image bitmap correspondant au contenu du QuadTree
         * 
         * @b Complexité À COMPLÉTER
        **/
        ImagePNG exporter() const;

        /** --------------------------------------------------------------------
         * @brief Compression du QuadTree
         * @param delta le seuil maximal de différence de luminance (cf. sujet).
         * La valeur par défaut, delta=0, provoque une compression sans dégradation.
         * @pre delta<255
         * 
         * @b Complexité À COMPLÉTER
        **/
        void compressionDelta(unsigned delta);

        /** --------------------------------------------------------------------
         * @brief Compression du QuadTree
         * @param phi le nombre maximal de feuilles après compression (cf. sujet).
         * @pre phi>0 car on ne peut supprimer la racine
         * 
         * @b Complexité À COMPLÉTER
        **/
        void compressionPhi(unsigned phi);


    private:
    //////////////////////////////////////////////////////////////////////////////////////
    // Attributs et types internes représentant la structure arborescente
    //////////////////////////////////////////////////////////////////////////////////////

        // Taille de l'image représentée
        unsigned _taille;

        // Type des noeuds de l'arbre (structure pere-fils)
        struct Noeud
        {
            Noeud* pere; // nullptr si racine
            Noeud* fils[4]; // nullptr si feuille
            Couleur rvb; // du pixel si feuille, moyenne des fils sinon
        };
        
        // Noeud racine
        Noeud _racine;
        
    //////////////////////////////////////////////////////////////////////////////////////
    // Fonctionnalités internes simplifiant l'implémentation des méthodes
    //////////////////////////////////////////////////////////////////////////////////////

        // Type interne représentant 1 bit (valeur 0 ou 1)
        typedef bool bit;

        // Fonction statique retournant la valeur du k-ième bit d'un entier positif n
        static bit kiemeBit(unsigned n, unsigned k);

        // Fonction statique réalisant l'affichage récursivement depuis le noeud *n
        static void afficher_rec(const Noeud * n, std::string tabs="");

        // EN AJOUTER AU BESOIN ...
        // Difference de luminescence
        float differenceLuminescence(const Couleur& couleurF, const Couleur& couleurN ) const ;
    
        //Fonction importer depuis
        void importerDepuis(const ImagePNG & img, int x, int y, int taille, Noeud* unNoeud);
        void exporterVers(ImagePNG& img, int x, int y, int taille, const Noeud* noeud) const;
        void ecrirePixels(ImagePNG& img, int x, int y, int taille, Couleur c) const ;

        //Fonction estPere
        bool estPere(Noeud unNoeud);
    
    
        // Compression
        void compressionDeltaRecurse(unsigned int delta, Noeud* unNoeud) ;
        void rechercheLuminescences(Noeud*unNoeud, unsigned chemin, unsigned profondeur, MAP_LUMINESCENCE_TO_PATH &luminescences) ;


};

#endif
