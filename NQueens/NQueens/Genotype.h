//#include 

const int DEFAULT_SIZE = 8;

typedef int * GenotypeLocs;

class Genotype
{
public:
	Genotype();
	Genotype(int size);

	Genotype Crossover(const Genotype rentOne, const Genotype rentTwo, int split);

	Genotype Mutate(const Genotype old, int one, int two) const;

protected:
	GenotypeLocs GetArrPointer();
	int getArrSize();
	void SetSize(int size);

private:
	GenotypeLocs gl;
	int arrSize;
};
