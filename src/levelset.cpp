#include "../include/levelset.hpp"


levelset::levelset(int n, int m)
: matrice<real>(n,m)
{}

levelset::levelset(int n, int m, std::vector<real> V) 
: matrice<real>(n,m,V)
{}

levelset::levelset(matrice<real> A)
: matrice<real>(A)
{}


std::ostream& operator<<(std::ostream& stream, const levelset& imag)
{
    // fill the metadata header 
    stream << "P2" << endl;
    stream << imag.nb_colonnes() << " " << imag.nb_lignes() << endl;
    stream << 1 << endl;
    for  (int i=1; i<=imag.nb_lignes(); i++){
        for (int j=1; j<=imag.nb_colonnes(); j++){
            stream << imag(i,j) << " ";
        }
        stream << endl;
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, levelset& imag)
{
    std::string type;
    stream >> type;
    if (type != "P5") {
        cout << "file type must be P5. Read " << type << endl;
        exit(-1);
    }
    int n, m;
    stream >> m;
    stream >> n;
    int max_val;
    stream >> max_val;
    int num_pix=n*m;
    std::vector<real> data(num_pix);
    for (int i = 0; i < num_pix; i++)
    {
        stream >> data[i];
    }

    levelset sortie(n,m,data);
    imag=sortie;

    return stream;
}

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
