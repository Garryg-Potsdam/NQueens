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
#include <cstdlib>

// Epsilon to calculate fitness
const float EPSILON = 0.0001f;

// The default value to build board and genotype
const int DEFAULT_N = 8;

// typedef to hole Genotype vector
typedef std::vector<int> GenotypeLocs;

class Genotype
{
public:
	///////////////////////////////////////////////////////////////////////////////
	//                                Constructors                               //
	///////////////////////////////////////////////////////////////////////////////
	// Non-default contructor
	// Params:	size - integet size of the genotype to build
	// Post:	A vector to hold a default size of 'size' will be created
	Genotype();

	// Non-default contructor
	// Params:	size - integet size of the genotype to build
	// Post:	A vector to hold a default size of 'size' will be created
	Genotype(int size);

	///////////////////////////////////////////////////////////////////////////////
	//                              Begin  Methods                               //
	///////////////////////////////////////////////////////////////////////////////

	// Params:	None
	// Post:	The size of the gl vector is returned
	int GetVectorSize() const;

	// test function
	/*void printGenome();*/

	// Params:	size - new size of the vector
	// Post:	The size of the vector is changed to 'size'
	void SetVectorSize(int size);

	// Params:	A seperate genotype is created is given to method
	// Post:	The object is updated to the given locs
	void SetGenotypeLocs(GenotypeLocs &locs);

	// Params:	A blank genotype is created and given to method to modify
	// Post:	The locs is updated to the current object
	void GetGenotypeLocs(GenotypeLocs &locs);

	// Params:	one, two, the positions in the vector to swap
	// Post:	The positions in the vector, one and two, are swapped
	void MutateGenotype(int one, int two);

	// Params:	one, two, the positions in the vector to randomize
	// Post:	Specific positions in the vector are randomized
	void MutateGenotypeAllele(int one, int two, int n);
	
	// Params:	none
	// Post:	The fitness of the current Genome is returned
	float GetFitness();

	// Params:	None
	// Post:	predicates to caller if genome was selected for mating
	bool WasSelectedForMatingPool();

	// Params:	Boolean set, true if selected false otherwise
	// Post:	PDM for selection set to 'set'
	void SetSelectedForMatingPool(bool set);

	// Params:	None
	// Post:	A string is returned to caller showing the board 
	//			and the positions of the queens 
	std::string ToString();
	
protected:
	// Params:	size - The size of the genome to generate
	// Post:	The genome is generated
	void GenerateGenotype(int s);

	// Params:	None
	// Post:	The fitness for the current genotype is calculated
	void CalculateFitness();
	
	// Params:	None
	// Post:	The number of collisions for all rows is returned(double)
	float GetRowCollisions();

	// Params: none
	// Post:	The number of collisions for all diagonal options is calculated
	//			(double)
	float GetDiaCollisions();

private:
	// Params:	none
	// Post:	A string of the top/bottom of the board is returned to caller
	std::string PrintTopAndBottom();

	///////////////////////////////////////////////////////////////////////////
	//                          Private Data Members                         //
	///////////////////////////////////////////////////////////////////////////

	GenotypeLocs gl;	// Vector to hold genome
	float fitness;		// The fitness of the genome
	int vectorSize;		// Size of the Vector
	bool mFlag;			// PDM flag predicating if object is selected for mating
};
