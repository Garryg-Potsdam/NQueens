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
#include <fstream>
#include "Population.h"

using namespace std;

// Constants
const string OUT_FILE = "out.txt";

const string DETAILED_OUT = "dets.txt";

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
bool foundSolution(Population pop, int N, ofstream & dout);

int main() 
{
	// Values to run program for
	int N, generations, runTimes, childrenCount;

	// Gather information
	cout << "Enter the board size: ";
	cin >> N;
	
	cout << "Number of generations: ";
	cin >> generations; 
	
	cout << "Amount of run times: ";
	cin  >> runTimes;

	cout << "How many children: ";
	cin >> childrenCount;

	// Calculate values
	// Population size
	int popSize = N * 10;
	// The amount of parents
	int parentSize = N;
	// increment if parentSize is odd
	if (N % 2 == 1)
		parentSize++;

	ofstream fout;

	ofstream dout;

	fout.open(OUT_FILE.c_str());

	dout.open(DETAILED_OUT.c_str());

	while (runTimes > 0) 
	{
		// Seed rand in main to maintain pseudo-randomness 
		// and not reseed with every call to receive a new random number
		srand(time(NULL));

		// is there a solution
		// Population of randomly generated genotypes
		Population mainPop = Population(N, popSize, true);

		// if a solution is found its stored in this
		if (!foundSolution(mainPop, mainPop.getSize(), dout)) 
		{
			fout << "Run Times Left: " << runTimes << endl;
			dout << "Run Times Left: " << runTimes << endl;
			
			// Main evolution loop
			while (generations < 1001) 
			{
				// if we find a solution we grab it and stop evolving				
				// Population of this gens parents
				Population parents = buildParents(mainPop, N, parentSize, popSize);

				// Population of this gens children
				Population children = makeBabies(parents, N, childrenCount);
				
				// Add the best children elimnate the worst from previous gen
				mainPop.addGenes(children, parentSize);
				
				// If a solution is found, we leave the main loop.
				if (foundSolution(children, children.getSize(), dout)) {break;}

				// decrement generations left
				generations++;
			}
		}

		generations = 1;
		runTimes--;
	}

	fout.close();
	dout.close();
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
Population makeBabies(Population parents, int gnomeSize, int childCount) {
	Population children(gnomeSize, childCount, false);
	for (int i = 0; i < childCount; i++) {
		int one = rand() % parents.getSize();
		int two = rand() % parents.getSize();
		children.addGene(parents.Crossover(parents.getGenotype(one), parents.getGenotype(two), parents.getRandom(parents.getSize())));
	}
	return children;
}

// Parameters:  pop - the population to check for a solution in
//             size - population size to look through
// Returns:    bool - true if there is a solution false otherwise
// Post-Condition: prints the first correct solution it finds
bool foundSolution(Population pop, int size, ofstream& dout) {
	for (int i = size - 1; i > 0; i--)
		if (pop.getGenotype(i).GetFitness() == 10000) {
			dout << pop.getGenotype(i).ToString() << endl;
			return true;
		}
	return false;
}