// Olivier Nguyen
// Student ID : 6605583
/*
#include "Population.h"

using namespace std;

default_random_engine generator;
const double maximum = 32.768;
int Population::m_size = 0;	
const double epsilon = 1.0 / 100000000;
bool isContained(vector<int> arr,int n,int x) // check for unique number in a vector to make sure not repeating an individual for selections
{
	for(int i=0;i<n;i++)
	{
	  if(arr[i]==x)
		return true;
	}
	return false;
}

struct SortByFitness
{
   bool operator()(RealIndividual  & L, RealIndividual  & R) 
   { return L.m_fitness < R.m_fitness; }
};

Population::Population()  // Creates a population of N indviduals
{
	meanAge = 0.0;
	for(int i=0;i<defaultMaxSize;i++)
     {
        RealIndividual temp;
        population.push_back(temp);
		m_size++;
     }
}

Population::Population(int size, int length)  // Creates a population of N indviduals
{
	meanAge = 0.0;
      for(int i=0;i<size;i++)
     {
        RealIndividual temp(length);
        population.push_back(temp);
		m_size++;
     }
 }
 
void Population::evaluate_pop() // evaluates fitness of the population
{
    for(int i=0;i<m_size;i++)
        population[i].evaluate_fitness();
}

void Population::set_probabilities(double mutationRate, double factor) // will define the probabilities for mutation
{
	m_mutationRate  = mutationRate;
	m_factor = factor;
}

void Population::find_mostfit() // will find the most fit individual and display fitness and genotype
{
		double best = 100.0;
		RealIndividual bestindividual(population.size());

        for(int i=0;i<m_size;i++)
			{
				if (population[i].m_fitness < best){
					best = population[i].m_fitness;
					bestindividual = population[i];
				}
			}
		bestInd = bestindividual;
		m_most_fit = best;
		//most_fit.push_back(m_most_fit);
}

void Population::evaluateMeanAge()
{
	int oldest = 0;
	double sum =0.0;
	for(int i=0;i<m_size;i++)
		sum += (double)population[i].age;

	for(int i=0;i<m_size;i++)
	{
		if(population[i].age > oldest)
			oldest = population[i].age;
	}
	m_oldest = oldest;
	sum = sum / (double)m_size;
	meanAge = sum;
	cout << meanAge << endl;
}

void Population::evaluateMeanFitness()
{
	double sum =0.0;
	for(int i=0;i<m_size;i++)
		sum += population[i].m_fitness;

	sum = sum / (double)m_size;
	meanFitness = sum;
	cout << "Average fitness: " << meanFitness << endl;
	//mostFitMean.push_back(meanFitness);
}

void Population::show_popfitness() // Shows entire population fitness
{
	for(int i=0;i<m_size;i++)
		cout << setprecision(5) << population[i].show_fitness() << endl;
}

Population& Population::parent_selection()
{
	double sum_fitness = 0.0;
	double random;
	double sum_check = 0.0;

	double bestFitness = 100.0;
	int randomPick = rand() % m_size;

	// Roulette Wheel selection

		for(int i=0;i<m_size;i++)
			sum_fitness += population[i].m_fitness;  // Calculate sum of all fitnesses in population

		
		random = sum_fitness*rand()/(RAND_MAX); // Generate random number from interval (0,S)
			for(int i=0;i<m_size;i++) // Go through the population and sum fitnesses from 0 - sum s. When the sum s is greater then r, stop and return the chromosome where you are. 
			{
				sum_check += population[i].m_fitness;
				if (sum_check >= random)
				{
					temp_pop.push_back(population[i]); // add chosen individual to parent vector
					population.erase(population.begin()+i); // remove from intial pool
					m_size--; // decrement initial pool size	
					
					return *this;
				}
			}
}

Population& Population::survival_selection(int tournamentSize)		// Tournament selection : randomly  selected  individuals in a subgroup compete and the fittest is selected
{

	double bestFitness = 100.0;
	int bestPosition = 1;

    vector <int> index(tournamentSize);					// vector holding K integers ( position )

	for(int i=0;i<tournamentSize;i++)
	{
		index[i] = rand() % temp_pop.size();
		while(isContained(index, i, index[i]))			// will create K unique numbers to avoid pickin the same individual
			index[i] = rand() % temp_pop.size();
	}
	for(int i=0;i<tournamentSize;i++)
	{
		if (temp_pop[index[i]].m_fitness < bestFitness)	// find the most fit of the K chosen
		{
			bestFitness = temp_pop[index[i]].m_fitness;
			bestPosition = index[i];
		}
	}

	temp_pop[bestPosition].age++;
	population.push_back(temp_pop[bestPosition]);		// add most fit of tournament to new population
	temp_pop.erase(temp_pop.begin() + bestPosition);
	m_size++;
	index.clear();

	return *this;
}

Population& Population::elite_selection(double elitismRate)		// go through entire population and check their fitness		
{
	double maxElites;
	int count = 0;
	maxElites =  floor(population.size() * elitismRate);

	sort(population.begin(), population.end(), SortByFitness());
	
	for(int i=0;i<maxElites;i++)
		population[i].isElite = true;

	return *this;
}

Population& Population::RealCrossover() // crosses all parents, puts them in offspring vector
{
	RealIndividual temp1(10), temp2(10);
	pair<RealIndividual, RealIndividual> offspring(temp1,temp2);

	for(size_t i=0;i<defaultMaxSize;i+=2)
	{
		offspring = temp_pop[i] * temp_pop[i+1];
		temp_pop.push_back(offspring.first);
		temp_pop.push_back(offspring.second);
	}

	return *this;
}

pair<RealIndividual, RealIndividual> operator*(RealIndividual parent1, RealIndividual parent2) // crosses over 2 parents, produces 2 offspring
{
	RealIndividual offspring1(parent1.m_length), offspring2(parent2.m_length);
        const double alpha = 0.8;
		int crossover_point = rand() % (parent1.m_length-1) + 1;
		const int crossover_type = 0;

		switch(crossover_type)
		{
		case 0: // First type : chose constant alpha. The offsprings haev a mix of the parents genotype for each cell
			for(int i=0;i<parent1.m_length;i++)
			{
				offspring1.m_genotype[i] = alpha * parent2.m_genotype[i] + (1-alpha) * parent1.m_genotype[i];
				offspring2.m_genotype[i] = alpha * parent1.m_genotype[i] + (1-alpha) * parent2.m_genotype[i];
			}
			offspring1.evaluate_fitness();
			offspring2.evaluate_fitness();
			return make_pair(offspring1, offspring2);
			break;

		case 1: // Second type: Chose a crossover point. Copy the content of first parent. Past that point, will have the content of parent 2
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
			return make_pair(offspring1, offspring2);
			break;
		default: cout << "Invalid crossover type! Please enter 0 or 1" << endl;
			
		}
 }

Population& Population::operator!()
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
	return *this;
}

void Population::show_individual(int x) // display a certain individual's genotype
{
	population[x].show_genotype();
}

void Population::show_best()
{
		cout << endl << "Most fit individual has a fitness of: " << m_most_fit << endl;

		cout << "Genotype of the current most fit individual:" << endl;
		bestInd.show_genotype();
}


*/
/*
Individual& operator!(Individual& target)
{
		double stdeviation;
		double mean;
        double random;
		for(int i=0;i<target.m_length;i++) // will go through every element
            {
				random = rand() % 100 + 1;
				random = random / 100.0;
				if (random <= 0.2) // 10% per element for mutation
				{
					stdeviation = fabs(target.m_genotype[i] * 0.3); // STANDARD DEVIATION WILL BE A % OF THE INITIAL SOLUTION
					mean = target.m_genotype[i];

					normal_distribution<double> distribution(mean,stdeviation); // will produce noise/small variation to the element of the individual
						double number = distribution(generator);
						target.m_genotype[i] = number;
						while (fabs(target.m_genotype[i]) > maximum)
						{
							number = distribution(generator);
							target.m_genotype[i] = number;
						}
						
				}
			}
		target.evaluate_fitness();
		return target;
}
*/

