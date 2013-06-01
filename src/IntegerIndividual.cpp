#include "Individual.h"
#include "IntegerIndividual.h"
//#include <cstdlib>

random_device seed_gen ;
default_random_engine gen(seed_gen());

IntegerIndividual::IntegerIndividual()
{

	m_length = defaultMaxSize;
	normal_distribution<double> distribution(8.0,8.0); 

	while(1)
	{
		for(int i = 0; i < defaultMaxSize; i++)
		{

			double number = fabs(distribution(gen));	// make sure we only get positive numbers

			while (int(number) == 0 && int(number) <= 30)					// make sure we don't get 0
				number = fabs(distribution(gen));

			m_genotype.push_back((int)number);
		}
		evaluate_fitness();
		if (m_fitness > 0)
			break;
		m_genotype.clear();
	}
}

IntegerIndividual::IntegerIndividual(int length)
{
	m_length = length;


	normal_distribution<double> distribution(8.0,8.0); 
	

	while(1)
	{
		for(int i = 0; i < defaultMaxSize; i++)
		{

			double number = fabs(distribution(gen));

			while (int(number) == 0)
				number = fabs(distribution(gen));

			m_genotype.push_back((int)number);
		}
		evaluate_fitness();
		if (m_fitness > 0)
			break;
	}
}

void IntegerIndividual::evaluate_fitness()
{
	int weight[15] = {25,20,31,45,15,32,28,26,13,17,19,38,21,38,29}; // weight
	int value[15] = {300,220,350,405,215,328,257,339,223,222,207,360,268,341,301}; // value
	m_fitness = 0;
	_weight = 0;
	for(int i = 0;i<defaultMaxSize;i++)
		m_fitness += (int)m_genotype[i] * value[i];
	for(int i =0;i<defaultMaxSize;i++)
		_weight += (int)m_genotype[i] * weight[i];

	if(_weight > maxCapacity)
		m_fitness = 0;

}

IntegerIndividual& operator!(IntegerIndividual& target)
{
	//int mutationType = 0;
	int temp;
	int pointA = rand() % target.m_length;
	int pointB = rand() % target.m_length;
	int randomPoint = rand() % target.m_length;
	double Pm = 0.1;
	int random;
	while(pointA == pointB)	// avoid picking the same point
		pointB = rand () % target.m_length;

	switch(target.mutationType)
	{
	case 0: // Select 2 random points, shuffle in between
		if (pointA < pointB)
			random_shuffle(target.m_genotype.begin() + pointA, target.m_genotype.begin() + pointB);
		else
			random_shuffle(target.m_genotype.begin() + pointB, target.m_genotype.begin() + pointA);
		
		target.evaluate_fitness();
		

				target.evaluate_fitness();
		
		return target;
		break;
	case 1: // random point has a random number Xi
		target.m_genotype[pointA] = rand () % 30 + 1;
		target.m_genotype[pointB]--;
		if(target.m_genotype[pointB] <= 0)
			target.m_genotype[pointB]++;
		if(target.m_genotype[pointA] >= 25)
			--target.m_genotype[pointA];
		target.evaluate_fitness();


		return target;
		break;
	case 2: // swap 2 random points
		temp = (int)target.m_genotype[pointA];
		target.m_genotype[pointA] = target.m_genotype[pointB];
		target.m_genotype[pointB] = temp;
		target.evaluate_fitness();
		return target;
		break;

	default: cout << "Wrong Mutation type" << endl;

	}
}

