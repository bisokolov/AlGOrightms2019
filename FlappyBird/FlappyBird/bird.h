#ifndef  BIRD_GUARD_H
#define BIRD_GUARD_H
#include "flappy.h"

class Bird {
public:
	Bird(const Point2d & startingPosition);
	bool isAlive(const LevelDescription & level);
	void nextPosition(bool hasJumped);


private:
	Point2d position;
};



#endif // ! BIRD_GUARD_H

