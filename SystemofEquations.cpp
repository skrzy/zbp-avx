#include "SystemOfEquations.h"

#include <fstream>
#include <memory>

#include "vectorclass/vectorclass.h"

using namespace std;

SystemOfEquations::SystemOfEquations(std::string filename) {
	ifstream ifs;
	ifs.open(filename);

	ifs >> n;

	if (n % 8 > 0) {
		throw std::runtime_error("n must be a multiplicity of 8");
	}
	
	// Wskazowka do zadania 1
	size_t bytesMatrix = n * n * sizeof(float);
	size_t bytesVector = n * sizeof(float);
	
	size_t spaceA = bytesMatrix + sizeof(Vec8f);
	size_t spaceB = bytesVector + sizeof(Vec8f);
	size_t spaceX = bytesVector + sizeof(Vec8f);
	
	unalignedA = malloc(spaceA);
	unalignedB = malloc(spaceB);
	unalignedX = malloc(spaceX);
	
	void *tempA = unalignedA;
	void *tempB = unalignedB;
	void *tempX = unalignedX;

	A = (float*)std::align(sizeof(Vec8f), bytesMatrix, tempA, spaceA);
	B = (float*)std::align(sizeof(Vec8f), bytesVector, tempB, spaceB);
	X = (float*)std::align(sizeof(Vec8f), bytesVector, tempX, spaceX);
	// koniec wskazowki

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ifs >> A[i * n + j];
		}
	}

	for (int i = 0; i < n; ++i) {
		ifs >> B[i];
	}
}

SystemOfEquations::~SystemOfEquations()
{
	free(unalignedA);
	free(unalignedB);
	free(unalignedX);
}