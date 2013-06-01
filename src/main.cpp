// Olivier Nguyen
// Student ID : 6605583


#include "Evolution.h"

const double elitismRate = 0.05;
const int tournamentSize = 4;
const int maxAge = 50;

const int maxGeneration = 50;

int main()
{
   srand((unsigned int)time(NULL));	
	 
   Evolution evolution;
   
   evolution.BooleanLoop(50,elitismRate,maxAge,0, tournamentSize);				
   evolution.BooleanLoop(50,elitismRate,maxAge,1, tournamentSize);
   evolution.IntegerLoop(maxGeneration,elitismRate,maxAge,0, tournamentSize);	// a higher number of generations can achieve a better fitness
   evolution.IntegerLoop(maxGeneration,elitismRate,maxAge,1, tournamentSize);	 


   system("pause");
}


