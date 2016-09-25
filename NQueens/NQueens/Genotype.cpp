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

Genotype Genotype::Mutate(const Genotype old, int one, int two) const
{
	int temp = old.gl[one];

	old.gl[one] = old.gl[two];

	old.gl[two] = temp;
}

int * Genotype::GetArrPointer()
{
	return gl;
}

void Genotype::SetSize(int size)
{
	arrSize = size;
}

int Genotype::getArrSize() {
	return arrSize;
}