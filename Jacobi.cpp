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
	// Zaalokowac odpowiednio pamiec i wyrownac
	size_t bytesMatrix = (system.n / 8) * system.n * sizeof(Vec8f);
    size_t bytesVector = (system.n / 8) * sizeof(Vec8f);

	size_t spaceAlpha = bytesMatrix + sizeof(Vec8f);
	size_t spaceBeta = bytesVector + sizeof(Vec8f);
    size_t spaceX = bytesVector + sizeof(Vec8f);
    size_t spaceX_prev = bytesVector + sizeof(Vec8f);

	void * unalignedAlpha = malloc(spaceAlpha);
	void * unalignedBeta = malloc(spaceBeta);
    void * unalignedX = malloc(spaceX);
    void * unalignedX_prev = malloc(spaceX_prev);

	void *tempAlpha = unalignedAlpha;
    void *tempBeta = unalignedBeta;
    void *tempX = unalignedX;
    void *tempX_prev = unalignedX_prev;

	Vec8f * Alpha = (Vec8f*)std::align(sizeof(Vec8f), bytesMatrix, tempAlpha, spaceAlpha);
    Vec8f * Beta = (Vec8f*)std::align(sizeof(Vec8f), bytesVector, tempBeta, spaceBeta);
    Vec8f * X = (Vec8f*)std::align(sizeof(Vec8f), bytesVector, tempX, spaceX);
    Vec8f * X_prev = (Vec8f*)std::align(sizeof(Vec8f), bytesVector, tempX_prev, spaceX_prev);

	// Etap 2
	// uzupelnic X zerami
	for (int i = 0; i < system.n / 8; i++) {
        X_prev[i] = .0;
        X[i] = .0;
    }

	// Etap 3
	// Zaimplementowac metode wyznaczajaca Alpha i Beta na podstawie A i B
	this->generateAlphaBeta(system.A, system.B, Alpha, Beta, system.n);

//	std::cout << "Alpha = " << std::endl << avxToString(Alpha, system.n, system.n) << std::endl;
//	std::cout << "Beta = " << std::endl << avxToString(Beta, 1, system.n) << std::endl;

	for (int i = 0; i < iterations; ++i) {
		/// Etap 4
		/// Zaimplementowac metode wykonujaca pojedyncza iteracje algorytmu Jacobiego
//		std::cout << "X(" << i << ") = " << std::endl ;
//        std::cout << avxToString(X, 1, system.n) << std::endl;
//        std::cout << avxToString(X_prev, 1, system.n) << std::endl;

		this->makeIteration(Alpha, Beta, X_prev, X, system.n);
		std::swap(X, X_prev);
	}

	// Etap 5
	// Skopiowac elementy z X do system.X
	for (int i = 0; i < system.n / 8; i++) {
        X[i].store(system.X + i * 8);
    }

	// Etap 1.b
	// Zwolnic zaalokowana pamiec.
	free(unalignedAlpha);
    free(unalignedBeta);
    free(unalignedX);
    free(unalignedX_prev);
}


void Jacobi::generateAlphaBeta(float *A, float *B, Vec8f * Alpha, Vec8f * Beta, int n)
{
    for (int i = 0; i < n; i++) {
        float divisor = -A[i * n + i];
        A[i * n + i] = B[i];
        for (int j = 0; j < n / 8; j++) {
            Alpha[i * n / 8 + j].load_a(A + (i * n + j * 8));
            Alpha[i * n / 8 + j] /= divisor;
            if (j * 8 <= i && i < (j + 1) * 8) {
                Beta[j].insert(i % 8, -Alpha[i * n / 8 + j][i % 8]);
                Alpha[i * n / 8 + j].insert(i % 8, .0);
            }
        }
//        std::cout << "Alpha = " << std::endl << avxToString(Alpha, n, n) << std::endl;
    }
}


void Jacobi::makeIteration(const Vec8f * Alpha, const Vec8f * Beta, const Vec8f * X_prev, Vec8f * X, int n)
{
	for (int i = 0; i < n; i++) {   // row
        Vec8f sum = .0;
        for (int j = 0; j < n / 8; j++) {   // vector in row
            sum += Alpha[i * n / 8 + j] * X_prev[j];
//            sum += horizontal_add(tmp);
        }
        X[i / 8].insert(i % 8, horizontal_add(sum));
    }

    for (int i = 0; i < n / 8; i++) {
        X[i] += Beta[i];
    }
}


