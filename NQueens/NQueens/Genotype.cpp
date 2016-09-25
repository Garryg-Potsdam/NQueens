#include "Genotype.h"

Genotype::Genotype()
{
	Genotype(DEFAULT_SIZE);
}


Genotype::Genotype(const int s)
{
	GenotypeLocs nGl;

	nGl = new int[s];

	for (int i = 0; i < s; i++)
		nGl[i] = -1;

	SetSize(s);

}

int * Genotype::GetArrPointer()
{
	return gl;
}

void Genotype::SetArrPointer(int * ptr)
{
	gl = ptr;
}

void Genotype::SetSize(int size)
{
	arrSize = size;
}

int Genotype::getArrSize() const {
	return arrSize;
}