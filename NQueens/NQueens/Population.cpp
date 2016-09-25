/*
	Author:		Garry Griggs & Gregory Hughes
	Date:		9/25/2016
	Project:	NQueens
	FileName:	Population.cpp
	Purpose:	Population Class methods
*/

#include "Population.h"

// Parameters:     n - 1/10 the population size
//             build - boolean value true = make random population
//                     false = make no population
// Post-Condition: initializes a population object of genotypes
Population::Population(int n, bool build) {
	N = n;
	size = 0;
	populationSize = n * 10;
	if (build)
		buildPopulation();
}

// Post-Condition: fills population with random genotypes and mutates
//                 10% of them
void Population::buildPopulation() {
	gts = new Genotype[populationSize];
	for (int i = 0; i < populationSize; i++) {
		gts[i] = Genotype(N);
		if (getRandom(N) > (N/10))
			gts[i].MutateGenotype(getRandom(N), getRandom(N));
		size++;
	}
}

// Parameters: n - the range to return a random in
// Returns: a number in range [0, n]
int Population::getRandom(int n) {
	srand(time(NULL));
	return rand() % n;
}

// Returns: a genotype at a specified location
Genotype Population::getGenotype(int i) {
	return gts[i];
}

// Parameters:      children - the population to add children from
//             totalChildren - the total children you want added
// Post-Condition: adds all the desired children from one population to another
void Population::addChildren(Population children, int totalChildren) {
	for (int i = 0; i < totalChildren; i++) {
		gts[N - 1 - i] = children.getGenotype(i);
	}
}

// Parameters: gt - the genotype of a child you want to add to a population
// Post-Condition: adds child gt to population if there is room
void Population::addChild(Genotype gt) {
	if (size < N - 1) {
		gts[size] = gt;
		size++;
	}
}

// Parameters: parentOne - the first parent to take a chunk of genotype from
//             parentTwo - the second paretn to take a chunk of genotype from
// Post-Condition: takes a chunk from each parent and builds a new child then 
//                 mutates 10% of the time
// Returns:        child - the child of the two spliced parents
Genotype Population::Crossover(Genotype & parentOne, Genotype & parentTwo, int split) {
	// Parents to splice
	GenotypeLocs one = parentOne.GetGenotypeLocs();
	GenotypeLocs two = parentTwo.GetGenotypeLocs();
	// the child
	GenotypeLocs feedus = new int[parentOne.getArrSize()];

	// add values from parent one
	for (int i = 0; i < split; i++)
		feedus[i] = one[i];
	// add values from parent two
	for (int i = split; i < parentOne.getArrSize; i++)
		feedus[i] = two[i];

	// the new child
	Genotype child = Genotype(parentOne.getArrSize());
	// mutate if conditions met
	if (getRandom(N) > (N / 10))
		child.MutateGenotype(getRandom(N), getRandom(N));

	child.SetGenotypeLocs(feedus);
	// return the new child
	return child;
}

