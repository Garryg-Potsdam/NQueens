///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                       Population Implementation File                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//	Author:    Garry Griggs & Gregory Hughes                                 //
//	Date:      9/26/2016                                                     //
//	Project:   NQueens                                                       //
//	FileName:  PopulationClass.cpp                                           //
//	Purpose:   This file contains the implementation for the genotype        //
//             population object                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "Population.h"

/*
Author:		Garry Griggs & Gregory Hughes
Date:		9/25/2016
Project:	NQueens
FileName:	Population.cpp
Purpose:	Population Class methods
*/

// Parameters:     n - 1/10 the population size
//             build - boolean value true = make random population
//                     false = make no population
// Post-Condition: initializes a population object of genotypes
Population::Population(int n, int popSize, bool build) {
	N = n;
	size = 0;
	populationSize = popSize;
	gts.assign(popSize, Genotype(N));
	if (build)		
		buildPopulation();
}

// Post-Condition: fills population with random genotypes and mutates
//                 10% of them
void Population::buildPopulation() {	
	for (int i = 0; i < populationSize; i++) {
		gts[i] = Genotype(N);
		Genotype temp = gts[i];
		size++;
	}
}

// Returns: size - the size of the population
int Population::getSize() {
	return size;
}

// Returns: a genotype at a specified location
Genotype Population::getGenotype(int i) {
	return gts[i];
}

// Parameters: gt - the genotype of a child you want to add to a population
// Post-Condition: adds child gt to population if there is room
void Population::addGene(Genotype gt) {
	if (size < populationSize) {
		gts[size] = gt;
		size++;
	}
}

// Parameters:      children - the population to add children from
//             totalChildren - the total children you want added
// Post-Condition: adds all the desired children from one population to another
void Population::addGenes(Population newGenes, int totalGenes) {
	for (int i = 0; i < totalGenes; i++) {
		Genotype newG = newGenes.getGenotype(i);
		int oldG = rand() % getSize();
		if (gts[oldG].GetFitness() < newG.GetFitness())
			gts[oldG] = newG;
	}
}

// Returns the highest current fitness
float Population::getHighestFitness() {
	float temp = 0.0;
	for (int i = 0; i < getSize(); i++)
		if (gts[i].GetFitness() > temp)
			temp = gts[i].GetFitness();
	return temp;
}

// If we find a solution, grab it and send it up
std::string Population::getSolution() {
	for (int i = 0; i < getSize(); i++)
		if (gts[i].GetFitness() == 10000)
			return gts[i].ToString();
}

// Parameters: kill - the amount of population to replace
void Population::annihilate(int kill) {
	Population newSeeds(N, kill, true);
	for (int i = 0; i < newSeeds.getSize(); i++) {
		int oldG = rand() % populationSize;
		if (gts[oldG].GetFitness() < newSeeds.getGenotype(i).GetFitness())
			gts[oldG] = newSeeds.getGenotype(i);
	}
}

// Mutate half the population if we are stuck at a local max
void Population::radiation() {
	for (int i = 0; i < getSize(); i++)
		if (rand() % 100 < 50)
			gts[i].MutateGenotype(rand() % N, rand() % N);
}

// Parameters: parentOne - the first parent to take a chunk of genotype from
//             parentTwo - the second paretn to take a chunk of genotype from
// Post-Condition: takes a chunk from each parent and builds a new child then 
//                 mutates 10% of the time
// Returns:        child - the child of the two spliced parents
Genotype Population::Crossover(Genotype &parentOne, Genotype &parentTwo, int split) {
	// Parents to splice
	GenotypeLocs one;
	one.assign(N, 0);
	parentOne.GetGenotypeLocs(one);
	GenotypeLocs two;
	two.assign(N, 0);
	parentTwo.GetGenotypeLocs(two);
	GenotypeLocs feedus;
	feedus.assign(N, 0);

	// add values from parent one
	for (int i = 0; i < split; i++)
		feedus[i] = one[i];
	// add values from parent two
	for (int i = split; i < parentOne.getArrSize(); i++)
		feedus[i] = two[i];

	// the new child
	Genotype child = Genotype(N);	
	child.SetGenotypeLocs(feedus);
	if (rand() % 100 < (N / 10))
		child.MutateGenotype(rand() % N, rand() % N);
	return child;
}