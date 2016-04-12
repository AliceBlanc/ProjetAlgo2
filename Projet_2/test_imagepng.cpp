#include "imagepng.hpp"
#include "quadtree.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    ImagePNG image;

    // vérifie la présence de noms de fichiers en paramètres
    if(argc < 3)
    {
    std::cerr << "please provide in and out filename" << std::endl;
    return 0;
    }

    image.charger(argv[1]);

    Couleur pixel;
    unsigned gris;
    for (unsigned x=0; x<image.largeur(); x++)
    {
        for (unsigned y=0; y<image.hauteur(); y++)
        {
            pixel = image.lirePixel(x,y);
            gris = (pixel.R + pixel.V + pixel.B)/3;
            pixel.R = pixel.V = pixel.B = gris;
            image.ecrirePixel(x,y,pixel);
        }
    }

    image.sauver(argv[2]);
}
