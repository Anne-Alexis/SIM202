#include <iostream>
#include <fstream>
#include <vector>
#include "image.hpp"
#include "matrice.hpp"
#include "parametres.hpp"
#include "image.hpp"

#pragma once

using namespace std;
/*
matrice<real> image_en_matrice(const ImageGrayscale &f)
{
    matrice<real> res(f.h, f.w);

    //Mettre les valeurs des pixels dans res ata.

    return res;
}
*/
// function to compute c1 and c2

vector<real> c1_and_c2(const matrice<real>& f, const matrice<real>& phi);
