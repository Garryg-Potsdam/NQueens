#include <ctime>
#include <iostream>
#include "Genotype.h"

class Population : public Genotype {

public:
	Population(int n, bool build);
	Genotype Crossover(Genotype & rentOne, Genotype & rentTwo, int split);
	Genotype getGenotype(int i);
	void addChildren(Population p, int totalChildren);
	int getRandom(int n);
	void addChild(Genotype gt);
	void buildPopulation();
private:
	int populationSize;
	int N;
	int size;
	Genotype *gts;

};