#include "NoAvxJacobi.h"

#include <memory>
#include <sstream>
#include <iostream>


std::string NoAvxJacobi::matrixToString(const float * A, int rows, int cols)
{
    std::ostringstream oss;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            oss << A[i * cols + j] << ", ";
        }
        oss << std::endl;
    }

    return oss.str();
}


void NoAvxJacobi::operator()(NoAvxSystemOfEquations &system, int iterations)
{
    size_t bytesMatrix = system.n * system.n * sizeof(float);
    size_t bytesVector = system.n * sizeof(float);

    float * Alpha = (float*)malloc(bytesMatrix);
    float * Beta = (float*)malloc(bytesVector);
    float * X = (float*)malloc(bytesVector);
    float * X_prev = (float*)malloc(bytesVector);

    for (int i = 0; i < system.n; i++) {
        X_prev[i] = .0;
        X[i] = .0;
    }

    // Etap 3
    // Zaimplementowac metode wyznaczajaca Alpha i Beta na podstawie A i B
    this->generateAlphaBeta(system.A, system.B, Alpha, Beta, system.n);

    std::cout << "Alpha = " << std::endl << matrixToString(Alpha, system.n, system.n) << std::endl;
    std::cout << "Beta = " << std::endl << matrixToString(Beta, 1, system.n) << std::endl;

    for (int i = 0; i < iterations; ++i) {
        /// Etap 4
        /// Zaimplementowac metode wykonujaca pojedyncza iteracje algorytmu Jacobiego
        std::cout << "X(" << i << ") = " << std::endl ;
        std::cout << matrixToString(X, 1, system.n) << std::endl;
        std::cout << matrixToString(X_prev, 1, system.n) << std::endl;

        this->makeIteration(Alpha, Beta, X_prev, X, system.n);
        std::swap(X, X_prev);
    }

    // Etap 5
    // Skopiowac elementy z X do system.X
    for (int i = 0; i < system.n; i++) {
        system.X[i] = X[i];
    }

    // Etap 1.b
    // Zwolnic zaalokowana pamiec.
    free(Alpha);
    free(Beta);
    free(X);
    free(X_prev);
}


void NoAvxJacobi::generateAlphaBeta(float *A, float *B, float * Alpha, float * Beta, int n)
{
    for (int i = 0; i < n; i++) {
        float divisor = A[i * n + i];
        Beta[i] = B[i] / divisor;
        for (int j = 0; j < n; j++) {
            Alpha[i * n + j] = A[i * n + j] / (-divisor);
        }
        Alpha[i * n + i] = 0;
//        std::cout << "Alpha = " << std::endl << matrixToString(Alpha, n, n) << std::endl;
    }
}


void NoAvxJacobi::makeIteration(const float * Alpha, const float * Beta, const float * X_prev, float * X, int n)
{
    for (int i = 0; i < n; i++) {   // row
        float sum = .0;
        for (int j = 0; j < n; j++) {   // vector in row
            sum += Alpha[i * n + j] * X_prev[j];
        }
        X[i] = sum + Beta[i];
    }
}


