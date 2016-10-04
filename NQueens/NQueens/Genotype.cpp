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
//#include <cstdlib>

///////////////////////////////////////////////////////////////////////////////
//                               Public Methods                              //
///////////////////////////////////////////////////////////////////////////////

// Non-default contructor
// Params:	size - integet size of the genotype to build
// Post:	A vector to hold a default size of 'size' will be created
Genotype::Genotype()
{
	gl.reserve(DEFAULT_N);
	GenerateGenotype(DEFAULT_N);
}

// Non-default contructor
// Params:	size - integet size of the genotype to build
// Post:	A vector to hold a default size of 'size' will be created
Genotype::Genotype(int s)
{
	SetVectorSize(s);
	gl.resize(s);
	GenerateGenotype(s);
}

// Params:	None
// Post:	The size of the gl vector is returned
int Genotype::GetVectorSize() const 
{
	return vectorSize;
}

// Params:	size - new size of the vector
// Post:	The size of the vector is changed to 'size'
void Genotype::SetVectorSize(int size)
{
	vectorSize = size;
}

// Params:	A seperate genotype is created is given to method
// Post:	The object is updated to the given locs
void Genotype::SetGenotypeLocs(GenotypeLocs &locs)
{
	for (int i = 0; i < vectorSize; i++)
	{
		gl[i] = locs[i];
	}
	CalculateFitness();
}

// Params:	A blank genotype is created and given to method to modify
// Post:	The locs is updated to the current object
void Genotype::GetGenotypeLocs(GenotypeLocs &locs)
{
	for (int i = 0; i < vectorSize; i++)
	{
		locs[i] = gl[i];
	}
}

// Params:	one, two, the positions in the vector to swap
// Post:	The positions in the vector, one and two, are swapped
void Genotype::MutateGenotype(int one, int two)
{
	int temp = gl[one];

	gl[one] = gl[two];

	gl[two] = temp;
	CalculateFitness();
}

// Params:	one, two, the positions in the vector to randomize
// Post:	Specific positions in the vector are randomized
void Genotype::MutateGenotypeAllele(int one, int two, int n)
{
	gl[one] = rand() % n;

	gl[two] = rand() % n;
	CalculateFitness();
}

// Params:	none
// Post:	The fitness of the current Genome is returned
float Genotype::GetFitness()
{
	return fitness;
}

// Params:	None
// Post:	predicates to caller if genome was selected for mating
bool Genotype::WasSelectedForMatingPool()
{
	return mFlag;
}

// Params:	Boolean set, true if selected false otherwise
// Post:	PDM for selection set to 'set'
void Genotype::SetSelectedForMatingPool(bool set)
{
	mFlag = set;
}

// Params:	None
// Post:	A string is returned to caller showing the board 
//			and the positions of the queens 
std::string Genotype::ToString()
{
	std::string ans = PrintTopAndBottom();

	for (int row = 0; row < vectorSize; row++) {
		ans += "\n|";
		for (int col = 0; col < vectorSize; col++) {
			if (gl[col] == row)
				ans += "Q";
			else
				ans += " ";
			if (col < vectorSize - 1)
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

// Params:	size - The size of the genome to generate
// Post:	The genome is generated
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

// test function
//void Genotype::printGenome() {
//	for (int i = 0; i < arrSize; i++)
//		std::cout << "[" << gl[i] <<  "]";
//	std::cout << std::endl;
//}

// Params:	None
// Post:	The fitness for the current genotype is calculated
void Genotype::CalculateFitness()
{
	float totCollisions = 0.0f;	
	totCollisions = GetRowCollisions() + GetDiaCollisions() + EPSILON;
	// set PDM
	fitness = (1 / totCollisions);
}

// Params:	None
// Post:	The number of collisions for all rows is returned(double)
float Genotype::GetRowCollisions()
{
	float tot = 0;

	std::vector<int> v;
	v.resize(vectorSize);

	for (int i = 0; i < vectorSize; i++) {
		v[gl[i]]++;		
	}

	for (int i = 0; i < vectorSize; i++) {
		if (v[i] > 0)
			tot += (v[i] * (v[i] - 1)) / 2;
	}

	return tot;
}

// Params:	none
// Post:	A string of the top/bottom of the board is returned to caller
float Genotype::GetDiaCollisions()
{
	float tot = 0;
	
	for (int col = 0; col < vectorSize - 1; col++) {		
		float y1 = col;
		float x1 = gl[col];
		for (int col2 = col + 1; col2 < vectorSize; col2++) {
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

// Params:	none
// Post:	A string of the top/bottom of the board is returned to caller
std::string Genotype::PrintTopAndBottom()
{
	std::string ans;

	ans = "+";

	for (int i = 0; i < vectorSize; i++)
		ans += "-+";

	return ans;
}
