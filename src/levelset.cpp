#include "../include/levelset.hpp"
#include "image.hpp"

vector<real> c1_and_c2(const matrice<real>& f, const matrice<real>& phi)
{
    int l = f.nb_lignes();
    int c = f.nb_colonnes();
    real area1 = 0;
    real area2 = 0;
    real val1 = 0;
    real val2 = 0;

    for (int i = 1; i<=l ; i++)
    {
        for (int j = 1; j<=c ; j++)
        {
            if (phi(i,j) > 0)
            {
                area1 = area1 + 1;
                val1 = val1 + f(i,j);
            }
            else
            {
                area2 = area2 + 1;
                val2  = val2 + f(i,j);
            }
        }
    }
    vector<real> out;    
    out.push_back(val1/area1);
    out.push_back(val2/area2);
    return out;
}
