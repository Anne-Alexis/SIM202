#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

//#include "..\include\image.hpp"
#include "..\include\levelset.hpp"
#include "..\include\resolution.hpp"
#include "..\include\parametres.hpp"

std::ofstream out;


int main()
{	
	std::cout<<"Initialisation :"<<std::endl;
	int taille=500;

	levelset f( deux_cercles(taille) );
	levelset phi_0( initialisation_generale(taille) );

	std::cout<<"Recherche du minimum :"<<std::endl;
	std::vector<real> c(c1_and_c2(f,phi_0));
	std::cout<<c[0]<<std::endl;
	std::cout<<c[1]<<std::endl;

	levelset phi_f( resolution_globale(phi_0,f) );

	
	phi_f.blanc_noir();
	phi_0.blanc_noir();

	std::cout<<"Résultat final :"<<std::endl;

	out.open("output/solution.ppm");
	out<< phi_f;
	out.close();

	out.open("output/depart.ppm");
	out<< phi_0;
	out.close();

	out.open("output/reference.ppm");
	out<< f;
	out.close();
}
