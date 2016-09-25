#include "Population.h"

using namespace std;

bool foundSolution(Population pop, int N);

int main() {
	
	int N = 8;
	int generations = 1000;	
	Population pop = Population(N);

	while (generations > 0) {		
		if (foundSolution(pop, N)) {
			break;
		}
		generations--;
	}

}

bool foundSolution(Population pop, int N) {
	for (int i = 0; i < N * 10; i++) {
		if (pop.getGenotype(i).getFitness() == 0) {
			return true;
		}
	}
}
