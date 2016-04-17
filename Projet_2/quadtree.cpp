#include <bitset>
#include <iostream>
#include <cassert>
#include <cmath>
#include "quadtree.hpp"


#define luminescence(f) (abs(0.0f+((f)->rvb.R + (f)->rvb.V + (f)->rvb.B) - ((f)->pere->rvb.R + (f)->pere->rvb.V + (f)->pere->rvb.B))/3.0f)

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
    
    // Utilise une fonction privée récursive pour décomposer l'image en quadtree
    importerDepuis(img, 0, 0, _taille, &_racine);
    
}

//------------------------------------------------------------------------------
void QuadTree::importerDepuis(const ImagePNG & img, int x, int y, int taille, Noeud* unNoeud) {
    if (taille > 1) {
        for (int i = 0 ;i < 4 ; ++i)
        {
            unNoeud->fils[i] = new Noeud() ;
            unNoeud->fils[i]->pere = unNoeud ;
        }
        importerDepuis(img, x,           y,           taille/2, unNoeud->fils[0]);
        importerDepuis(img, x,           y+taille/2,  taille/2, unNoeud->fils[1]);
        importerDepuis(img, x+taille/2,  y,           taille/2, unNoeud->fils[2]);
        importerDepuis(img, x+taille/2,  y+taille/2,  taille/2, unNoeud->fils[3]);
        // Calcul de la couleur moyenne des fils
        std::vector<Couleur> couleursFils ;
        for(int i = 0 ; i < 4 ; ++i) {
            couleursFils.push_back(unNoeud->fils[i]->rvb) ;
        }
        unNoeud->rvb = moyenne(couleursFils) ;
    } else {
        // Si la taille est de 1, alors c'est un pixel. Récupérer la couleur du pixel de l'image.
        unNoeud->rvb = img.lirePixel(x, y) ;
    }
}

//------------------------------------------------------------------------------
ImagePNG QuadTree::exporter() const
{
    ImagePNG img = *new ImagePNG(_taille, _taille);
    
    // img._hauteur = _taille ;
    // img._largeur = _taille ;
    
    exporterVers(img, 0, 0, _taille,  &_racine) ;
    return img;
}

void QuadTree::exporterVers(ImagePNG& img, int x, int y, int taille, const Noeud* unNoeud) const
{
    if (taille > 1) {
        for(int i = 0 ; i < 4 ; ++i) {
            if(unNoeud->fils[i]) {
                exporterVers(img, x + ((i>>1)*(taille/2)), y + ((i&1)*taille/2), taille/2, unNoeud->fils[i] );
            } else {
                ecrirePixels(img, x, y, taille/2, unNoeud->rvb) ;
            }
        }

    } else {
        // Si la taille est de 1, alors c'est un pixel. Ecrire le pixel et sa couleur.
        ecrirePixels(img, x, y, taille, unNoeud->rvb) ;
    }
}

void QuadTree::ecrirePixels(ImagePNG& img, int x, int y, int taille, Couleur c) const
{
    if(taille <= 1) {
        img.ecrirePixel(x, y, c) ;
    } else {
        for(int a = 0 ; a < taille ; ++a) {
            for(int b = 0 ; b < taille ; ++b) {
                img.ecrirePixel(x+a, y+b, c) ;
            }
        }
    }
}

bool QuadTree::estPere(Noeud unNoeud){
    return unNoeud.fils[0]!=nullptr;
}

//------------------------------------------------------------------------------
void QuadTree::compressionDelta(unsigned delta)
{
    compressionDeltaRecurse(delta, &_racine) ;
}

void QuadTree::compressionDeltaRecurse(unsigned int delta, Noeud* unNoeud)
{
    bool aDesPetitsEnfants = false;
    for (auto f : unNoeud->fils)
        aDesPetitsEnfants = aDesPetitsEnfants | (f != nullptr && (f->fils[0]!=nullptr || f->fils[1]!=nullptr || f->fils[2]!=nullptr || f->fils[3]!=nullptr)) ;
    
    if(aDesPetitsEnfants) // Si un noeud a des petits enfants (profondeur arbre sous-jacent > 2) alors recursion sur les fils
    {
        aDesPetitsEnfants = false ;
        for(auto f : unNoeud->fils) {
            compressionDeltaRecurse(delta, f) ;
            // Refaire le calcul des petits enfants après la compression de l'arbre sous-jascent
            aDesPetitsEnfants = aDesPetitsEnfants | (f != nullptr && ( f->fils[0]!=nullptr || f->fils[1]!=nullptr || f->fils[2]!=nullptr || f->fils[3]!=nullptr)) ;
        }
    }
    
    
    
    if(! aDesPetitsEnfants) {// Verifier si l'arbre sous-jacent a des petits enfants (profondeur > 2)
        float max = 0.0f ;
        for (auto f : unNoeud->fils) {
            float tmp = luminescence(f) ;
            if(tmp > max)
                max = tmp ;
        }
        if(max <= delta) { // Suppression des fils
            for (int i = 0 ; i < 4 ; ++i) {
                delete unNoeud->fils[i] ;
                unNoeud->fils[i] = nullptr ;
            }
        }
    }
    
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