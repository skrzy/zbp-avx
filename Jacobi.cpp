#include "Jacobi.h"

#include <memory>
#include <sstream>
#include <iostream>


std::string Jacobi::avxToString(const Vec8f * A, int rows, int cols)
{
	std::ostringstream oss;
	Vec8f aux = 0;
	float *V = (float*)&aux; // by zapewnic wyrownanie

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols / 8; ++j) {
			A[i * cols / 8 + j].store_a(V);
			for (int q = 0; q < 8; ++q) {
				oss << V[q] << ", ";
			}
		}
		oss << std::endl;
	}

	return oss.str();
}


void Jacobi::operator()(SystemOfEquations &system, int iterations)
{
	// Etap 1.a:
	// Zaalokowac odpowiednio pamiec i wyrównac
	//Vec8f * Alpha = ...
	//Vec8f * Beta = ...
	//Vec8f * X = ...
	//Vec8f * X_prev = ...

	// Etap 2
	// uzupelnic X zerami
	

	// Etap 3
	// Zaimplementowac metode wyznaczajaca Alpha i Beta na podstawie A i B
	this->generateAlphaBeta(system.A, system.B, Alpha, Beta, system.n);

	std::cout << "Alpha = " << std::endl << avxToString(Alpha, system.n, system.n) << std::endl;
	std::cout << "Beta = " << std::endl << avxToString(Beta, 1, system.n) << std::endl;

	for (int i = 0; i < iterations; ++i) {
		/// Etap 4
		/// Zaimplementowac metode wykonujaca pojedyncza iteracje algorytmu Jacobiego
		std::cout << "X(" << i << ") = " << std::endl ;
		std::cout << avxToString(X_prev, 1, system.n) << std::endl;
		
		this->makeIteration(Alpha, Beta, X_prev, X, system.n);
		std::swap(X, X_prev);
	}

	// Etap 5
	// Skopiowac elementy z X do system.X
	

	// Etap 1.b
	// Zwolnic zaalokowana pamiec.
	
}


void Jacobi::generateAlphaBeta(float *A, float *B, Vec8f * Alpha, Vec8f * Beta, int n)
{
	
}


void Jacobi::makeIteration(const Vec8f * Alpha, const Vec8f * Beta, const Vec8f * X_prev, Vec8f * X, int n)
{
	
}


