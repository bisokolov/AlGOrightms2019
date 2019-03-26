#ifndef GUARD_GENETIC_H
#define GUARD_GENTIC_H

#include<vector>
#include "agentPopulation.h"


bool levelPassed(const AgentPopulation & pop,const LevelDescription& level);

std::vector<bool> GeneticAlgorithm(const LevelDescription& level);





#endif 

