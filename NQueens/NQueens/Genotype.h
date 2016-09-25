//#include 

const int DEFAULT_SIZE = 8;

typedef int * GenotypeLocs;

class Genotype
{
public:
	Genotype();
	Genotype(int size);

	int getArrSize() const;

protected:
	
	int * GetArrPointer();

	void SetArrPointer(int * ptr);

	void SetSize(int size);

private:
	int * gl;
	int arrSize;

};
