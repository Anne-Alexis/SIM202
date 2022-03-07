#include "../include/resolution.hpp"

#define PI 3.14159265

real heaviside(real x)
{
    return 0.5 + std::atan(x/epsilon)/PI;
}

real dirac(real x)
{
    return epsilon/(PI*(epsilon*epsilon + x*x));
}

void Euler_Explicite(const matrice<real> &phi_n, matrice<real> &phi_np1, const matrice<real> &f, real cm, real cp)
{
    int n= phi_n.nb_lignes();
    int m= phi_n.nb_colonnes();

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            int ir,ig,jh,jb;
            i==n ? ir=0 : ir = 1;
            i==1 ? ig=0 : ig = 1;
            j==n ? jb=0 : jb = 1;
            j==1 ? jh=0 : jh = 1;
            real gradip = phi_n(i+ir,j) -phi_n(i,j);
            real gradim = phi_n(i,j)    -phi_n(i-ig,j);
            real gradjp = phi_n(i,j+jb) -phi_n(i,j);
            real gradjm = phi_n(i,j)    -phi_n(i,j-jh);
            real gradi0 = 0.5*(gradip+gradim);
            real gradj0 = 0.5*(gradjp+gradjm);
            phi_np1(i,j)  = gradip/std::sqrt( eta*eta + gradip*gradip + gradj0*gradj0 );
            phi_np1(i,j) += gradjp/std::sqrt( eta*eta + gradjp*gradjp + gradi0*gradi0 );

            //
            int im;
            i==1 ? im=1 : im=i-1;
            im==n ? ir=0 : ir = 1;
            im==1 ? ig=0 : ig = 1;

            gradip = phi_n(im+ir,j) -phi_n(im,j);
            gradjp = phi_n(im,j+jb) -phi_n(im,j);
            gradjm = phi_n(im,j)    -phi_n(im,j-jh);
            gradj0 = 0.5*(gradjp+gradjm);
            phi_np1(i,j) -= gradip/std::sqrt( eta*eta + gradip*gradip + gradj0*gradj0 );

            //
            int jm;
            j==1 ? jm=1 : jm=j-1;
            jm==n ? jb=0 : jb = 1;
            jm==1 ? jh=0 : jh = 1;
            i==n ? ir=0 : ir = 1;
            i==1 ? ig=0 : ig = 1;

            gradip = phi_n(i+ir,jm) -phi_n(i,jm);
            gradim = phi_n(i,jm)    -phi_n(i-ig,jm);
            gradjp = phi_n(i,jm+jb) -phi_n(i,jm);
            gradi0 = 0.5*(gradip + gradim);
            phi_np1(i,j) -= gradjp/std::sqrt( eta*eta + gradjp*gradjp + gradi0*gradi0 );

            phi_np1(i,j) *= mu;
            phi_np1(i,j) += -nu - lambda1*( f(i,j)-cm )*( f(i,j)-cm ) + lambda2*( f(i,j)-cp )*( f(i,j)-cp ) ;
            phi_np1(i,j) *= dt*dirac( phi_n(i,j) );
            phi_np1(i,j) += phi_n(i,j);
        }
    }
}

matrice<real> resolution_globale(const matrice<real> &phi_0, const matrice<real> &f)
{
    std::vector<real> c( c1_and_c2(f ,phi_0) );
    matrice<real> phi_n=phi_0;
    matrice<real> phi_np1=phi_0;
    int cpt(0);


    while( ( c[0] > 0.0001 || c[1]< 0.9999 ) && cpt < 10000 )
    {
        cpt++;
        phi_n=phi_np1;
        c=c1_and_c2(f,phi_n);
        Euler_Explicite(phi_n, phi_np1, f, c[0] , c[1]);
    }

    std::cout<<"Erreur Linf :"<<(phi_n-phi_np1).normeinf()<<std::endl;
    std::cout<<"cm :"<<c[0]<<std::endl;
    std::cout<<"cp :"<<c[1]<<std::endl;
    std::cout<<"Nb itérations :"<<cpt<<std::endl;

    return phi_np1;
}

matrice<real> cercle(int taille)
{
    matrice<real> f(taille,taille);
    for(int i=1; i<=taille; i++)
    {
        for(int j=1; j<=taille; j++)
        {
            if( std::sqrt( (i-taille/2)*(i-taille/2)+(j-taille/2)*(j-taille/2) )  < taille/3 )
            {
                f(i,j)=1.0;
            }
            else
            {
                f(i,j)=0.0;
            }
        }
    }
    return f;
}

matrice<real> deux_cercles(int taille)
{
    matrice<real> f(taille,taille);
    for(int i=1; i<=taille; i++)
    {
        for(int j=1; j<=taille; j++)
        {
            if( std::sqrt( (i-taille/2)*(i-taille/2)+(j-taille/4)*(j-taille/4) )  < taille/6 )
            {
                f(i,j)=1.0;
            }
            else if (std::sqrt( (i-taille/2)*(i-taille/2)+(j-0.75*taille)*(j-0.75*taille) )  < taille/6)
            {
                f(i,j)=1.0;
            }
            else
            {
                f(i,j)=0.0;
            }
        }
    }
    return f;
}

matrice<real> carre(int taille)
{
    matrice<real> f(taille,taille);
    for(int i=1; i<=taille; i++)
    {
        for(int j=1; j<=taille; j++)
        {
            if( i> 0.75*taille || j> 0.75*taille || i<0.25*taille || j<0.25*taille)
            {
                f(i,j)=0.0;
            }
            else
            {
                f(i,j)=1.0;
            }
        }
    }

    return f;
}

matrice<real> initialisation_cercle(int taille)
{
    matrice<real> f(taille,taille);
    for(int i=1; i<=taille; i++)
    {
        for(int j=1; j<=taille; j++)
        {
            f(i,j) = std::sqrt( (i-taille/2)*(i-taille/2)+(j-taille/2)*(j-taille/2) ) - (taille/3 - 8);

        }
    }
    return f;
}

std::ostream& operator<<(std::ostream& stream, const matrice<double>& imag){
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



std::istream& operator>>(std::istream& stream, matrice<real>& imag){
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

    matrice<real> sortie(n,m,data);
    imag=sortie;

    return stream;
}



