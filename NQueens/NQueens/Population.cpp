#include "Population.h"

Population::Population(int n) {
	N = n;
	populationSize = n * 10;
}

void Population::buildPopulation() {
	gts = new Genotype[populationSize];
	for (int i = 0; i < populationSize; i++) {
		gts[i] = Genotype(N);
		gts[i].MutateGenotype(getRandom(N), getRandom(N));
	}
}

int Population::getRandom(int n) {
	srand(time(NULL));
	return rand() % n + 1;
}

Genotype Population::getGenotype(int i) {
	return gts[i];
}

Genotype Population::Crossover(Genotype & rentOne, Genotype & rentTwo, int split)
{
	GenotypeLocs one = rentOne.GetGenotypeLocs();

	GenotypeLocs two = rentTwo.GetGenotypeLocs();

	GenotypeLocs feedus = new int[rentOne.getArrSize()];

	for (int i = 0; i < split; i++)
		feedus[i] = one[i];
	
	for (int i = split; i < rentOne.getArrSize; i++)
		feedus[i] = two[i];

	Genotype child = Genotype(rentOne.getArrSize());

	child.SetGenotypeLocs(feedus);
	
	return child;
}

