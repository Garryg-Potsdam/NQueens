///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         Population Definition File                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//	Author:    Garry Griggs & Gregory Hughes                                 //
//	Date:      9/26/2016                                                     //
//	Project:   NQueens                                                       //
//	FileName:  PopulationClass.h                                             //
//	Purpose:   This file contains the implementation for the genotype        //
//             population object                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// This is a population class
// This class is used to build a population
// of genotypes for solving NQueens
#include "Genotype.h"

class Population
{
public:
	// Parameters:     n - 1/10 the population size
	//             build - boolean value true = make random population
	//                     false = make no population
	// Post-Condition: initializes a population object of genotypes
	Population(int n, int popSize, bool build);

	// Parameters: n - the range to return a random in
	// Returns: a number in range [0, n]
	Genotype Crossover(Genotype & rentOne, 
							Genotype & rentTwo, 
							int split);

	// Returns: a genotype at a specified location
	Genotype getGenotype(int i);
	
	// Parameters:      children - the population to add children from
	//             totalChildren - the total children you want added
	// Post-Condition: adds all the desired children from one population to another
	void addGenes(Population newGenes, int totalGenes);
	
	// Parameters: parentOne - the first parent to take a chunk of genotype from
	//             parentTwo - the second paretn to take a chunk of genotype from
	// Returns:        child - the child of the two spliced parents	
	void addGene(Genotype gt);

	// Returns: size - the size of the population
	int getSize();

	void annihilate(int kill);

	// Returns the highest current fitness
	float getHighestFitness();

	// Mutate half the population if we are stuck at a local max
	void radiation();

	// If we find a solution, grab it and send it up
	std::string getSolution();

protected:
	// the Genotype vector where the population is kept
	std::vector<Genotype> gts;

private:


	// Post-Condition: fills population with random genotypes and mutates	
	void buildPopulation();

	// the max size of the population
	int populationSize;

	// The size of the genome
	int N;

	// the current size of the population
	int size;
	
};