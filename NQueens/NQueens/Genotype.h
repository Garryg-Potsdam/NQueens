//#include 

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

protected:
	
	int * GetArrPointer();

	void SetArrPointer(int * ptr);

	void SetSize(int size);

private:
	int * gl;
	int arrSize;
	double fitness;
};
