#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <random>
#include <fstream>
#include <utility>
#include <algorithm> 

using namespace std;



class Individual
{
		protected:
			vector<double> m_genotype;	// Vector containing the elements of the individiual
            int m_length;				// Gives the length of the individual vector
			int age;
			double m_fitness;			// Holds the fitness of the individual
			int mutationType;

        private:
			//static const int defaultMaxSize = 10;		// default maximum genotype size
			virtual void evaluate_fitness() = 0;					// Evalulates fitness of individual
			bool isElite;



			template <class T>
			friend pair<T,T> operator*(T parent1, T parent2);
			template <class T>
			friend struct SortByFitness;

        public:

			Individual();								// default constructor creates random size genotype up to defaultMaxSize
            Individual(int length);						// Generates an individual by random with N elements
			//~Individual();
			Individual(vector<double>);					// constructor creates Individual with specified genotype
			Individual(vector<int>);					// constructor creates Individual with specified genotype
			Individual(vector<bool>);					// constructor creates Individual with specified genotype
			double getFitness() {return m_fitness;}
            void show_genotype();						// Displays content of the individual
			void printFitness() {cout << "Fitness: " << m_fitness << endl;}
            double show_fitness() {return m_fitness;}	// display fitness of the individual (Ackley's function)
			bool getElite() {return isElite;}
			void setElite() {isElite = true;}
			void setFalse() {isElite = false;}
			int getAge() {return age;}
			void incrementAge() {age++;}
			void setMutationType(int type) {mutationType = type;}

//friend class Population;
friend class Evolution;

};

#endif // INDIVIDUAL_H
