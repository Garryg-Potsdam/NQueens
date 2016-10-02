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
#include <iostream>

const int DEFAULT_SIZE = 8;

const float EPSILON = 0.0001f;

typedef int * GenotypeLocs;

class GenotypeClass
{
public:
	GenotypeClass();

	GenotypeClass(int size);

	int getArrSize() const;

	void SetArrSize(int size);

	GenotypeLocs GetGenotypeLocs();

	void SetGenotypeLocs(GenotypeLocs locs);

	void MutateGenotype(int one, int two);

	float GetFitness();

	bool WasSelectedForMatingPool();

	void SetSelectedForMatingPool(bool set);

	virtual bool operator<=(const GenotypeClass & rtOp) const;

	virtual bool operator>=(const GenotypeClass & rtOp) const;

	virtual bool operator<(const GenotypeClass & rtOp) const;

	virtual bool operator>(const GenotypeClass & rtOp) const;

	virtual bool operator==(const GenotypeClass & rtOp) const;

	virtual bool operator!=(const GenotypeClass & rtOp) const;

	std::string ToString();

protected:
	void GenerateGenotype(int s);

	void CalculateFitness();
	
	float GetRowCollisions();

	float GetDiaCollisions();

	void SetArrPointer(int * ptr);

	void SetSize(int size);

private:
	std::string PrintTopAndBottom();

	int * gl;
	int arrSize;
	float fitness;
	bool mFlag;
};
