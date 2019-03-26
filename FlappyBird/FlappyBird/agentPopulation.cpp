#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "agent.h"
#include "agentPopulation.h"
#include "flappy.h"



AgentPopulation::AgentPopulation(int pop,const LevelDescription & level) {

	this->populationSize = pop;
	this->populationOfAgents.reserve(this->populationSize);

	int numbOfDecisions = level.length / HORIZONTAL_VELOCITY;

	for (int i = 0;i < this->populationSize;++i) {
		Agent ag(numbOfDecisions);
		this->populationOfAgents.push_back(ag);
	}
}
void AgentPopulation::copyPopulation(const AgentPopulation & parents, int size) {
	this->populationSize = size;
	this->populationOfAgents.reserve(this->populationSize);
	for (int i = 0;i < this->populationSize;++i) {
		this->populationOfAgents[i] = parents.populationOfAgents[i];
	}

}

AgentPopulation  AgentPopulation::ParentSelection(int proportion,const LevelDescription & level) {  // proportion in numbers
	AgentPopulation parents(0,level);
	parents.copyPopulation(*this, proportion);
	return parents;
}

AgentPopulation  AgentPopulation::Crossover(const AgentPopulation & parents, int proportion, const LevelDescription & level) {
	AgentPopulation crossovers(0,level);
	crossovers.populationOfAgents.reserve(proportion);
	int i = 0;
	srand(time(NULL));
	while (i < proportion) {
		int crossoverPoint = rand() % (int)(level.length / HORIZONTAL_VELOCITY); 

		int j = rand() % parents.getPopSize();
		int k = rand() % parents.getPopSize();
		Agent childOne(parents.populationOfAgents[k], parents.populationOfAgents[j],crossoverPoint);
		Agent childTwo(parents.populationOfAgents[j], parents.populationOfAgents[k],crossoverPoint);
		crossovers.addAgent(childOne);
		crossovers.addAgent(childTwo);

		
		++i;
	}
	srand(1);
	return crossovers;
}

AgentPopulation  AgentPopulation::Mutation(const AgentPopulation & parents, const AgentPopulation & children, int proportion, const LevelDescription & level) {
	AgentPopulation mutations(0,level );
	mutations.populationOfAgents.reserve(proportion);
	int i = 0;
	srand(time(NULL));
	while (i < proportion / 2)
	{
		
		int i = rand() % parents.getPopSize();
		Agent ag = parents.populationOfAgents[i];
		ag.mutateAgent();
		mutations.addAgent(ag);
	}
	while (i < proportion)
	{
		
		int i = rand() % children.getPopSize();
		Agent ag = children.populationOfAgents[i];
		ag.mutateAgent();
		mutations.addAgent(ag);
	}
	srand(1);
	return mutations;
}

AgentPopulation  AgentPopulation::CreateNextGeneration(const AgentPopulation & parents, const AgentPopulation & children, const AgentPopulation & mutations, int population, const LevelDescription & level) {
	AgentPopulation nextGen(0, level);
	nextGen.populationOfAgents.resize(population);
	for (int i = 0;i < parents.populationSize;++i) {
		Agent ag = parents.populationOfAgents[i];
		nextGen.populationOfAgents.push_back(ag);
	}
	for (int i = 0;i < children.populationSize;++i) {
		Agent ag = children.populationOfAgents[i];
		nextGen.populationOfAgents.push_back(ag);
	}
	for (int i = 0;i < mutations.populationSize;++i) {
		Agent ag = mutations.populationOfAgents[i];
		nextGen.populationOfAgents.push_back(ag);
	}
	return nextGen;
}

void AgentPopulation::addAgent(const Agent & ag) {
	this->populationSize = this->populationSize + 1;
	this->populationOfAgents[this->populationSize] = ag;
}



void AgentPopulation::ComputePopulationFitness(const LevelDescription & level) {
	for (int i = 0;i < populationSize;++i) {
		populationOfAgents[i].computeAgentFitness(level);
	}
	//sort the individuals
	std::sort(this->populationOfAgents.begin(), this->populationOfAgents.end(), compareAgents);
}

Agent & AgentPopulation::getBestIndividual() {
	return this->populationOfAgents[0];
}