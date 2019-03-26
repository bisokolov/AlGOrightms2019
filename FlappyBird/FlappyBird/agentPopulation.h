#ifndef GUARD_AGENT_POPULATION_H
#define GUARD_AGENT_POPULATION_H
#include<vector>
#include "agent.h"
#include "flappy.h"



class AgentPopulation {
public:
	AgentPopulation(int pop,const LevelDescription & level);
	void copyPopulation(const AgentPopulation &, int);
	void ComputePopulationFitness(const LevelDescription & level);
	void addAgent(const Agent &);
	AgentPopulation  ParentSelection(int, const LevelDescription & level);  // proportion in numbers
	AgentPopulation  Crossover(const AgentPopulation & parents, int, const LevelDescription & level); //proportion in numbers
	AgentPopulation  Mutation(const AgentPopulation & parents, const AgentPopulation & crossovers, int, const LevelDescription & level); //proportion in numbers
	AgentPopulation  CreateNextGeneration(const AgentPopulation &, const AgentPopulation&, const AgentPopulation&, int, const LevelDescription & level);
	Agent & getBestIndividual();
	int getPopSize() const { return populationSize; }


	//private:  should be private
	std::vector<Agent> populationOfAgents;
	int populationSize;
};



#endif