
#include "Evolution.h"
#include <string>
int Evolution::m_generation = 0;

//template <class T>
Evolution::Evolution()
{	

}

void Evolution::IntegerLoop(int maxGeneration, double elitismRate, int maxAge, int mutationType, int tournamentSize)
{


	Population<IntegerIndividual> intPopulation;
	m_generation = 0;
	
		cout << endl << "Population size: " << intPopulation.defaultMaxSize << endl;
		cout << "Tournament size: " << tournamentSize << endl;
		cout << "Max generations: " << maxGeneration << endl;
		cout << "Elitism rate: " << elitismRate << endl;
		cout << "Maximum age: " << maxAge << endl;
		cout << "Press enter to begin Integer loop with mutation type " << mutationType<< endl;
		cin.get();
		cout << "Loop starting!" << endl;


	while(m_generation != maxGeneration)
	{
		intPopulation.elite_selection(elitismRate);		// select elites

		intPopulation.temp_pop.clear();

		while(intPopulation.m_size != 0)
		intPopulation.knapsackParentSelection();	// select parents

		intPopulation.KnapsackCrossover();
		intPopulation.setMutationType(mutationType);
		intPopulation.mutateKnapsack();

		intPopulation.population.clear();
		intPopulation.m_size = 0;
		intPopulation.checkSurvival(maxAge);					// elites survive & old individuals are eliminated

		while(intPopulation.m_size != intPopulation.defaultMaxSize)
		intPopulation.knapsackSurvivalSelection(tournamentSize);	// select survivors from temporary population

		m_generation++;
		cout << "Generation: " << m_generation << " " << endl;
		//intPopulation.evaluateMeanAge();
		intPopulation.find_mostfit();
		cout << "Most Fit: " << intPopulation.give_mostfit()<< " " ;
		intPopulation.bestInd.printWeight();
	}


		cout << endl << "Most fit individual has a fitness of: "  << intPopulation.m_most_fit << endl;

		cout << "Genotype of the current most fit individual:" << endl;
		intPopulation.bestInd.show_genotype();
		intPopulation.bestInd.printWeight();	

		intPopulation.population.clear();
		intPopulation.m_size = 0;

}



void Evolution::BooleanLoop(int maxGeneration, double elitismRate, int maxAge, int mutationType, int tournamentSize)
{
	Population<BinaryIndividual> BoolPopulation;
	m_generation = 0;

		cout << "Population size: " << BoolPopulation.defaultMaxSize << endl;
		cout << "Tournament size: " << tournamentSize << endl;
		cout << "Max generations: " << maxGeneration << endl;
		cout << "Elitism rate: " << elitismRate << endl;
		cout << "Maximum age: " << maxAge << endl;
		cout << "Press enter to begin Boolean loop with mutation type " << mutationType<< endl;
		cin.get();
		cout << "Loop starting!" << endl;



	while(m_generation != maxGeneration)
	{
		BoolPopulation.elite_selection(elitismRate);		// select elites

		BoolPopulation.temp_pop.clear();

		while(BoolPopulation.m_size != 0)
		BoolPopulation.knapsackParentSelection();	// select parents

		BoolPopulation.KnapsackCrossover();
		BoolPopulation.setMutationType(mutationType);
		BoolPopulation.mutateKnapsack();

		BoolPopulation.population.clear();
		BoolPopulation.m_size = 0;
		BoolPopulation.checkSurvival(maxAge);					// elites survive & old individuals are eliminated

		while(BoolPopulation.m_size != BoolPopulation.defaultMaxSize)
		BoolPopulation.knapsackSurvivalSelection(tournamentSize);	// select survivors from temporary population


		m_generation++;
		cout << "Generation: " << m_generation << " " << endl;
		//intPopulation.evaluateMeanAge();
		BoolPopulation.find_mostfit();
		cout << "Most Fit: " << BoolPopulation.give_mostfit()<< " " ;
		BoolPopulation.bestInd.printWeight();
	}


		cout << endl << "Most fit individual has a fitness of: " << BoolPopulation.m_most_fit << endl;

		cout << "Genotype of the current most fit individual:" << endl;
		BoolPopulation.bestInd.show_genotype();
		BoolPopulation.bestInd.printWeight();	

		BoolPopulation.population.clear();
		BoolPopulation.m_size = 0;

}

/*
void Evolution::AckleyLoop(int pop_size, int length, int tournamentSize, int maxGeneration, double mutationRate, double noiseFactor, double elitismRate, int maxAge)
{
		Population<RealIndividual> RealPopulation;
		RealPopulation.set_probabilities(mutationRate, noiseFactor);
		while(m_generation != maxGeneration)
		{
			RealPopulation.temp_pop.clear(); 

			for(int i =0; i<RealPopulation.m_size;i++)
				RealPopulation.population[i].isElite = false;	// select elites
			RealPopulation.elite_selection(elitismRate);
			
			while (RealPopulation.m_size != 0) // will go through all the population select parents
				RealPopulation.parent_selection();

			RealPopulation.AckleyCrossover();		// crossover
						
			
			//!RealPopulation;		// mutation

			// select survivals
			RealPopulation.population.clear();
			RealPopulation.m_size = 0;

			for(size_t i =0;i<RealPopulation.temp_pop.size();i++)
			{
				if(RealPopulation.temp_pop[i].age == maxAge)
				{
					RealPopulation.temp_pop.erase(RealPopulation.temp_pop.begin() + i);				// deletes element if max age is reached
					i--;
				}
			}
	
			for(size_t i=0;i<RealPopulation.temp_pop.size();i++)
			{
				if (RealPopulation.temp_pop[i].isElite == true)
				{
					RealPopulation.temp_pop[i].age++;
					RealPopulation.population.push_back(RealPopulation.temp_pop[i]);					// Elites get a free pass
					RealPopulation.temp_pop.erase(RealPopulation.temp_pop.begin() + i);
					i--;
					RealPopulation.m_size++;
				}
			}


			while (RealPopulation.m_size != RealPopulation.defaultMaxSize)
				RealPopulation.survival_selection(tournamentSize);

			m_generation++;
			cout << "Generation: " << m_generation << " Mean Age : " ;			// display details of the generation
			RealPopulation.evaluateMeanAge();
			RealPopulation.evaluateMeanFitness();
			RealPopulation.find_mostfit();
			double epsilon = 0.00000001;
			if (RealPopulation.m_most_fit - 0.0 < epsilon)								// check for solution
			{
			cout << "SOLUTION FOUND" << endl;
			cout << endl << "Most fit individual has a fitness of: " << RealPopulation.m_most_fit << endl;

			cout << "Genotype of the current most fit individual:" << endl;
			RealPopulation.bestInd.show_genotype();
			break;
			}
		}
		cout << "SOLUTION NOT FOUND!" << endl;
		cout << endl << "Most fit individual has a fitness of: " << RealPopulation.m_most_fit << endl;

		cout << "Genotype of the current most fit individual:" << endl;
		RealPopulation.bestInd.show_genotype();
}
*/


/*
void Evolution::loop(Population& object, int populationSize, int tournamentSize, int maxGeneration, double mutationRate, double noiseFactor, double elitismRate, int maxAge)
{

		object.set_probabilities(mutationRate, noiseFactor);
		while(m_generation != maxGeneration)
		{
			object.temp_pop.clear(); 

			for(int i =0; i<object.m_size;i++)
				object.population[i].isElite = false;	// select elites
			object.elite_selection(elitismRate);
			
			while (object.m_size != 0) // will go through all the population select parents
				object.parent_selection();

			object.RealCrossover();		// crossover
						
			
			!object;		// mutation

			// select survivals
			object.population.clear();
			object.m_size = 0;

			for(size_t i =0;i<object.temp_pop.size();i++)
			{
				if(object.temp_pop[i].age == maxAge)
				{
					object.temp_pop.erase(object.temp_pop.begin() + i);				// deletes element if max age is reached
					i--;
				}
			}
	
			for(size_t i=0;i<object.temp_pop.size();i++)
			{
				if (object.temp_pop[i].isElite == true)
				{
					object.temp_pop[i].age++;
					object.population.push_back(object.temp_pop[i]);					// Elites get a free pass
					object.temp_pop.erase(object.temp_pop.begin() + i);
					i--;
					object.m_size++;
				}
			}


			while (object.m_size != populationSize)
				object.survival_selection(tournamentSize);

			m_generation++;
			cout << "Generation: " << m_generation << " Mean Age : " ;			// display details of the generation
			object.evaluateMeanAge();
			object.evaluateMeanFitness();
			object.find_mostfit();

			if (object.m_most_fit - 0.0 < epsilon)								// check for solution
			{
			cout << "SOLUTION FOUND" << endl;
			cout << endl << "Most fit individual has a fitness of: " << object.m_most_fit << endl;

			cout << "Genotype of the current most fit individual:" << endl;
			object.bestInd.show_genotype();
			break;
			}
		}
		cout << "SOLUTION NOT FOUND!" << endl;
		cout << endl << "Most fit individual has a fitness of: " << object.m_most_fit << endl;

		cout << "Genotype of the current most fit individual:" << endl;
		object.bestInd.show_genotype();
}



void Evolution::saveFitness(Population& object, int pop_size, int length, int tournamentSize, int maxGeneration, double mutationRate, double noiseFactor, double elitismRate, int maxAge)
{

    ofstream outfile("saved_fitness.csv");
	
	outfile << "Population size: " << pop_size << endl;
	outfile << "Individual size: " << length << endl;
	outfile << "Tournament size: " << tournamentSize << endl;
	outfile << "Max generations: " << maxGeneration << endl;
	outfile << "Mutation rate: " << mutationRate << endl;
	outfile << "Noise factor: " << noiseFactor << endl;
	outfile << "Elitism rate: " << elitismRate << endl;
	outfile << "Maximum age: " << maxAge << endl << endl;
    outfile << "Generation,Best Fitness,Mean Fitness" << endl;
	
    for(int i=0;i<m_generation;i++)
    {
		outfile << i+1 << "," << object.most_fit[i] << "," << object.mostFitMean[i] << endl;
    }

    outfile.close();
}


*/