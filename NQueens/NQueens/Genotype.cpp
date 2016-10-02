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
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//                               Public Methods                              //
///////////////////////////////////////////////////////////////////////////////

Genotype::Genotype()
{
	GenerateGenotype(DEFAULT_SIZE);
}

Genotype::Genotype(const int s)
{
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

void Genotype::SetGenotypeLocs(GenotypeLocs & locs)
{
	for (int i = 0; i < arrSize; i++)
	{
		gl[i] = locs[i];
	}
}

void Genotype::GetGenotypeLocs(GenotypeLocs & locs)
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
	std::string ans = "";
	
	for (int i = 0; i < arrSize; i++)
	{
		ans += gl[i] +" ";
	}

	ans += "\n" +  PrintTopAndBottom();

	for (int i = arrSize - 1; i >= 0; i--)
	{
		ans += "\n|";
		// Print board spaces
		for (int j = 0; j < arrSize; j++)
		{
			if (gl[i] == j)
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


void Genotype::GenerateGenotype(int s)
{
	for (int i = 0; i < s; i++)
	{
		int temp = std::rand();
		gl[i] = temp % s;
	}

	SetSize(s);

	CalculateFitness();

	mFlag = false;
}

void Genotype::CalculateFitness()
{
	float collisions = 0.0f;

	collisions += GetRowCollisions();

	collisions += GetDiaCollisions();

	// We double counted...

	collisions = collisions / 2;

	// set PDM

	fitness = 1 / (collisions + EPSILON);
}

float Genotype::GetRowCollisions()
{
	float tot = 0;

	for (int i = 0; i < arrSize; i++)
	{
		int row = gl[i];
		
		for (int j = 0; j < arrSize; j++)
		{
			if (j != i)
			{
				if (gl[j] == gl[i])
					tot++;
			}
		}
	}

	return tot;
}

float Genotype::GetDiaCollisions()
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

void Genotype::SetSize(int size)
{
	arrSize = size;
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
