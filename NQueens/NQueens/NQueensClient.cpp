#include "Population.h"

using namespace std;

// Parameters:    mainPop - the main population in the evolution
//             parentSize - the amount of parents in the parent population
//                popSize - the size of the actual population
// Returns: a population of parents to mate
Population buildParents(Population mainPop, int parentSize, int popSize);

// Parameters:    parents - the genotypes to be mated
//             parentSize - the amount of parents in the parent population
// Returns: a batch of fresh children
Population makeBabies(Population parents, int parentSize);

// Parameters: mainPop - the main population in the evolution
//                   N - 1/10 the size of the population
// Retuns: a solution for NQueens if one was found
Genotype getSolutionGenotype(Population mainPop, int N);

// Parameters:  pop - the population to check for a solution in
//                N - 1/10 of the population size
// Returns:    bool - true if there is a solution false otherwise
bool foundSolution(Population pop, int N);

int main() {
	
	// Board size
	int N = 8;
	// Population size
	int popSize = N * 10;
	// The amount of parents
	int parentSize = N;
	// increment if parentSize is odd
	if (N % 2 == 1)
		parentSize++;

	// Total allowed generations
	int generations = 1000;	
	// Population of randomly generated genotypes
	Population mainPop = Population(N, true);
	// if a solution is found its stored in this
	Genotype gSolution;

	// Main evolution loop
	while (generations > 0) {
		// if we find a solution we grab it and stop evolving
		if (foundSolution(mainPop, N)) {
			gSolution = getSolutionGenotype(mainPop);
			break;
		}
		// Population of this gens parents
		Population parents  = buildParents(mainPop, parentSize, popSize);
		// Population of this gens children
		Population children = makeBabies(parents, parentSize);
		// Add the best children elimnate the worst from previous gen
		mainPop.addChildren(children, parentSize / 2);
		// decrement generations left
		generations--;
	}

}


// Parameters:    mainPop - the main population in the evolution
//             parentSize - the amount of parents in the parent population
//                popSize - the size of the actual population
// Returns: a population of parents to mate
Population buildParents(Population mainPop, int parentSize, int popSize) {
	Population parents(parentSize, false);
	for (int i = 0; i < parentSize; i++) {
		// randomly get three potential maters
		Genotype materOne = mainPop.getGenotype(mainPop.getRandom(popSize));
		Genotype materTwo = mainPop.getGenotype(mainPop.getRandom(popSize));
		Genotype materThree = mainPop.getGenotype(mainPop.getRandom(popSize));
		if (materOne.GetFitness() >= materTwo.GetFitness()) {
			if (materOne.GetFitness() >= materThree.GetFitness())
				parents.addChild(materOne);
			else
				parents.addChild(materThree);
		}
		else { // two is bigger than one
			if (materTwo.GetFitness() > materThree.GetFitness())
				parents.addChild(materTwo);
			else
				parents.addChild(materThree);
		}
	}
	return parents;
}

// Parameters:    parents - the genotypes to be mated
//             parentSize - the amount of parents in the parent population
// Returns: a batch of fresh children
Population makeBabies(Population parents, int parentSize) {
	Population children(parentSize, false);
	for (int i = 0; i < parentSize; i += 2) {
		children.addChild(parents.Crossover(parents.getGenotype(i), parents.getGenotype(i + 1), parents.getRandom(parentSize)));
		children.addChild(parents.Crossover(parents.getGenotype(i + 1), parents.getGenotype(i), parents.getRandom(parentSize)));
	}
}

// Parameters: mainPop - the main population in the evolution
//                   N - 1/10 the size of the population
// Retuns: a solution for NQueens if one was found
Genotype getSolutionGenotype(Population pop, int N) {
	Genotype temp;
	for (int i = 0; i < N * 10; i++) {
		if (pop.getGenotype(i).GetFitness() == 10000) {
			temp = pop.getGenotype(i);
		}
	}
	return temp;
}

// Parameters:  pop - the population to check for a solution in
//                N - 1/10 of the population size
// Returns:    bool - true if there is a solution false otherwise
bool foundSolution(Population pop, int N) {
	for (int i = 0; i < N * 10; i++) {
		if (pop.getGenotype(i).GetFitness() == 10000) {
			return true;
		}
	}
}
