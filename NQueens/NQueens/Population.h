#include <ctime>
#include <iostream>
#include "Genotype.h"

class Population : public Genotype {

public:
	Population(int n);
	Genotype Crossover(Genotype & rentOne, Genotype & rentTwo, int split);
	Genotype getGenotype(int i);
	void addChildren(Population p, int totalChildren);
	int getRandom(int n);
private:
	int populationSize;
	int N;
	Genotype *gts;
	void buildPopulation();

};