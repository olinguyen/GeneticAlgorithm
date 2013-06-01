#ifndef POPULATION_H
#define POPULATION_H
//#include "Individual.h"
#include "RealIndividual.h"
#include "BinaryIndividual.h"
#include "IntegerIndividual.h"
//using namespace std;



//default_random_engine generator;
const double maximum = 32.768;


template <class T>
class Population
{
    private:
		double m_mutationRate, m_factor;			// size of population & probabilty of mutation & standard deviation factor
		int m_most_fit;							// best fitness 
		int m_oldest;								// Oldest individual of the population
		vector <double> most_fit;					// vector holding the best fitness for each generation
		vector <double> mostFitMean;				// vector holding the mean fitness for each generation
		vector<T> population;				// vector that holds all the individuals
		vector<T> temp_pop;				// Virtual population consisting of parents and offspring


		static int m_size;
		static const int defaultMaxSize = 100;		// Default size
		double meanAge;								// Average age in generations of the population
		double meanFitness;							// Average Fitness of population

		friend Individual& operator!(Individual&);	// mutation performed by a friend function - needs access to private members
		friend pair<RealIndividual, RealIndividual> operator*(RealIndividual parent1, RealIndividual parent2);
		template <class T>
		friend pair<T,T> operator*(T parent1, T parent2);
		template <class T>
		friend struct SortByFitness;				// Will sort individuals by fitness in the population
		T bestInd;							// best individual

public:
		Population();													// Default constructor creates random size population up to defaultMaxSize
		Population(int size, int length);									// Creates a population of N indvidiuals and user-defined length
		void evaluate_pop();												// evaluates fitness of all the population
        void show_popfitness();												// Show the fitness of each individual in the population
		int give_mostfit() {return m_most_fit;}							// returns the most fit indvidual
		void set_probabilities(double mutationRate, double factor);			// sets the probabilities for the mutation function
		void find_mostfit();												// Will find the most fit individual in the population and display them
		void AckleyCrossover();												// takes all and produces offspring
		void KnapsackCrossover();												// takes all and produces offspring

		void operator!();													// Mutates the population; returns self, which is now a new population
		void parent_selection();											// Selects a parent using roulette wheel selection
		Population& knapsackParentSelection();
		void survival_selection(int tournamentSize);
		Population& knapsackSurvivalSelection(int);
		void elite_selection(double);		
		void save_fitness();												// Saves the fitness of the population into a txt file
		void evaluateMeanAge();
		void evaluateMeanFitness();
		void printPopulationWeight();
		void mutateKnapsack();
		void checkSurvival(int);
		void setMutationType(int);
		void show_individual(int x);										// will display the genotype of the individual X in the population
		void show_offspring(int x);											// will display the genotype of the offspring X in the population
		void show_parent(int x);											// will display the genotype of the parent X in the population
		void show_best();

friend class Evolution;
};

template <class T>
struct SortByFitness
{
   bool operator()(T  & L, T  & R) 
   { return L.m_fitness < R.m_fitness; }
};

template <class T>
int Population<T>::m_size = 0;	

template <class T>
Population<T>::Population()  // Creates a population of N indviduals
{

		for(int i=0;i<defaultMaxSize;i++)
		{
			T temp;
			population.push_back(temp);
			m_size++;
		}		
	
}

template <class T>
Population<T>::Population(int size, int length)  // Creates a population of N indviduals
{
	
	for(int i=0;i<size;i++)
	{
		T temp(length);
		population.push_back(temp);
		m_size++;
	}
	
 }

template <class T>
void Population<T>::evaluate_pop() // evaluates fitness of the population
{
    for(int i=0;i<m_size;i++)
        population[i].evaluate_fitness();
}
template <class T>
void Population<T>::set_probabilities(double mutationRate, double factor) // will define the probabilities for mutation
{
	m_mutationRate  = mutationRate;
	m_factor = factor;
}

template <class T>
void Population<T>::setMutationType(int mutationType)
{
	for(size_t i=0;i<temp_pop.size();i++)
		temp_pop[i].setMutationType(mutationType);

}

template <class T>
void Population<T>::checkSurvival(int maxAge)
{
	
	SortByFitness<T> es;
	std::sort(temp_pop.begin(), temp_pop.end(), es);

	for(size_t i =0;i<temp_pop.size();i++)
	{
		if(temp_pop[i].getAge() == maxAge)
		{
			temp_pop.erase(temp_pop.begin() + i);				// deletes element if max age is reached
			i--;
		}
	}
	
	for(size_t i=0;i<temp_pop.size();i++)
	{
		if (temp_pop[i].getElite() == true)
		{
			//cout << temp_pop[i].show_fitness() << endl;
			temp_pop[i].incrementAge();
			population.push_back(temp_pop[i]);					// Elites get a free pass
			temp_pop.erase(temp_pop.begin() + i);
			i--;
			m_size++;

		}
	}
}

template <class T>
void Population<T>::find_mostfit() // will find the most fit individual and display fitness and genotype
{
		int best = 0;
		T bestindividual;

        for(int i=0;i<m_size;i++)
			{
				if (population[i].getFitness() > best){
					best = (int)population[i].getFitness();
					bestindividual = population[i];
				}
			}
		bestInd = bestindividual;
		m_most_fit = best;
		//most_fit.push_back(m_most_fit);
}
template <class T>
void Population<T>::evaluateMeanAge()
{
	int oldest = 0;
	double sum =0.0;
	for(int i=0;i<m_size;i++)
		sum += (double)population[i].getAge();

	for(int i=0;i<m_size;i++)
	{
		if(population[i].getAge() > oldest)
			oldest = population[i].getAge();
	}
	m_oldest = oldest;
	sum = sum / (double)m_size;
	meanAge = sum;
	cout << "Mean Age " << meanAge << endl;
}

template <class T>
void Population<T>::evaluateMeanFitness()
{
	double sum =0.0;
	for(int i=0;i<m_size;i++)
		sum += population[i].getFitness();

	sum = sum / (double)m_size;
	meanFitness = sum;
	cout << "Average fitness: " << meanFitness << endl;
	//mostFitMean.push_back(meanFitness);
}

template <class T>
void Population<T>::show_popfitness() // Shows entire population fitness
{
	for(int i=0;i<m_size;i++)
		cout << setprecision(5) << population[i].show_fitness() << endl;

}

template <class T>
void Population<T>::printPopulationWeight() // Shows entire population fitness
{
	for(int i=0;i<m_size;i++)
		population[i].printWeight();
}

template <class T>
void Population<T>::parent_selection()
{
	double sum_fitness = 0.0;
	double random;
	double sum_check = 0.0;

	double bestFitness = 100.0;
	int randomPick = rand() % m_size;

	// Roulette Wheel selection

		for(int i=0;i<m_size;i++)
			sum_fitness += population[i].getFitness();  // Calculate sum of all fitnesses in population

		
		random = sum_fitness*rand()/(RAND_MAX); // Generate random number from interval (0,S)
			for(int i=0;i<m_size;i++) // Go through the population and sum fitnesses from 0 - sum s. When the sum s is greater then r, stop and return the chromosome where you are. 
			{
				sum_check += population[i].getFitness();
				if (sum_check >= random)
				{
					temp_pop.push_back(population[i]); // add chosen individual to parent vector
					population.erase(population.begin()+i); // remove from intial pool
					m_size--; // decrement initial pool size	
					

				}
			}
}


template <class T>
Population<T>& Population<T>::knapsackParentSelection()
{

	int sum_fitness = 0;
	int random;
	int sum_check = 0;


	// Roulette Wheel selection
	
		for(int i=0;i<m_size;i++)
			sum_fitness += (int)population[i].getFitness();  // Calculate sum of all fitnesses in population

		
		random = rand() % (sum_fitness+1); // Generate random number from interval (0,S)
			for(int i=0;i<m_size;i++) // Go through the population and sum fitnesses from 0 - sum s. When the sum s is greater then r, stop and return the chromosome where you are. 
			{
				sum_check += (int)population[i].getFitness();
				if (sum_check >= random)
				{
					temp_pop.push_back(population[i]); // add chosen individual to parent vector
					population.erase(population.begin()+i); // remove from intial pool
					m_size--; // decrement initial pool size	
					return *this;
				}
			}


			
			return *this;
}

template <class T>
Population<T>& Population<T>::knapsackSurvivalSelection(int tournamentSize)
{

	int bestPosition = 1;
	int bestFitness = 0;
	//int tournamentSize = 4;
    vector <int> index(tournamentSize);					// vector holding K integers ( position )

	for(int i=1;i<tournamentSize;i++)
	{   
		index[i] = rand() % temp_pop.size();

	}

	for(int i=0;i<tournamentSize;i++)
	{
		if (temp_pop[index[i]].getFitness() > bestFitness)	// find the most fit of the K chosen
		{
			bestFitness = (int)temp_pop[index[i]].getFitness();
			bestPosition = index[i];
		}
	}

	temp_pop[bestPosition].incrementAge();
	population.push_back(temp_pop[bestPosition]);		// add most fit of tournament to new population
	temp_pop.erase(temp_pop.begin() + bestPosition);
	m_size++;
	index.clear();
	return *this;

}

template <class T>
void Population<T>::survival_selection(int tournamentSize)		// Tournament selection : randomly  selected  individuals in a subgroup compete and the fittest is selected
{

	double bestFitness = 100.0;
	int bestPosition = 1;

    vector <int> index(tournamentSize);					// vector holding K integers ( position )

	for(int i=0;i<tournamentSize;i++)
	{
		index[i] = rand() % temp_pop.size();
			index[i] = rand() % temp_pop.size();
	}
	for(int i=0;i<tournamentSize;i++)
	{
		if (temp_pop[index[i]].getFitness() < bestFitness)	// find the most fit of the K chosen
		{
			bestFitness = temp_pop[index[i]].getFitness();
			bestPosition = index[i];
		}
	}

	temp_pop[bestPosition].incrementAge();
	population.push_back(temp_pop[bestPosition]);		// add most fit of tournament to new population
	temp_pop.erase(temp_pop.begin() + bestPosition);
	m_size++;
	index.clear();


}
template <class T>
void Population<T>::elite_selection(double elitismRate)		// go through entire population and check their fitness		
{
	double maxElites;
	bool isKnapsack = 1;
	int count = 0;
	maxElites =  floor(population.size() * elitismRate);

	SortByFitness<T> es;

	std::sort(population.begin(), population.end(), es);

	for(int i=0;i<m_size;i++)
		population[i].setFalse();
	

	if(isKnapsack == true){
		for(int i=population.size()-1;i>(population.size()-1-maxElites);i--){
			population[i].setElite();
		}
	}

	else
		for(int i=0;i<maxElites;i++)
			population[i].setElite();

}

template <class T>
void Population<T>::AckleyCrossover() // crosses all parents, puts them in offspring vector
{
	RealIndividual temp1(10), temp2(10);
	pair<RealIndividual, RealIndividual> offspring(temp1,temp2);

	for(size_t i=0;i<defaultMaxSize;i+=2)
	{
		offspring = temp_pop[i] * temp_pop[i+1];
		temp_pop.push_back(offspring.first);
		temp_pop.push_back(offspring.second);
	}
}

template <class T>
void Population<T>::KnapsackCrossover()
{

	T temp1, temp2;
	pair<T, T> offspring(temp1,temp2);

	for(size_t i=0;i<defaultMaxSize;i+=2)
	{
		offspring = temp_pop[i] * temp_pop[i+1];
		temp_pop.push_back(offspring.first);
		temp_pop.push_back(offspring.second);
	}


}

template <class T>
pair<T,T> operator*(T parent1, T parent2) // crosses over 2 parents, produces 2 offspring
{

	T offspring1, offspring2;

		int crossover_point = rand() % (parent1.m_length-1) + 1;

			for(int i=0;i<crossover_point;i++)
				offspring1.m_genotype[i] = parent1.m_genotype[i];
			for(int i=crossover_point;i<parent1.m_length;i++)
				offspring1.m_genotype[i] = parent2.m_genotype[i];

			for(int i=0;i<crossover_point;i++)
				offspring2.m_genotype[i] = parent2.m_genotype[i];
			for(int i=crossover_point;i<parent1.m_length;i++)
				offspring2.m_genotype[i] = parent1.m_genotype[i];
			offspring1.evaluate_fitness();
			offspring2.evaluate_fitness();

			return make_pair(offspring1,offspring2);

 }

template <class T>

void Population<T>::operator!()
{
		double stdeviation;
		double mean;
        double random;

		for(size_t j=0;j<temp_pop.size()/2;j++) // will go through PARENTS
		{
            for(int i=0;i<temp_pop[j].m_length;i++) // will go through every element
            {
				random = rand() % 100 + 1;
				random = random/100.0;
				if (random <= m_mutationRate && temp_pop[j].isElite == false) // 10% per element for mutation
				{
					stdeviation = fabs(temp_pop[j].m_genotype[i] * m_factor); // STANDARD DEVIATION WILL BE A % OF THE INITIAL SOLUTION
					mean = temp_pop[j].m_genotype[i];

					normal_distribution<double> distribution(mean,stdeviation); // will produce noise/small variation to the element of the individual
						double number = distribution(generator);
						temp_pop[j].m_genotype[i] = number;

						while (fabs(temp_pop[j].m_genotype[i]) > maximum)
						{

							number = distribution(generator);
							temp_pop[j].m_genotype[i] = number;
						}
				}
            }
			temp_pop[j].evaluate_fitness();
		}

}

template <class T>
void Population<T>::show_individual(int x) // display a certain individual's genotype
{
	population[x].show_genotype();
}
template <class T>
void Population<T>::show_best()
{
		cout << endl << "Most fit individual has a fitness of: " << m_most_fit << endl;

		cout << "Genotype of the current most fit individual:" << endl;
		bestInd.show_genotype();
}

template <class T>
void Population<T>::mutateKnapsack()
{
	for(size_t i=0;i<temp_pop.size()/2;i++)
	{
		if (temp_pop[i].getElite() != true){
		!temp_pop[i];
	//	while(temp_pop[i].getFitness() == 0)
		//	!temp_pop[i];
		}
	}
}



#endif // POPULATION_H




//void operator!(); // the mutation function with the operator overloaded
/*
vector<T> operator*(T parent1, T parent2) // crosses over 2 parents, produces 2 offspring
{
	vector<T> offspringContainer;
	T offspring1, offspring2;

		int crossover_point = rand() % (parent1.m_length-1) + 1;

			for(int i=0;i<crossover_point;i++)
				offspring1.m_genotype[i] = parent1.m_genotype[i];
			for(int i=crossover_point;i<parent1.m_length;i++)
				offspring1.m_genotype[i] = parent2.m_genotype[i];

			for(int i=0;i<crossover_point;i++)
				offspring2.m_genotype[i] = parent2.m_genotype[i];
			for(int i=crossover_point;i<parent1.m_length;i++)
				offspring2.m_genotype[i] = parent1.m_genotype[i];
			offspring1.evaluate_fitness();
			offspring2.evaluate_fitness();

			offspringContainer.push_back(offspring1);
			offspringContainer.push_back(offspring2);
			offspring1.show_genotype();
			offspring2.show_genotype();
			return offspringContainer;

 }
 */