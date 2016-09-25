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

Genotype Genotype::Crossover(const Genotype rentOne, const Genotype rentTwo, int split)
{
	Genotype child = Genotype(rentOne.arrSize);

	for (int i = 0; i < split; i++)
		child.gl[i] = rentOne.gl[i];
	
	for (int i = split; i < rentOne.arrSize; i++)
		child.gl[i] = rentTwo.gl[i];

}

Genotype Genotype::Mutate(const Genotype old, int one, int two) const
{
	int temp = old.gl[one];

	old.gl[one] = old.gl[two];

	old.gl[two] = temp;
}

void Genotype::SetSize(int size)
{
	arrSize = size;
}