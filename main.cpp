#include "SystemOfEquations.h"
#include "Jacobi.h"

#include "vectorclass/vectorclass.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;


int main() {
	
	SystemOfEquations system("system_4096.txt");
	Jacobi jacobi;
	int iters = 20;
	jacobi(system, iters);

	// drukuj wektor
	std::cout << "Rozwiazanie ukladu po " << iters << " iteracjach:" << std::endl;
	std::copy(system.X, system.X + system.n, std::ostream_iterator<float>(std::cout, ", "));

	getchar();

	return 0;
}