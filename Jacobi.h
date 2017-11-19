#pragma once
#include <string>
#include "vectorclass/vectorclass.h"
#include "SystemOfEquations.h"

class Jacobi
{
public:
	Jacobi() {}
	~Jacobi() {}

	void operator()(SystemOfEquations &system, int iterations);
	std::string avxToString(const Vec8f * A, int rows, int cols);

protected:

	void generateAlphaBeta(float *A, float *B, Vec8f * Alpha,  Vec8f * Beta, int n);
	void makeIteration(const Vec8f * Alpha, const Vec8f * Beta, const Vec8f * X_prev, Vec8f * X, int n);
};
