#include "Individual.h"
#include "BinaryIndividual.h"

BinaryIndividual::BinaryIndividual()
{
	m_length = defaultMaxSize;

	while(1)
	{
		for(int i = 0; i < defaultMaxSize; i++)
			m_genotype.push_back(rand() % 2);

		evaluate_fitness();
		if(m_fitness >0)
			break;
		m_genotype.clear();
	}

}

BinaryIndividual::BinaryIndividual(int length)
{
	rand();
	m_length = length;
	while(1)
	{
		for(int i = 0; i < length; i++)
			m_genotype.push_back(rand() % 2);

		evaluate_fitness();
		if(m_fitness >0)
			break;
	}
}

void BinaryIndividual::evaluate_fitness()
{
	int weight[15] = {25,20,31,45,15,32,28,26,13,17,19,38,21,38,29}; // weight
	int value[15] = {300,220,350,405,215,328,257,339,223,222,207,360,268,341,301}; // value
	m_fitness = 0;
	_weight = 0;
	for(int i = 0;i<defaultMaxSize;i++)
		m_fitness += m_genotype[i] * value[i];
	for(int i =0;i<defaultMaxSize;i++)
		_weight += (int)m_genotype[i] * weight[i];

	if(_weight > maxCapacity)
		m_fitness = 0;

	
}

BinaryIndividual& operator!(BinaryIndividual& target)
{
	//int mutationType = 0;
	int pointA = rand() % target.m_length;
	int pointB = rand() % target.m_length;
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
		return target;
		break;
	
	case 1: // flip a cell
		if (target.m_genotype[pointA] == 0)
		target.m_genotype[pointA] = 1;
		else
		target.m_genotype[pointA] = 0;
		return target;
		break;

	default: cout << "Invalid mutation type" << endl;
	}
}


