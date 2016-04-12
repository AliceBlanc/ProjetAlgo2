#ifndef __IMAGEPNG_HPP__
#define __IMAGEPNG_HPP__
/**
 * @file imagepng.hpp
 * @author C. Jermann
 * @since 2016.03.23
 * @brief Fichier définissant une encapsulation de la bibliothèque C++ LodePNG (http://lodev.org/lodepng/)
**/

#include <string>
#include <vector>
#include <iostream>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 * @brief Structure représentant une couleur en codage Rouge, Vert, Bleu sur 24 bits
 * @attention Chaque composante doit avoir une valeur en 0 (foncé) et 255 (clair)
**/
struct Couleur
{
    unsigned R,V,B;
};

/**
 * @brief Opérateur d'affichage d'une couleur sous forme de triplet (R,V,B)
 * @param os Le flux d'affichage
 * @param c La couleur à afficher
 * @return Le flux après affichage
 * 
 * @b Complexité θ(1)
**/
std::ostream & operator<<(std::ostream & os, const Couleur & c);

/**
 * @brief Calcule la couleur moyenne d'un vecteur de couleurs
 * @param cs L'ensemble des couleurs à moyenner
 * @return La couleur moyenne
 * 
 * @b Complexité θ(cs.size())
**/
Couleur moyenne(std::vector<Couleur> cs);

/**
 * @brief Calcule la différence de luminance de deux couleurs
 * @param c1 La couleur 1
 * @param c2 La couleur 3
 * @return La différence de luminance entre c1 et c2
 * 
 * @b Complexité θ(1)
**/
unsigned diff_lum(Couleur c1, Couleur c2);


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 * @brief Classe ImagePNG qui encapsule la définition d'une image de la bibliothèque LodePNG
**/
class ImagePNG
{
    public:
        /** --------------------------------------------------------------------
         * @brief Constructeur d'une image vide
         * 
         * @b Complexité θ(1)
        **/
        ImagePNG();

        /** --------------------------------------------------------------------
         * @brief Constructeur d'une image blanche de taille LxH
         * @param L Largeur souhaitée
         * @param H Hauteur souhaitée
         * @pre L>0, H>0
         * 
         * @b Complexité θ(1)
        **/
        ImagePNG(unsigned L, unsigned H);

        /** --------------------------------------------------------------------
         * @brief Destructeur
         * 
         * @b Complexité θ(1)
        **/
        ~ImagePNG();

        /** --------------------------------------------------------------------
         * @brief Chargement d'une image depuis un fichier
         * @param fichierpng le nom du fichier contenant l'image au format PNG à charger
         * 
         * @b Complexité θ(L*H), L=largeur de l'image, H=hauteur de l'image
        **/
        void charger(std::string fichierpng);

        /** --------------------------------------------------------------------
         * @brief Enregistrement d'un fichier depuis une image
         * @param fichierpng le nom du fichier recevant l'image au format PNG
         * 
         * @b Complexité θ(L*H), L=largeur de l'image, H=hauteur de l'image
        **/
        void sauver(std::string fichierpng) const;

        /** --------------------------------------------------------------------
         * @brief Accès à la couleur d'un pixel de l'image
         * @param x abscisse du pixel
         * @param y ordonnée du pixel
         * @return couleur du pixel de coordonnées (x,y)
         * @pre (x,y) doit être valide (dans [0,_largeur-1]*[0,_hauteur-1])
         * 
         * @b Complexité θ(1)
        **/
        Couleur lirePixel(unsigned x, unsigned y) const;

        /** --------------------------------------------------------------------
         * @brief Modification de la couleur d'un pixel de l'image
         * @param x abscisse du pixel
         * @param y ordonnée du pixel
         * @param c couleur du pixel
         * @pre (x,y) doit être valide (dans [0,_largeur-1]*[0,_hauteur-1])
         * 
         * @b Complexité θ(1)
        **/
        void ecrirePixel(unsigned x, unsigned y, Couleur c);

        /** --------------------------------------------------------------------
         * @brief Largeur de l'image
         * 
         * @b Complexité θ(1)
        **/
        inline unsigned largeur() const {return _largeur;}

        /** --------------------------------------------------------------------
         * @brief Hauteur de l'image
         * 
         * @b Complexité θ(1)
        **/
        inline unsigned hauteur() const {return _hauteur;}

    private:
    // Attributs
        unsigned _largeur,_hauteur;
        std::vector<uint8_t> _pixels; // stockage de l'image
    // Fonction interne facilitatrice
        unsigned coord(unsigned x, unsigned y) const; // validation des coordonnées et calcul de l'indice correspondant
};

#endif
