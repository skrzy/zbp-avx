#include "NoAvxSystemOfEquations.h"

#include <fstream>
#include <memory>

#include "vectorclass/vectorclass.h"

using namespace std;

NoAvxSystemOfEquations::NoAvxSystemOfEquations(std::string filename) {
    ifstream ifs;
    ifs.open(filename);

    ifs >> n;

    if (n % 8 > 0) {
        throw std::runtime_error("n must be a multiplicity of 8");
    }

    // Wskazowka do zadania 1
    size_t bytesMatrix = n * n * sizeof(float);
    size_t bytesVector = n * sizeof(float);

    A = (float*)malloc(bytesMatrix);
    B = (float*)malloc(bytesVector);
    X = (float*)malloc(bytesVector);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ifs >> A[i * n + j];
        }
    }

    for (int i = 0; i < n; ++i) {
        ifs >> B[i];
    }
}

NoAvxSystemOfEquations::~NoAvxSystemOfEquations()
{
    free(A);
    free(B);
    free(X);
}

