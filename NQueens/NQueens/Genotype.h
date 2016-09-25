#include "ExceptionClass.h"

const int DEFAULT_SIZE = 8;

typedef int * GenotypeLocs;

class Genotype
{
public:
	Genotype();

	Genotype(int size);

	int getArrSize() const;

	GenotypeLocs GetGenotypeLocs();

	void SetGenotypeLocs(GenotypeLocs locs);

	void MutateGenotype(int one, int two);

	float GetFitness();

	bool WasSelectedForMatingPool();

	void SetSelectedForMatingPool(bool set);

	virtual bool operator<=(const Genotype & rtOp) const;

	virtual bool operator>=(const Genotype & rtOp) const;

	virtual bool operator<(const Genotype & rtOp) const;

	virtual bool operator>(const Genotype & rtOp) const;

	virtual bool operator==(const Genotype & rtOp) const;

	virtual bool operator!=(const Genotype & rtOp) const;

protected:
	void GenerateGenotype(int s);

	void CalculateFitness();
	
	int GetRowCollisions();

	int GetDiaCollisions();

	//int GetDiaCollisions(int m);

	void SetArrPointer(int * ptr);

	void SetSize(int size);

private:
	GenotypeLocs gl;
	int arrSize;
	float fitness;
	bool mFlag;
};
