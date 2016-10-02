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
	if (build) {
		buildPopulation();

		PrintPopToFile();
	}
}

// Post-Condition: fills population with random genotypes and mutates
//                 10% of them
void PopulationClass::buildPopulation() {
	std::cout << "buildPopulation" << std::endl;

	gts = new GenotypeClass[populationSize];
	
	for (int i = 0; i < populationSize; i++) {
		gts[i].SetArrSize(size);
		gts[i] = GenotypeClass(N);
		if (getRandom(N) > (N / 10))
			gts[i].MutateGenotype(getRandom(N), getRandom(N));
		std::cout << gts[i].ToString() << std::endl;
		size++;
	}
}

// Parameters: n - the range to return a random in
// Returns: a number in range [0, n]
int PopulationClass::getRandom(int n) {
	return rand() % n;
}

// Returns: a genotype at a specified location
GenotypeClass PopulationClass::getGenotype(int i) {
	std::cout << "getGenotype" << std::endl;
	return gts[i];
}

// Parameters:      children - the population to add children from
//             totalChildren - the total children you want added
// Post-Condition: adds all the desired children from one population to another
void PopulationClass::addChildren(PopulationClass children, int totalChildren) {
	std::cout << "addChildren" << std::endl;
	for (int i = 0; i < totalChildren; i++) {
		gts[N - 1 - i] = children.getGenotype(i);
	}


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
	std::cout << "crossover" << std::endl;
	// Parents to splice
	GenotypeLocs one = parentOne.GetGenotypeLocs();
	GenotypeLocs two = parentTwo.GetGenotypeLocs();
	// the child
	GenotypeLocs feedus = new int[parentOne.getArrSize()];

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

void PopulationClass::PrintPopToFile()
{
	std::ofstream fout;

	fout.open("OUTPUT.txt", std::fstream::app| std::fstream::out);

	for (int i = 0; i < populationSize; i++)
	{
		fout << gts[i].ToString() << std::endl << std::endl;
	}
}
