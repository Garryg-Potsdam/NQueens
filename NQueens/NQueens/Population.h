#include <ctime>
#include <iostream>
#include "Genotype.h"

class Population : public Genotype {

public:
	Population(int n);
	void buildPopulation();
	Genotype Crossover(Genotype & rentOne, Genotype & rentTwo, int split);
	Genotype getGenotype(int i);
	int getRandom(int n);
private:
	int populationSize;
	int N;
	Genotype *gts;

};