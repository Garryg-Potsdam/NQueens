//#include 

const int DEFAULT_SIZE = 8;

typedef int * GenotypeLocs;

class Genotype
{
public:
	Genotype();
	Genotype(int size);

	void Crossover(const Genotype rentOne, const Genotype rentTwo, Genotype & childOne, Genotype & childTwo);

	Genotype Mutate(const Genotype old) const;

protected:
	void SetSize(int size);

private:
	GenotypeLocs gl;
	int arrSize;
};
