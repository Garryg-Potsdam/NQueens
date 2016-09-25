//#include 

const int DEFAULT_SIZE = 8;

typedef int * GenotypeLocs;

class Genotype
{
public:
	Genotype();
	Genotype(int size);
	
	Genotype Mutate(const Genotype old) const;
	int getArrSize();

protected:
	void SetSize(int size);

private:
	GenotypeLocs gl;
	int arrSize;
};
