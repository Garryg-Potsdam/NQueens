/*
	Author:		Garry Griggs & Gregory Hughes
	Date:		9/25/2016
	Project:	NQueens
	FileName:	Population.h
	Purpose:	Header file for Population class
*/


#include <ctime>
#include <iostream>
#include "Genotype.h"



class Population : public Genotype {

public:
	// Parameters:     n - 1/10 the population size
	//             build - boolean value true = make random population
	//                     false = make no population
	// Post-Condition: initializes a population object of genotypes
	Population(int n, bool build);	

	// Parameters: n - the range to return a random in
	// Returns: a number in range [0, n]
	int getRandom(int n);

	// Returns: a genotype at a specified location
	Genotype getGenotype(int i);

	// Parameters:      children - the population to add children from
	//             totalChildren - the total children you want added
	// Post-Condition: adds all the desired children from one population to another
	void addChildren(Population p, int totalChildren);

	// Parameters: gt - the genotype of a child you want to add to a population
	// Post-Condition: adds child gt to population if there is room
	void addChild(Genotype gt);

	// Parameters: parentOne - the first parent to take a chunk of genotype from
	//             parentTwo - the second paretn to take a chunk of genotype from
	// Post-Condition: takes a chunk from each parent and builds a new child then 
	//                 mutates 10% of the time
	// Returns:        child - the child of the two spliced parents
	Genotype Crossover(Genotype & rentOne, Genotype & rentTwo, int split);
	
private:

	void buildPopulation();
	int populationSize;
	int N;
	int size;
	Genotype *gts;

};