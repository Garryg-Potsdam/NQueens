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

#include "PopulationClass.h"
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
PopulationClass::PopulationClass(int n, bool build) {
	N = n;
	size = 0;
	populationSize = n * 10;
	gts = new GenotypeClass[populationSize];
	if (build)
		buildPopulation();
}

// Post-Condition: fills population with random genotypes and mutates
//                 10% of them
void PopulationClass::buildPopulation() {	
	for (int i = 0; i < populationSize; i++) {
		gts[i].SetArrSize(size);
		gts[i] = GenotypeClass(N);
		if (getRandom(N) > (N / 10))
			gts[i].MutateGenotype(getRandom(N), getRandom(N));
		size++;
	}
	/*
	for (int i = 0; i < populationSize; i++) {
		std::cout << "Fitness " << i << ": " << gts[i].GetFitness() << std::endl;
	}
	mergesort(gts, 0, populationSize - 1);
	std::cout << std::endl << std::endl;
	for (int i = 0; i < populationSize; i++) {
		std::cout << "Fitness " << i << ": " << gts[i].GetFitness() << std::endl;
	}
	*/
}

// Parameters: n - the range to return a random in
// Returns: a number in range [0, n]
int PopulationClass::getRandom(int n) {
	return rand() % n;
}

// Returns: a genotype at a specified location
GenotypeClass PopulationClass::getGenotype(int i) {
	return gts[i];
}

// Parameters:      children - the population to add children from
//             totalChildren - the total children you want added
// Post-Condition: adds all the desired children from one population to another
void PopulationClass::addChildren(PopulationClass children, int totalChildren) {
	mergesort(gts, 0, populationSize - 1);
	mergesort(children.gts, 0, populationSize - 1);
	for (int i = 0; i < totalChildren; i++)
		gts[i] = children.getGenotype(i);

}



// Parameters: gt - the genotype of a child you want to add to a population
// Post-Condition: adds child gt to population if there is room
void PopulationClass::addChild(GenotypeClass gt) {
	std::cout << "addChild" << std::endl;
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
GenotypeClass PopulationClass::Crossover(GenotypeClass & parentOne, GenotypeClass & parentTwo, int split) {
	// Parents to splice
	GenotypeLocs one;
	parentOne.GetGenotypeLocs(one);
	GenotypeLocs two;
	parentTwo.GetGenotypeLocs(two);

	// the child
	GenotypeLocs feedus;

	// add values from parent one
	for (int i = 0; i < split; i++)
		feedus[i] = one[i];
	// add values from parent two
	for (int i = split; i < parentOne.getArrSize(); i++)
		feedus[i] = two[i];

	// the new child
	GenotypeClass child = GenotypeClass(parentOne.getArrSize());
	// mutate if conditions met
	if (getRandom(N) >(N / 10))
		child.MutateGenotype(getRandom(N), getRandom(N));

	child.SetGenotypeLocs(feedus);
	// return the new child
	return child;
}


void PopulationClass::mergesort(GenotypeClass *genes, int low, int high) {
	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(genes, low, mid);
		mergesort(genes, mid + 1, high);
		merge(genes, low, high, mid);
	}
	return;
}
void PopulationClass::merge(GenotypeClass *genes, int low, int high, int mid) {
	int i, j, k;
	GenotypeClass allele[50];
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