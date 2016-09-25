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

}

void Genotype::SetSelectedForMatingPool()
{

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

}

//int * Genotype::GetArrPointer() 
//{
//	return gl;
//}

void Genotype::SetArrPointer(int * ptr) 
{
	gl = ptr;
}

void Genotype::SetSize(int size)
{
	arrSize = size;
}

