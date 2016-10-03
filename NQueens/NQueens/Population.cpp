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
#include <fstream>

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

// Parameters: n - the range to return a random in
// Returns: a number in range [0, n]
int Population::getRandom(int n) {
	return rand() % n;
}

// Returns: a genotype at a specified location
Genotype Population::getGenotype(int i) {
	return gts[i];
}

// Parameters:      children - the population to add children from
//             totalChildren - the total children you want added
// Post-Condition: adds all the desired children from one population to another
void Population::addGenes(Population newGenes, int totalGenes) {	
	for (int i = 0; i < totalGenes; i++)
		gts[getRandom(getSize())] = newGenes.getGenotype(i);
}


// Parameters: gt - the genotype of a child you want to add to a population
// Post-Condition: adds child gt to population if there is room
void Population::addGene(Genotype gt) {
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
Genotype Population::Crossover(Genotype &parentOne, Genotype &parentTwo, int split) {
	// Parents to splice
	GenotypeLocs one;
	one.assign(N, 0);
	parentOne.GetGenotypeLocs(one);
	GenotypeLocs two;
	two.assign(N, 0);
	parentTwo.GetGenotypeLocs(two);

	// the child
	GenotypeLocs feedus;
	feedus.assign(N, 0);

	// add values from parent one
	for (int i = 0; i < split; i++)
		feedus[i] = one[i];
	// add values from parent two
	for (int i = split; i < parentOne.getArrSize(); i++)
		feedus[i] = two[i];

	// the new child
	Genotype child = Genotype(parentOne.getArrSize());
	// mutate if conditions met
	if (getRandom(100) > (N / 10))
		child.MutateGenotype(getRandom(N), getRandom(N));

	child.SetGenotypeLocs(feedus);
	// return the new child
	return child;
}


int Population::getSize() {
	return size;
}

void Population::sort() {
	mergesort(gts, 0, populationSize - 1);
}

void Population::shuffle() {
	for (int i = 0; i < N * 10; i++) {
		int randOne = getRandom(N * 10);
		int randTwo = getRandom(N * 10);
		Genotype temp = gts[randOne];
		gts[randOne] = gts[randTwo];
		gts[randTwo] = temp;
	}
}

void Population::mergesort(std::vector<Genotype> genes, int low, int high) {
	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(genes, low, mid);
		mergesort(genes, mid + 1, high);
		merge(genes, low, high, mid);
	}
	return;
}

void Population::merge(std::vector<Genotype> genes, int low, int high, int mid) {
	int i, j, k;
	std::vector<Genotype> allele;
	int size = getSize();
	allele.assign(1000, Genotype(N));
	i = low;
	k = low;
	j = mid + 1;
	while (i <= mid && j <= high) {
		if (genes[i].GetFitness() < genes[j].GetFitness()) {
			allele[k] = genes[i];
			k++;
			i++;
		} else {
			allele[k] = genes[j];
			k++;
			j++;
		}
	}
	while (i <= mid) {
		allele[k] = genes[i];
		k++;
		i++;
	}
	while (j <= high) {
		allele[k] = genes[j];
		k++;
		j++;
	}
	for (i = low; i < k; i++) {
		genes[i] = allele[i];
	}
}