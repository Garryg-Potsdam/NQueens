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


#include "GenotypeClass.h"

class PopulationClass
{
public:
	PopulationClass(int n, bool build);

	GenotypeClass Crossover(GenotypeClass & rentOne, 
							GenotypeClass & rentTwo, 
							int split);
	
	GenotypeClass getGenotype(int i);
	
	void addChildren(PopulationClass p, int totalChildren);
	
	int getRandom(int n);
	
	void addChild(GenotypeClass gt);
	
	void buildPopulation();

private:

	int populationSize;
	int N;
	int size;
	GenotypeClass *gts;
};