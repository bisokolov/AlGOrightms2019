#include <vector>
#include "flappy.h"
#include "genetic.h"
#include "agent.h"
#include "agentPopulation.h"




std::vector<bool> GeneticAlgorithm(const LevelDescription& level) {
	int population = 100;
	AgentPopulation algorithmPopulation(population,level);
	algorithmPopulation.ComputePopulationFitness(level);

	//computing the distribution of the population
	int proportionOfParents = 35; // 35 %
	int numberOfParents = (population * proportionOfParents) / 100;
	int proportionOfChildren = 65; //65 %
	int numberOfChildren = (population * proportionOfChildren) / 100;
	int numberOfMutations = population - numberOfParents - numberOfChildren;
	
	while (!(levelPassed(algorithmPopulation,level))) {

		AgentPopulation parents = algorithmPopulation.ParentSelection(numberOfParents,level);
		AgentPopulation crossovers = algorithmPopulation.Crossover(parents, numberOfChildren, level);
		AgentPopulation mutations = algorithmPopulation.Mutation(parents, crossovers,numberOfMutations,level);
		algorithmPopulation = algorithmPopulation.CreateNextGeneration(parents, crossovers, mutations,population,level);
		algorithmPopulation.ComputePopulationFitness(level);

	}

	Agent solution = algorithmPopulation.getBestIndividual();
	return solution.decompress();

}

bool levelPassed(const AgentPopulation & pop,const LevelDescription & level) {
	for (int i = 0;i < pop.populationSize;++i) {
		if (pop.populationOfAgents[i].levelPassed(level))
			return true;
	}
	return false;
}