#include "Genotype.h"

class Population : public Genotype {

public:
	Population(int n);
	void buildPopulation();
	Genotype Crossover(Genotype rentOne, Genotype rentTwo, int split);

private:
	int populationSize;
	int N;
	Genotype *gts;

};