#include "Genotype.h"

class Population {

public:
	Population(int n);
	void buildPopulation();
	Genotype Crossover(const Genotype rentOne, const Genotype rentTwo, int split);

private:
	int populationSize;
	int N;
	Genotype *gts;

};