#include "SystemOfEquations.h"
#include "Jacobi.h"

#include "NoAvxSystemOfEquations.h"
#include "NoAvxJacobi.h"

#include "vectorclass/vectorclass.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <chrono>

using namespace std;
using namespace std::chrono;


int main() {

	int iters = 20;
	string dataSet = "system_8.txt";

	/* ---------------- AVX ---------------- */
	SystemOfEquations system(dataSet);
	Jacobi jacobi;

    high_resolution_clock::time_point start = high_resolution_clock::now();
	jacobi(system, iters);
    high_resolution_clock::time_point finish = high_resolution_clock::now();
	duration<double> time =  duration_cast<duration<double>>(finish - start);
	/* ---------------- AVX ---------------- */



	/* ---------------- NO AVX ---------------- */
	NoAvxSystemOfEquations noAvxSystem(dataSet);
	NoAvxJacobi noAvxJacobi;

	high_resolution_clock::time_point noAvxStart = high_resolution_clock::now();
	noAvxJacobi(noAvxSystem, iters);
	high_resolution_clock::time_point noAvxFinish = high_resolution_clock::now();
	duration<double> noAvxTime =  duration_cast<duration<double>>(noAvxFinish - noAvxStart);
	/* ---------------- NO AVX ---------------- */

	// drukuj wektor
	std::cout << "Rozwiazanie ukladu po " << iters << " iteracjach w czasie " << time.count() << "s:" << std::endl;
	std::copy(system.X, system.X + system.n, std::ostream_iterator<float>(std::cout, ", "));

	std::cout << endl;

	std::cout << "Rozwiazanie ukladu po " << iters << " iteracjach w czasie " << noAvxTime.count() << "s bez wykorzystania instrukcji wektorowych:" << std::endl;
	std::copy(noAvxSystem.X, noAvxSystem.X + noAvxSystem.n, std::ostream_iterator<float>(std::cout, ", "));

//	getchar();

	return 0;
}