#include <vector>
#include "flappy.h"
#include "genetic.h"






std::vector<bool> getAgentDecisions(const LevelDescription & level) {
	std::vector<bool> decision = GeneticAlgorithm(level);
	return decision;
}