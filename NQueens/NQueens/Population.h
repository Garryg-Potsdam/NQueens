class Population {

public:
	Population(int n);
	void buildPopulation();

private:
	int populationSize;
	int N;
	Genotype gts[populationSize];

};