#ifndef LEVELSET_HPP
#define LEVELSET_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "image.hpp"
#include "matrice.hpp"
#include "parametres.hpp"
#include "image.hpp"

#pragma once

using namespace std;

class levelset: public matrice<real>
{
    protected:
    public:
        levelset(int n, int m);
        levelset(int n, int m, std::vector<real>);
        levelset(matrice<real>);

};


std::ostream& operator<<(std::ostream&, const levelset &);
std::istream& operator>>(std::istream&, levelset &);

vector<real> c1_and_c2(const matrice<real>& f, const matrice<real>& phi);

#endif
