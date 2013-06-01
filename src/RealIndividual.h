#ifndef RealIndividual_H
#define RealIndividual_H
#include "Individual.h"

class RealIndividual: public Individual
{
private: 
		static const int defaultMaxSize = 10;

public:
		RealIndividual();
		RealIndividual(int length);
		void evaluate_fitness();
		void mutateA();
		void mutateB();
		void mutateC();
		friend pair <RealIndividual, RealIndividual> operator*(RealIndividual parent1, RealIndividual parent2);
		friend RealIndividual& operator!(RealIndividual&);	// mutation performed by a friend function - needs access to private members
		//friend vector<T> operator*(T parent1, T parent2);

};

#endif