#ifndef IntegerIndividual_H
#define IntegerIndividual_H
#include "Individual.h"
class IntegerIndividual: public Individual
{
private: 
		int _value;
		int _weight;
		static const int maxCapacity = 5000;
		static const int defaultMaxSize = 15;

public:
		IntegerIndividual();
		IntegerIndividual(int length);
		void evaluate_fitness();
		int getWeight() {return _weight;}
		void printWeight() {cout << "Weight: " << _weight << endl;}
		void mutateA();
		void mutateB();
		
		friend IntegerIndividual& operator!(IntegerIndividual&);	// mutation performed by a friend function - needs access to private members

};

#endif