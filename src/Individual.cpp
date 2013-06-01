// Olivier Nguyen
// Student ID : 6605583
#include "Individual.h"
using namespace std;
const float pi = atan(1.0f) * 4.0f;

Individual::Individual()
{

	age = 0;
	isElite = false;
	mutationType = 1;
}

Individual::Individual(int length) : m_length(length) // Creates an individual with a random bit string, and computes the fitness. It takes in an argument length whcih will determine the size of the individual
{

	age = 0;
	isElite = false;
}

Individual::Individual(vector<double> SomeGenotype)
{
	for (int i=0;i<m_length;i++)
		m_genotype.push_back(SomeGenotype[i]);

	evaluate_fitness();
	age = 0;
}

void Individual::show_genotype() // Display the bit of string that the individual holds
{
        for(int i=0;i<m_length;i++)
            cout << setprecision(4) << m_genotype[i] << ", ";

		cout << endl;
}


void Individual::evaluate_fitness() // Evaluates the fitness of the individual
{
}
