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

#include "GenotypeClass.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//                               Public Methods                              //
///////////////////////////////////////////////////////////////////////////////

GenotypeClass::GenotypeClass()
{
	GenerateGenotype(DEFAULT_SIZE);
}

GenotypeClass::GenotypeClass(const int s)
{
	GenerateGenotype(s);
}

int GenotypeClass::getArrSize() const 
{
	return arrSize;
}

GenotypeLocs GenotypeClass::GetGenotypeLocs()
{
	return gl;
}

void GenotypeClass::SetGenotypeLocs(GenotypeLocs locs)
{
	gl = locs;
}

void GenotypeClass::MutateGenotype(int one, int two)
{
	int temp = gl[one];

	gl[one] = gl[two];

	gl[two] = temp;
}

float GenotypeClass::GetFitness()
{
	return fitness;
}

bool GenotypeClass::WasSelectedForMatingPool()
{
	return mFlag;
}

void GenotypeClass::SetSelectedForMatingPool(bool set)
{
	mFlag = set;
}

bool GenotypeClass::operator<=(const GenotypeClass & rtOp) const
{
	return fitness <= rtOp.fitness;
}

bool GenotypeClass::operator>=(const GenotypeClass & rtOp) const
{
	return fitness >= rtOp.fitness;
}

bool GenotypeClass::operator<(const GenotypeClass & rtOp) const
{
	return fitness < rtOp.fitness;
}

bool GenotypeClass::operator>(const GenotypeClass & rtOp) const
{
	return fitness > rtOp.fitness;
}

bool GenotypeClass::operator==(const GenotypeClass & rtOp) const
{
	if (arrSize == rtOp.arrSize)
	{
		for (int i = 0; i < arrSize; i++)
			if (gl[i] != rtOp.gl[i])
				return false;

		return true;
	}
	else
		throw NoComparisonForObjectException();
}

bool GenotypeClass::operator!=(const GenotypeClass & rtOp) const
{
	if (arrSize == rtOp.arrSize)
	{
		for (int i = 0; i < arrSize; i++)
			if (gl[i] != rtOp.gl[i])
				return true;

		return false;
	}
	else
		throw NoComparisonForObjectException();
}

std::string GenotypeClass::ToString()
{
	std::string ans = "";

	std::cout << std::endl;

	for (int i = 0; i < arrSize; i++)
	{
		ans += gl[i] +" ";

		std::cout << *&gl[i] << " ";
	}

	ans += "\n" +  PrintTopAndBottom();

	for (int i = arrSize - 1; i >= 0; i--)
	{
		ans += "\n|";

		// Print board spaces
		for (int j = 0; j < arrSize; j++)
		{
			if (gl[j] == i)
				ans += "Q";
			else
				ans += " ";

			if (j != arrSize - 1)
				ans += " ";
		}

		ans += "|\n";

		if (i != 0) 
		{
			ans += "+";
			// Print inner boarder
			for (int j = 0; j < arrSize; j++)
			{
				ans += " +";
			}
		}
		
	}

	ans += PrintTopAndBottom();

	return ans;
}


///////////////////////////////////////////////////////////////////////////////
//                            Protected Methods                              //
///////////////////////////////////////////////////////////////////////////////


void GenotypeClass::GenerateGenotype(int s)
{
	GenotypeLocs nGl;

	nGl = new int[s];

	for (int i = 0; i < s; i++)
	{
		int temp = std::rand();
		nGl[i] = temp % s;
	}

	gl = nGl;

	SetSize(s);

	CalculateFitness();

	mFlag = false;
}

void GenotypeClass::CalculateFitness()
{
	float collisions = 0.0f;

	collisions += GetRowCollisions();

	collisions += GetDiaCollisions();

	// We double counted...

	collisions = collisions / 2;

	// set PDM

	fitness = 1 / (collisions + EPSILON);
}

float GenotypeClass::GetRowCollisions()
{
	float tot = 0;

	for (int i = 0; i < arrSize; i++)
	{
		int row = gl[i];
		
		for (int j = 0; j < arrSize; j++)
		{
			if (j != i)
			{
				if (gl[j] = gl[i])
					tot++;
			}
		}
	}

	return tot;
}

float GenotypeClass::GetDiaCollisions()
{
	float tot = 0;

	// i is the x coord to check against
	for (int i = 0; i < arrSize; i++)
	{
		// j is the x coord that we are verifying
		// check all coordinates agains the slope and intercept
		for (int j = 0; j < arrSize; j++)
		{
			if (j != i)
			{
				//int x2 = j;
				//int y2 = gl[j];

				//		m =		(y1 - y2)	/ (x1 - x2)
				int slope = (gl[i] - gl[j]) / (i - j);

				// if the slopes on the points match then they are a collision
				//    waiting to happen.
				if (slope == 1 || slope == -1)
					tot++;
			}
		}
	}

	return tot;
}

void GenotypeClass::SetArrPointer(int * ptr) 
{
	gl = ptr;
}

void GenotypeClass::SetSize(int size)
{
	arrSize = size;
}

///////////////////////////////////////////////////////////////////////////////
//                              Private Methods                              //
///////////////////////////////////////////////////////////////////////////////

std::string GenotypeClass::PrintTopAndBottom()
{
	std::string ans;

	ans = "+";

	for (int i = 0; i < arrSize; i++)
		ans += "-+";

	return ans;
}
