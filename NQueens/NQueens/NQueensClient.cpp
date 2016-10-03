///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                           NQueens Client, Our Bot                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//	Author:    Garry Griggs & Gregory Hughes                                 //
//	Date:      9/26/2016                                                     //
//	Project:   NQueens                                                       //
//	FileName:  NqueensClient.cpp                                             //
//	Purpose:   This file contains the implementation of our NQueens program  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include "Population.h"

using namespace std;

// Parameters:    mainPop - the main population in the evolution
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
//                popSize - the size of the actual population
// Returns: a population of parents to mate
Population buildParents(Population mainPop, int genomeSize, int parentSize, int popSize);

// Parameters:    parents - the genotypes to be mated
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
// Returns: a batch of fresh children
Population makeBabies(Population parents, int gnomeSize, int parentSize);

// Parameters:  pop - the population to check for a solution in
//                N - 1/10 of the population size
// Returns:    bool - true if there is a solution false otherwise
// Post-Condition: prints the first correct solution it finds
bool foundSolution(Population pop, int N);

int main() {

	// Seed rand in main to maintain pseudo-randomness 
	// and not reseed with every call to receive a new random number
	srand(time(NULL));
	

	// GREG: CIN these three variables
	// Board size
	int N = 12; 
	// Total allowed generations
	int generations = 1;
	// total times to run
	int runTimes = 25;



	// Population size
	int popSize = N * 10;
	// The amount of parents
	int parentSize = N;
	// increment if parentSize is odd
	if (N % 2 == 1)
		parentSize++;

	while (runTimes > 0) {
		// is there a solution
		bool solution = true;
		// Population of randomly generated genotypes
		Population mainPop = Population(N, popSize, true);
		// if a solution is found its stored in this
		if (!foundSolution(mainPop, mainPop.getSize())) {
			solution = false;
			cout << "Run Times Left: " << runTimes << endl;
			// Main evolution loop
			while (generations < 1001) {
				// if we find a solution we grab it and stop evolving				
				// Population of this gens parents
				Population parents = buildParents(mainPop, N, parentSize, popSize);
				// Population of this gens children
				Population children = makeBabies(parents, N, parentSize);
				// Add the best children elimnate the worst from previous gen
				mainPop.addGenes(children, parentSize);
				if (solution = foundSolution(children, children.getSize()))
					break;
				// decrement generations left
				generations++;
			}
		}
		generations = 1;
		runTimes--;
	}
}


// Parameters:    mainPop - the main population in the evolution
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
//                popSize - the size of the actual population
// Returns: a population of parents to mate
Population buildParents(Population mainPop, int gnomeSize, int parentSize, int popSize) {
	Population parents(gnomeSize, parentSize, false);
	for (int i = 0; i < parentSize; i++) {
		// randomly get three potential maters
		Genotype materOne = mainPop.getGenotype(mainPop.getRandom(popSize));
		Genotype materTwo = mainPop.getGenotype(mainPop.getRandom(popSize));
		Genotype materThree = mainPop.getGenotype(mainPop.getRandom(popSize));
		if (materOne.GetFitness() >= materTwo.GetFitness()) {
			if (materOne.GetFitness() >= materThree.GetFitness())
				parents.addGene(materOne);
			else
				parents.addGene(materThree);
		}
		else { // two is bigger than one
			if (materTwo.GetFitness() > materThree.GetFitness())
				parents.addGene(materTwo);
			else
				parents.addGene(materThree);
		}
	}
	return parents;
}

// Parameters:    parents - the genotypes to be mated
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
// Returns: a batch of fresh children
Population makeBabies(Population parents, int gnomeSize, int parentSize) {
	Population children(gnomeSize, parentSize, false);
	for (int i = 0; i < parentSize; i += 2) {
		children.addGene(parents.Crossover(parents.getGenotype(i), parents.getGenotype(i + 1), parents.getRandom(parentSize)));
		children.addGene(parents.Crossover(parents.getGenotype(i + 1), parents.getGenotype(i), parents.getRandom(parentSize)));
	}
	return children;
}

// Parameters:  pop - the population to check for a solution in
//             size - population size to look through
// Returns:    bool - true if there is a solution false otherwise
// Post-Condition: prints the first correct solution it finds
bool foundSolution(Population pop, int size) {
	for (int i = size - 1; i > 0; i--)
		if (pop.getGenotype(i).GetFitness() == 10000) {
			cout << pop.getGenotype(i).ToString() << endl;
			return true;
		}
	return false;
}
