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
	void addGenes(Population p, int totalChildren);
	
	// Parameters: gt - the genotype of a child you want to add to a population
	// Post-Condition: adds child gt to population if there is room
	int getRandom(int n);

	// Parameters: parentOne - the first parent to take a chunk of genotype from
	//             parentTwo - the second paretn to take a chunk of genotype from
	// Post-Condition: takes a chunk from each parent and builds a new child then 
	//                 mutates 10% of the time
	// Returns:        child - the child of the two spliced parents	
	void addGene(Genotype gt);
	void shuffle();
	void sort();
	int getSize();

private:
	void mergesort(Genotype *a, int low, int high);
	void merge(Genotype *a, int low, int high, int mid);
	// Post-Condition: fills population with random genotypes and mutates
	//                 10% of them
	void buildPopulation();

	int populationSize;
	int N;
	int size;
	Genotype *gts;
};