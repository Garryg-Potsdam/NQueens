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
const string DETAILED_OUT = "details.out";		// File to output to

// Parameters:    mainPop - the main population in the evolution
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
//                popSize - the size of the actual population
// Returns: a population of parents to mate
Population buildParents(Population mainPop, int genomeSize, int parentSize, int popSize);

// Parameters:    parents - the genotypes to be mated
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
// Post-Condition: adds a batch of fresh children
Population makeBabies(Population parents, int gnomeSize, int parentSize);

// Params:	None
// Post:	Hopefully the console is cleared of it's contents.
void ClearConsoleBecauseWeAreNotOnWindows();

int main() 
{
	// Values to run program for
	int N, generations, totalRunTimes;

	// Gather information
	cout << "Enter the board size: ";
	cin >> N;
	
	cout << "Number of generations: ";
	cin >> generations; 
	
	cout << "Amount of run times: ";
	cin  >> totalRunTimes;

	
	// Calculate values
	// Population size
	int popSize = N * 10;	
	// Children size
	int childrenCount = popSize / 4;
	// radiation to break local maximum
	int mutate = N * 5;	
	// The amount of parents
	int parentSize = N;
	
	// increment if parentSize is odd
	if (N % 2 == 1)
		parentSize++;

	// open the details of the file output

	ofstream dout;

	dout.open(DETAILED_OUT.c_str());

	for (int r = 0; r < totalRunTimes; r++)
	{
		ClearConsoleBecauseWeAreNotOnWindows();
		cout << (r * 100) / totalRunTimes << "% complete" << endl;

		// reseed random for each run time
		srand(time(NULL) + (r * 37));

		// is there a solution
		// Population of randomly generated genotypes
		Population mainPop = Population(N, popSize, true);

		// keep track of generations
		int deGen = 0;
		int generationNumOfHighestFitness = 0;

		// are we at a local max
		int countLocalMax = 0;
		float prevMax = mainPop.getHighestFitness();
		float curMax = prevMax;
		
		// if a solution is found its stored in this
		if (prevMax != 10000) 
		{	
			// Main evolution loop
			while (generations > deGen) 
			{

				// keep track of local max
				if (curMax == prevMax) 
				{
					countLocalMax++;					
				}
				else 
				{
					generationNumOfHighestFitness = deGen;
					prevMax = curMax;
					countLocalMax = 0;					
				}				
				
				// if we are stuck at a local max, why not pour in some
				// radiation
				if (countLocalMax == mutate) 
				{
					mainPop.radiation();					
					countLocalMax = 0; // reset countLocalMax
					// set the current max					
					curMax = mainPop.getHighestFitness();

					// break if we are done.
					if (curMax == 10000) {break;}
				}
				
				// if we find a solution we grab it and stop evolving				
				// Population of this gens parents
				
				Population parents = buildParents(mainPop, N, parentSize, popSize);
				
				// Population of this gens children
				Population children = makeBabies(parents, N, childrenCount);

				mainPop.addGenes(children);
				
				// set the current max
				curMax = mainPop.getHighestFitness();
				
				if (curMax == 10000) {break;}

				// increment for current gen
				deGen++;
				
			}
		} 
		// else do nothing...
		
		if (curMax == 10000) 
		{
			dout << "CURRENT RUN TIME: " << r << endl;
			dout << "Generation Of Highest Fitness: " << 
				generationNumOfHighestFitness << endl;
			dout << "Highest Fitness: " << curMax << endl;
			dout << "Solution: " << endl << mainPop.getSolution() << endl;
            
			ostringstream sm;
			sm << r;
			string solOut = "Boards" + sm.str() + ".solution";

			fstream fout;

			fout.open(solOut.c_str());

			fout << endl << mainPop.getSolution();

			fout.close();
		} 
		else 
		{
			dout << "CURRENT RUN TIME: " << r << endl;
			dout << "Generation Of Highest Fitness: " << generations << endl;
			dout << "Highest Fitness: " << curMax << endl;
		}
		
		// Print a pretty line
		dout << endl;
		for (int i = 0; i < 40; i++)
			dout << "- ";
		dout << endl;

		// reset generations for next iterations
		deGen = 0;
	}

	
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
		int one   = rand() % popSize;
		int two   = rand() % popSize;
		int three = rand() % popSize;
		
		// check if they have mated yet if not grab and set mated true
		while (mainPop.getGenotype(one).WasSelectedForMatingPool())
			one = rand() % popSize;

		// set mated to true
		mainPop.getGenotype(one).SetSelectedForMatingPool(true);

		while (mainPop.getGenotype(two).WasSelectedForMatingPool())
			two = rand() % popSize;

		// set mated to true
		mainPop.getGenotype(two).SetSelectedForMatingPool(true);

		while (mainPop.getGenotype(three).WasSelectedForMatingPool())
			three = rand() % popSize;
		
		// set mated to true
		mainPop.getGenotype(three).SetSelectedForMatingPool(true);

		Genotype materOne = mainPop.getGenotype(one);
		Genotype materTwo = mainPop.getGenotype(two);
		Genotype materThree = mainPop.getGenotype(three);
		
		// Choose the best fit
		if (materOne.GetFitness() >= materTwo.GetFitness())
			if (materOne.GetFitness() >= materThree.GetFitness())
				parents.addGene(materOne);
			else
				parents.addGene(materThree);
		else // two is bigger than one
			if (materTwo.GetFitness() > materThree.GetFitness())
				parents.addGene(materTwo);
			else
				parents.addGene(materThree);		
	}

	// reset all the maters to not mated
	for (int i = 0; i < popSize; i++)
		mainPop.getGenotype(i).SetSelectedForMatingPool(false);
	return parents;
}

// Parameters:    parents - the genotypes to be mated
//			   genomeSize - the size of N the genome
//             parentSize - the amount of parents in the parent population
// Returns: a batch of fresh children
Population makeBabies(Population parents, int gnomeSize, int childCount) {
	Population children(gnomeSize, childCount, false);
	int countParents = 0;
	for (int i = 0; i < childCount; i++) {
		countParents += 2;		
		// if parents have all been used reset them
		if (countParents >= parents.getSize())
			for (int i = 0; i < parents.getSize(); i++)
				parents.getGenotype(i).SetSelectedForMatingPool(false);

		int one = rand() % gnomeSize;
		int two = rand() % gnomeSize;
		// look for unused parent
		while (parents.getGenotype(one).WasSelectedForMatingPool())
			one = rand() % gnomeSize;

		// set mated to true
		parents.getGenotype(one).SetSelectedForMatingPool(true);

		while (parents.getGenotype(two).WasSelectedForMatingPool())
			two = rand() % gnomeSize;

		// set mated to true
		parents.getGenotype(two).SetSelectedForMatingPool(true);

		// add new child gene to child pop from parents
		const long double sysTime = time(0);
		children.addGene(parents.Crossover(parents.getGenotype(one), parents.getGenotype(two), rand() % gnomeSize));
	}
	return children;
}

// Params:	None
// Post:	Hopefully the console is cleared of it's contents.
void ClearConsoleBecauseWeAreNotOnWindows()
{
	for (int i = 0; i < 200; i++)
		cout << endl;
}
