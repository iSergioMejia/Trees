#include <iostream>
#include "kDTree.h"
#include "kDPoint.h"
#include <vector>
#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
		std::vector<PUJ::kDPoint> points;

	std::ifstream in("in2.txt");
	double x, y, z;
	if(in)
	{
		while(!in.eof())
		{
			std::string leido;
			getline(in, leido);
			std::stringstream token(leido);
			token >> x >> y >> z;
			PUJ::kDPoint punto(x,y,z);
			points.push_back(punto);
		}
		in.close();
	}

	PUJ::kDTree<PUJ::kDPoint> tree(points);
	std::cout << "Arbol creado correctamente\n";
	//std::cout << "PreOrder Print: \n";
	//tree.PrintPreOrder();
	std::cout << "Ingrese las coordenadas x y z de un punto: ";
	std::cin >> x >> y >> z;
	while(x!=-1 || y!=-1 || z!=-1)
	{
		PUJ::kDPoint punto(x,y,z);
		const PUJ::kDPoint *point = tree.Find(punto);
		if(point != NULL) std::cout << "Point found: (" << point->getX() << ", " << point->getY() << ", " << point->getZ() << ")" << std::endl;
		else std::cout << "Error, no hay punto\n";
		std::cout << "Ingrese las coordenadas x y z de un punto: ";
		std::cin >> x >> y >> z;
	}


}
