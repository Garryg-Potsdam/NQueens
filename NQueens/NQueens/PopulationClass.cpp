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

PopulationClass::PopulationClass(int n, bool build) {
	N = n;
	size = 0;
	populationSize = n * 10;
	if (build)
		buildPopulation();
}

void PopulationClass::buildPopulation() {
	gts = new GenotypeClass[populationSize];
	for (int i = 0; i < populationSize; i++) {
		gts[i] = GenotypeClass(N);
		if (getRandom(N) > (N/10))
			gts[i].MutateGenotype(getRandom(N), getRandom(N));
		size++;
	}
}

int PopulationClass::getRandom(int n) {
	return rand() % n;
}

GenotypeClass PopulationClass::getGenotype(int i) {
	return gts[i];
}

void PopulationClass::addChildren(PopulationClass p, int totalChildren) {
	for (int i = 0; i < totalChildren; i++) {
		gts[N - 1 - i] = p.getGenotype(i);
	}
}

void PopulationClass::addChild(GenotypeClass gt) {
	if (size < N - 1) {
		gts[size] = gt;
		size++;
	}
}

GenotypeClass PopulationClass::Crossover(GenotypeClass & rentOne, GenotypeClass & rentTwo, int split) {
	GenotypeLocs one = rentOne.GetGenotypeLocs();

	GenotypeLocs two = rentTwo.GetGenotypeLocs();

	GenotypeLocs feedus = new int[rentOne.getArrSize()];

	for (int i = 0; i < split; i++)
		feedus[i] = one[i];
	
	for (int i = split; i < rentOne.getArrSize; i++)
		feedus[i] = two[i];

	GenotypeClass child = GenotypeClass(rentOne.getArrSize());
	if (getRandom(N) > (N / 10))
		child.MutateGenotype(getRandom(N), getRandom(N));

	child.SetGenotypeLocs(feedus);

	return child;
}

