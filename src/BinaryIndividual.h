#ifndef BinaryIndividual_H
#define BinaryIndividual_H
#include "Individual.h"
class BinaryIndividual: public Individual
{
private: 
		int _value;
		int _weight;
		static const int maxCapacity = 200;
		static const int defaultMaxSize = 15;

public:
		BinaryIndividual();
		BinaryIndividual(int length);
		void evaluate_fitness();
		int getWeight() {return _weight;}
		void printWeight() {cout << "Weight: " << _weight << endl;}
		void mutateA();
		void mutateB();
		void mutateC();

		friend BinaryIndividual& operator!(BinaryIndividual&);	// mutation performed by a friend function - needs access to private members
};

#endif