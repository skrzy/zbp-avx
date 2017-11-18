#pragma once
#include <string>

class SystemOfEquations
{
public:
	SystemOfEquations(std::string filename);
	~SystemOfEquations();

	int n;
	float *A;
	float *B;
	float *X;

protected:
	
	void *unalignedA;
	void *unalignedB;
	void *unalignedX;
};