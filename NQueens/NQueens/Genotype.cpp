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

	gl = nGl;

}

Genotype Genotype::Mutate(const Genotype old) const
{

}

void Genotype::SetSize(int size)
{
	arrSize = size;
}

int Genotype::getArrSize() {
	return arrSize;
}