

#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "Population.h"
class Evolution
{
private: 
	static int m_generation;

public:
	Evolution();

	void IntegerLoop(int maxGeneration, double elitismRate, int maxAge, int mutationType, int tournamentSize);
	void BooleanLoop(int maxGeneration, double elitismRate, int maxAge, int mutationType, int tournamentSize);
	void AckleyLoop(int pop_size, int length, int tournamentSize, int maxGeneration, double mutationRate, double noiseFactor, double elitismRate, int maxAge);
	void testLoop(int maxGeneration, double elitismRate, int maxAge, int mutationType, int tournamentSize);

	
};

#endif


