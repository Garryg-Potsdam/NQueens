#include "Population.h"

Population::Population(int n) {
	N = n;
	populationSize = n * 10;
}

void Population::buildPopulation() {
	gts = new Genotype[populationSize];
	for (int i = 0; i < populationSize; i++) {
		gts[i] = Genotype(N);
	}
}

Genotype Population::Crossover(Genotype rentOne, Genotype rentTwo, int split)
{
	Genotype child = Genotype(rentOne.getArrSize());

	for (int i = 0; i < split; i++)
	{
		child.gl[i] = rentOne.gl[i];
	}

}