#pragma once
#include <string>

class NoAvxSystemOfEquations
{
public:
    NoAvxSystemOfEquations(std::string filename);
    ~NoAvxSystemOfEquations();

    int n;
    float *A;
    float *B;
    float *X;
};
