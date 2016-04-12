/**
 * @file imagepng.cpp
 * @author C. Jermann
 * @since 2016.03.23
*/

#include "imagepng.hpp"
#include "lodepng.h"
#include <iostream>
#include <cassert>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Couleur & c)
{
    return os << "(" << c.R << "," << c.V << "," << c.B << ")";
}

//------------------------------------------------------------------------------
Couleur moyenne(std::vector<Couleur> cs)
{
    assert ( cs.size() > 0 );
    Couleur moy = {0,0,0};
    for (auto c : cs)
    {
        moy.R += c.R;
        moy.V += c.V;
        moy.B += c.B;
    }
    moy.R /= (unsigned)cs.size();
    moy.V /= (unsigned)cs.size();
    moy.B /= (unsigned)cs.size();
    return moy;
}

//------------------------------------------------------------------------------
unsigned diff_lum(Couleur c1, Couleur c2)
{
    return abs( (c1.R - c2.R) + (c1.V - c2.V) + (c1.B - c2.B) ) / 3;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ImagePNG::ImagePNG()
: _largeur(0), _hauteur(0) // initialisation à la déclaration
{}

//------------------------------------------------------------------------------
ImagePNG::ImagePNG(unsigned L, unsigned H)
: _largeur(L), _hauteur(H), _pixels(4*L*H,255) // initialisation à la déclaration
{}

//------------------------------------------------------------------------------
ImagePNG::~ImagePNG()
{} // rien à faire

//------------------------------------------------------------------------------
void ImagePNG::charger(std::string fichierpng)
{
    _pixels.clear();
    unsigned error = lodepng::decode(_pixels, _largeur, _hauteur, fichierpng.c_str());
    if(error)
    {
        std::cerr << "Erreur de chargement du fichier " << fichierpng << " : (" << error << ") " << lodepng_error_text(error) << std::endl;
        exit(1);
    }
}

//------------------------------------------------------------------------------
void ImagePNG::sauver(std::string fichierpng) const
{
    unsigned error = lodepng::encode(fichierpng.c_str(), _pixels, _largeur, _hauteur);
    if(error)
    {
        std::cerr << "Erreur d'enregistrement du fichier " << fichierpng << " : (" << error << ") " << lodepng_error_text(error) << std::endl;
        exit(1);
    }
}

//------------------------------------------------------------------------------
Couleur ImagePNG::lirePixel(unsigned x, unsigned y) const
{
    Couleur c;
    c.R = (unsigned)(_pixels[coord(x,y)]);
    c.V = (unsigned)(_pixels[coord(x,y)+1]);
    c.B = (unsigned)(_pixels[coord(x,y)+2]);
    return c;
}

//------------------------------------------------------------------------------
void ImagePNG::ecrirePixel(unsigned x, unsigned y, Couleur c)
{
    assert( c.R<=255);
    assert( c.V<=255);
    assert( c.B<=255);
    _pixels[coord(x,y)] = (uint8_t)c.R;
    _pixels[coord(x,y)+1] = (uint8_t)c.V;
    _pixels[coord(x,y)+2] = (uint8_t)c.B;
}

//------------------------------------------------------------------------------
unsigned ImagePNG::coord(unsigned x, unsigned y) const
{
    assert( x<=_largeur );
    assert( y<=_hauteur );
    return 4*(x+y*_largeur);
}