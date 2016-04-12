#include <bitset>
#include <iostream>
#include <cassert>
#include <cmath>
#include "quadtree.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Interface publique
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
QuadTree::QuadTree()
{
    _taille = 0;
    _racine.pere = nullptr;
    for(int i = 0; i < 4; i++){
        _racine.fils[i] = nullptr;
    }
    _racine.rvb.R = 0;
    _racine.rvb.V = 0;
    _racine.rvb.B = 0;
}

//------------------------------------------------------------------------------
QuadTree::~QuadTree()
{
    for(int i = 0; i < 4; i++){
        if(_racine.fils[i] != nullptr){
            delete _racine.fils[i];
            _racine.fils[i] = nullptr;
        }
    }
}

//------------------------------------------------------------------------------
void QuadTree::afficher() const
{
    if ( _taille == 0 )
    {
        cout << "Quadtree vide." << endl;
    }
    else
    {
        // utilise une fonction privée récursive
        afficher_rec(&_racine);
    }
}

//------------------------------------------------------------------------------
void QuadTree::importer(const ImagePNG & img)
{
    _taille = img.largeur() ; // par principe la largeur = longueur = 2^n
    importerDepuis(img, 0,         0,         _taille/2, _racine.fils[0]);
    importerDepuis(img, 0,         _taille/2, _taille/2, _racine.fils[1]);
    importerDepuis(img, _taille/2, 0,         _taille/2, _racine.fils[2]);
    importerDepuis(img, _taille/2, _taille/2, _taille/2, _racine.fils[3]);
    
    
// À COMPLÉTER
}

void QuadTree::importerDepuis(const ImagePNG & img, int x, int y, int taille, Noeud* unNoeud) {
    if (taille > 1) {
        for (int i = 0 ;i < 4 ; ++i)
        {
            unNoeud->fils[i] = new Noeud() ;
            unNoeud->fils[i]->pere = unNoeud ;
        }
        std::vector<Couleur> couleursFils ;
        importerDepuis(img, x,           y,           _taille/2, unNoeud->fils[0]);
        importerDepuis(img, x,           y+_taille/2, _taille/2, unNoeud->fils[1]);
        importerDepuis(img, x+_taille/2, y,           _taille/2, unNoeud->fils[2]);
        importerDepuis(img, x+_taille/2, y+_taille/2, _taille/2, unNoeud->fils[3]);
        for(int i = 0 ; i < 4 ; ++i) {
            couleursFils.push_back(unNoeud->fils[i]->rvb) ;
        }
        unNoeud->rvb = moyenne(couleursFils) ;
    } else {
        unNoeud->rvb = img.lirePixel(x, y) ;
    }
}

//------------------------------------------------------------------------------
ImagePNG QuadTree::exporter() const
{
    ImagePNG img;
// À COMPLÉTER
    return img;
}

//------------------------------------------------------------------------------
void QuadTree::compressionDelta(unsigned delta)
{
// À COMPLÉTER
}

//------------------------------------------------------------------------------
void QuadTree::compressionPhi(unsigned phi)
{
// À COMPLÉTER
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Fonctions facilitatrices (privées)
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
/*static*/ QuadTree::bit QuadTree::kiemeBit(unsigned n, unsigned k)
{
    
    bit b = 0;
    if ( k < 31 )
    {
        std::bitset<32> bits(n);
        b = bits[k];
    }
    return b;    
}

//------------------------------------------------------------------------------
/*static*/ void QuadTree::afficher_rec(const Noeud * n, string tabs/*=""*/)
{
    if (n != nullptr)
    {   // affichage du noeud
        cout << tabs << "- " << n << " de " << n->pere << " vers ";
        for (auto f : n->fils)
        {
            cout << f << " ";
        }
        cout << "RVB=" << n->rvb << endl;
        // et de ses fils récursivement
        for (auto f : n->fils)
        {
            afficher_rec(f,tabs+"   ");
        }
    }
}
