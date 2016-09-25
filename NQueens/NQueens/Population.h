#include "Genotype.h"

class Population : public Genotype {

public:
	Population(int n);
	void buildPopulation();
	Genotype Crossover(const Genotype rentOne, const Genotype rentTwo, int split) const;

private:
	int populationSize;
	int N;
	Genotype *gts;

};