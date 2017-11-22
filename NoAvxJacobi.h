#pragma once
#include <string>
#include "vectorclass/vectorclass.h"
#include "NoAvxSystemOfEquations.h"

class NoAvxJacobi
{
public:
    NoAvxJacobi() {}
    ~NoAvxJacobi() {}

    void operator()(NoAvxSystemOfEquations &system, int iterations);
    std::string matrixToString(const float * A, int rows, int cols);

protected:

    void generateAlphaBeta(float *A, float *B, float * Alpha, float * Beta, int n);
    void makeIteration(const float * Alpha, const float * Beta, const float * X_prev, float * X, int n);
};
