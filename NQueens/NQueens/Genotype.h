///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                           Genotype Definition File                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//	Author:    Garry Griggs & Gregory Hughes                                 //
//	Date:      9/26/2016                                                     //
//	Project:   NQueens                                                       //
//	FileName:  GenotypeClass.h                                               //
//	Purpose:   This file contains the definitions for the genotype object    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "ExceptionClass.h"
#include <string>
#include <vector>
#include <iostream>

const float EPSILON = 0.0001f;

typedef std::vector<int> GenotypeLocs;

class Genotype
{
public:
	Genotype();
	Genotype(int size);

	int getArrSize() const;
	void printGenome();
	void SetArrSize(int size);

	void SetGenotypeLocs(GenotypeLocs &locs);

	void GetGenotypeLocs(GenotypeLocs &locs);

	void MutateGenotype(int one, int two);

	float GetFitness();

	bool WasSelectedForMatingPool();

	void SetSelectedForMatingPool(bool set);

	std::string ToString();

protected:
	void GenerateGenotype(int s);

	void CalculateFitness();
	
	float GetRowCollisions();

	float GetDiaCollisions();

private:
	std::string PrintTopAndBottom();

	GenotypeLocs gl;
	int arrSize;
	float fitness;
	bool mFlag;
};
