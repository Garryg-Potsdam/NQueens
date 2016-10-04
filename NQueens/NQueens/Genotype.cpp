///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                        Genotype Implementation File                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//	Author:    Garry Griggs & Gregory Hughes                                 //
//	Date:      9/26/2016                                                     //
//	Project:   NQueens                                                       //
//	FileName:  GenotypeClass.cpp                                             //
//	Purpose:   This file contains the implementation for the genotype object //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "Genotype.h"

///////////////////////////////////////////////////////////////////////////////
//                               Public Methods                              //
///////////////////////////////////////////////////////////////////////////////

Genotype::Genotype()
{
	int s = 8;
	gl.reserve(s);
	GenerateGenotype(s);
}

Genotype::Genotype(int s)
{
	SetArrSize(s);
	gl.resize(s);
	GenerateGenotype(s);
}

int Genotype::getArrSize() const 
{
	return arrSize;
}

void Genotype::SetArrSize(int size)
{
	arrSize = size;
}

void Genotype::SetGenotypeLocs(GenotypeLocs &locs)
{
	for (int i = 0; i < arrSize; i++)
	{
		gl[i] = locs[i];
	}
	CalculateFitness();
}

void Genotype::GetGenotypeLocs(GenotypeLocs &locs)
{
	for (int i = 0; i < arrSize; i++)
	{
		locs[i] = gl[i];
	}
}

void Genotype::MutateGenotype(int one, int two)
{
	int temp = gl[one];

	gl[one] = gl[two];

	gl[two] = temp;
	CalculateFitness();
}

// Mutate a specific spot to add new values
void Genotype::MutateGenotypeAllele(int one, int two, int n)
{
	gl[one] = rand() % n;

	gl[two] = rand() % n;
	CalculateFitness();
}

float Genotype::GetFitness()
{
	return fitness;
}

bool Genotype::WasSelectedForMatingPool()
{
	return mFlag;
}

void Genotype::SetSelectedForMatingPool(bool set)
{
	mFlag = set;
}

std::string Genotype::ToString()
{
	std::string ans = PrintTopAndBottom();

	for (int row = 0; row < arrSize; row++) {
		ans += "\n|";
		for (int col = 0; col < arrSize; col++) {
			if (gl[col] == row)
				ans += "Q";
			else
				ans += " ";
			if (col < arrSize - 1)
				ans += "|";
		}
		ans += "|";
		ans += "\n" + PrintTopAndBottom();
	}
	

	return ans;
}


///////////////////////////////////////////////////////////////////////////////
//                            Protected Methods                              //
///////////////////////////////////////////////////////////////////////////////


void Genotype::GenerateGenotype(int s)
{
	for (int i = 0; i < s; i++)
	{
		int temp = std::rand();
		gl[i] = temp % s;
	}

	if (rand() % 100 < 10)
		MutateGenotype(rand() % s, rand() % s);
	CalculateFitness();
	mFlag = false;
}

void Genotype::printGenome() {
	for (int i = 0; i < arrSize; i++)
		std::cout << "[" << gl[i] <<  "]";
	std::cout << std::endl;
}

void Genotype::CalculateFitness()
{
	float totCollisions = 0.0f;	
	totCollisions = GetRowCollisions() + GetDiaCollisions() + EPSILON;
	// set PDM
	fitness = (1 / totCollisions);
}

float Genotype::GetRowCollisions()
{
	float tot = 0;

	std::vector<int> v;
	v.resize(arrSize);

	for (int i = 0; i < arrSize; i++) {
		v[gl[i]]++;		
	}

	for (int i = 0; i < arrSize; i++) {
		if (v[i] > 0)
			tot += (v[i] * (v[i] - 1)) / 2;
	}

	return tot;
}

float Genotype::GetDiaCollisions()
{
	float tot = 0;
	
	for (int col = 0; col < arrSize - 1; col++) {		
		float y1 = col;
		float x1 = gl[col];
		for (int col2 = col + 1; col2 < arrSize; col2++) {
			float y2 = col2;
			float x2 = gl[col2];
			if (x2 == x1)
				continue;
			float slope = (y1 - y2) / (x1 - x2);
			if (slope == 1.0 || slope == -1.0) {
				tot++;
			}
		}
	}
	return tot;
}

///////////////////////////////////////////////////////////////////////////////
//                              Private Methods                              //
///////////////////////////////////////////////////////////////////////////////

std::string Genotype::PrintTopAndBottom()
{
	std::string ans;

	ans = "+";

	for (int i = 0; i < arrSize; i++)
		ans += "-+";

	return ans;
}
