#include "Individual.h"
#include "RealIndividual.h"
#define pi 3.1416
//mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
default_random_engine generator1;
double maximum = 32.768;

RealIndividual::RealIndividual()
{
	m_length = defaultMaxSize;
	rand();
	//uniform_real_distribution<double> dist(-32.768, 32.768);
	for(int i = 0; i < defaultMaxSize; i++)
            m_genotype.push_back(68.536*rand()/(RAND_MAX) - 32.768);
	evaluate_fitness();
	age = 0;
}


RealIndividual::RealIndividual(int length)
{
	m_length = length;
	uniform_real_distribution<double> dist(-32.768, 32.768);
	for(int i = 0; i < length; i++)
            m_genotype.push_back(68.536*rand()/(RAND_MAX) - 32.768);
	evaluate_fitness();
		age = 0;

}

void RealIndividual::evaluate_fitness() // Evaluates the fitness of the individual
{
        double sum1 = 0;
        double sum2 = 0;
        double f;

        for(int i=0;i<m_length;i++)
            sum1 = sum1 +  m_genotype[i] * m_genotype[i];

        for(int i=0;i<m_length;i++)
            sum2 = sum2 + cos(2*(pi)*m_genotype[i]);

         f= -20*exp(-0.2*(sqrt((1/(double)m_length)*sum1)))-exp((1/(double)m_length)*sum2)+20+exp(1);
         m_fitness = f;
}

RealIndividual& operator!(RealIndividual& target)
{
		double stdeviation;
		double mean;
        double random;
		double Pm = 0.2;
		double NoiseFactor = 0.3;
		for(int i=0;i<target.m_length;i++) // will go through every element
            {
				random = rand() % 100 + 1;
				random = random / 100.0;
				if (random <= Pm) // 10% per element for mutation
				{
					stdeviation = fabs(target.m_genotype[i] * NoiseFactor); // STANDARD DEVIATION WILL BE A % OF THE INITIAL SOLUTION
					mean = target.m_genotype[i];

					normal_distribution<double> distribution(mean,stdeviation); // will produce noise/small variation to the element of the individual
						double number = distribution(generator1);
						target.m_genotype[i] = number;
						while (fabs(target.m_genotype[i]) > maximum)
						{
							number = distribution(generator1);
							target.m_genotype[i] = number;
						}
						
				}
			}
		target.evaluate_fitness();
		return target;
}

void RealIndividual::mutateA()		// Select 2 random points, shuffle in between
{
	int pointA = rand() % m_length;
	int pointB = rand() % m_length;
	while(pointA == pointB)
		pointB = rand () % m_length;
	cout << pointA << " " << pointB << endl;
	if (pointA < pointB)
		random_shuffle(m_genotype.begin() + pointA, m_genotype.begin() + pointB);
	else
		random_shuffle(m_genotype.begin() + pointB, m_genotype.begin() + pointA);

}
