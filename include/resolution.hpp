#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <fstream>

#include "levelset.hpp"
#include "matrice.hpp"
#include "parametres.hpp"

real heaviside(real x);
real dirac(real x);

void Euler_Explicite(const matrice<real> & phi_n, matrice<real> &phi_np1,const matrice<real> &f ,real cm, real cp);
void Euler_Implicite(const matrice<real> & phi_n, matrice<real> &phi_np1,const matrice<real> &f , real cm, real cp);

matrice<real> resolution_globale(const matrice<real> &phi_0, const matrice<real> &f);


//Quelques fonctions cible
matrice<real> cercle(int taille_matrice);
matrice<real> deux_cercles(int taille_matrice); 
matrice<real> carre(int taille_matrice);

//Initialisation de phi_0
matrice<real> initialisation_cercle(int taille);
matrice<real> initialisation_generale(int taille);

#endif