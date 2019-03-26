#ifndef GUARD_AGENT_H
#define GUARD_AGENT_H
#include <vector>
#include "flappy.h"


class Agent {
public: 
	Agent();	                 
	Agent(int );// generate agent with random decision
	Agent(const Agent &, const Agent &,int); // this function does the crossover
	void computeAgentFitness(const LevelDescription & level);
	void mutateAgent();
	bool levelPassed(const LevelDescription & level) const ;
	Agent  createIndividual();
	std::vector<bool> decompress();
	int getFitnessScore() const;

private:
	std::vector<bool> agentDecisions;
	int fitnessScore;
};

bool compareAgents(const Agent& agentOne, const Agent& agentTwo);


#endif // ! GUARD_AGENT_H

