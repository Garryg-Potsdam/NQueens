#include "ExceptionClass.h"
#include <string>

const int DEFAULT_SIZE = 8;

const float EPSILON = 0.0001f;

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

	std::string ToString();

protected:
	void GenerateGenotype(int s);

	void CalculateFitness();
	
	float GetRowCollisions();

	float GetDiaCollisions();

	//int GetDiaCollisions(int m);

	void SetArrPointer(int * ptr);

	void SetSize(int size);

private:
	std::string PrintTopAndBottom();

	GenotypeLocs gl;
	int arrSize;
	float fitness;
	bool mFlag;
};
