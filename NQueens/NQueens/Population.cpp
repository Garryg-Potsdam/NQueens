#include "Population.h"

Population::Population(int n) {
	N = n;
	populationSize = n * 10;
}

void Population::buildPopulation() {
	for (int i = 0; i < populationSize; i++) {
		gts[i] = Genotype(N);
	}
}

