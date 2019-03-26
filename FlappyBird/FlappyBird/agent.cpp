#include <vector>
#include <cstdlib>
#include <ctime>
#include "flappy.h"
#include "agent.h"
#include "bird.h"

Agent::Agent() {
	this->fitnessScore = 0;
}

Agent::Agent(int numbOfDecisions) {
	this->agentDecisions.reserve(numbOfDecisions);
	srand(time(NULL));
	for (int i = 0;i < numbOfDecisions;++i) {
		bool decision = rand() % 2;
		this->agentDecisions.push_back(decision);
	}
	

}

Agent::Agent(const Agent & parentA, const Agent & parentB,int crossoverPoint) {
	int i = 0;
	this->agentDecisions.reserve(parentA.agentDecisions.size());
	while (i < parentA.agentDecisions.size()) {
		if (i < crossoverPoint) {
			this->agentDecisions[i] = parentA.agentDecisions[i];
		} else {
			this->agentDecisions[i] = parentB.agentDecisions[i];
		}

		++i;
	}
}

void Agent::computeAgentFitness(const LevelDescription & level) {	//fitness function
	int fitness = 0;
	Point2d center;;
	center.x = 0;
	center.y = level.height / 2;
	Bird agentBird(center);
	int i = 0;
	if (agentBird.isAlive(level)) {
		while (agentBird.isAlive(level)) {
			++fitness;
			agentBird.nextPosition(this->agentDecisions[i]);
			++i;
		}

	}
	this->fitnessScore = fitness;
}

void Agent::mutateAgent() {
	srand(time(NULL));
	int i = rand() % 2;
	if (i) {
		int j = rand() % this->agentDecisions.size();
		int k = rand() % this->agentDecisions.size();
		if (j != k) {
			if (this->agentDecisions[j] == true) {
				this->agentDecisions[j] = false;
			}
			else {
				this->agentDecisions[j] = true;
			}

			if (this->agentDecisions[k] == true) {
				this->agentDecisions[k] =  false;
			}
			else {
				this->agentDecisions[k] = true;
			}
			
		}
	}
    else {
		int j = rand() % this->agentDecisions.size();
		if (this->agentDecisions[j] == true) {
			this->agentDecisions[j] == false;
		}
		else {
			this->agentDecisions[j] == true;
		}
	}
}

bool Agent::levelPassed(const LevelDescription & level) const {
	if (this->fitnessScore == level.height / HORIZONTAL_VELOCITY) {
		return true;
	}
	return false;
}

Agent Agent::createIndividual() {
	Agent ag;
	return ag;
}

std::vector<bool> Agent::decompress() {
	return this->agentDecisions;
}


int Agent::getFitnessScore() const {
	return this->fitnessScore;

}

bool compareAgents(const Agent& agentOne, const Agent& agentTwo) {
	return agentOne.getFitnessScore() > agentTwo.getFitnessScore();
}