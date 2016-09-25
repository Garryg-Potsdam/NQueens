#include "Genotype.h"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
//                             Public Methods                              //
/////////////////////////////////////////////////////////////////////////////

Genotype::Genotype()
{
	Genotype(DEFAULT_SIZE);
}

Genotype::Genotype(const int s)
{
	GenerateGenotype(s);

	SetSize(s);

	CalculateFitness();

	mFlag = false;
}

int Genotype::getArrSize() const 
{
	return arrSize;
}

GenotypeLocs Genotype::GetGenotypeLocs()
{
	return gl;
}

void Genotype::SetGenotypeLocs(GenotypeLocs locs)
{
	gl = locs;
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

bool Genotype::operator<=(const Genotype & rtOp) const
{
	return fitness <= rtOp.fitness;
}

bool Genotype::operator>=(const Genotype & rtOp) const
{
	return fitness >= rtOp.fitness;
}

bool Genotype::operator<(const Genotype & rtOp) const
{
	return fitness < rtOp.fitness;
}

bool Genotype::operator>(const Genotype & rtOp) const
{
	return fitness > rtOp.fitness;
}

bool Genotype::operator==(const Genotype & rtOp) const
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

bool Genotype::operator!=(const Genotype & rtOp) const
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

std::string Genotype::ToString()
{
	std::string ans;



	for (int i = arrSize - 1; i > 0; i--)
	{


		for (int j = 0; j < arrSize; j++)
		{

		}
	}

	return ans;
}


/////////////////////////////////////////////////////////////////////////////
//                           Protected Methods                             //
/////////////////////////////////////////////////////////////////////////////


void Genotype::GenerateGenotype(int s)
{
	GenotypeLocs nGl;

	nGl = new int[s];

	for (int i = 0; i < s; i++)
		nGl[i] = rand() % s;

	gl = nGl;
}

void Genotype::CalculateFitness()
{
	float collisions = 0.0f;

	collisions += GetRowCollisions();

	collisions += GetDiaCollisions();

	// We double counted...

	collisions = collisions / 2;

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
				if (gl[j] = gl[i])
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
				int x2 = j;
				int y2 = gl[j];

				//		m = (x1 - x2) / (y1 - y2)
				int slope = (i - j) / (gl[i] - gl[j]);

				// if the slopes on the points match then they are a collision waiting to happen.
				if (slope == 1 || slope == -1)
					tot++;
			}
		}
	}

	return tot;
}

void Genotype::SetArrPointer(int * ptr) 
{
	gl = ptr;
}

void Genotype::SetSize(int size)
{
	arrSize = size;
}

/////////////////////////////////////////////////////////////////////////////
//                             Private Methods                             //
/////////////////////////////////////////////////////////////////////////////

std::string Genotype::PrintTopAndBottom()
{
	std::string ans;

	return ans;
}
