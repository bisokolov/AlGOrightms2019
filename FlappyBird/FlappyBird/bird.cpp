#include "bird.h"
#include "flappy.h"


Bird::Bird(const Point2d & startingPosition) {
	this->position = startingPosition;
}

bool Bird::isAlive(const LevelDescription & level) {

	if (this->position.y == 0 || this->position.y == level.height) {
		return false;
	}
	if (this->position.x > level.length) {
		return false;
	}
	for (int i = 0;i < level.pylons.size();++i) {
		if ((this->position.x >= (level.pylons[i].center.x - level.pylons[i].width / 2))
			  && (this->position.x <= (level.pylons[i].center.x + level.pylons[i].width / 2))) {
			if (this->position.y <= (level.pylons[i].center.y - level.pylons[i].gapHeight / 2)
				|| this->position.y >= (level.pylons[i].center.y + level.pylons[i].gapHeight / 2))
			{
				return false;
			}

		}
	}

	return true;
}

void Bird::nextPosition(bool hasJumped) {
	
	if (hasJumped) {
		this->position.x = this->position.x + HORIZONTAL_VELOCITY;
		this->position.y = this->position.y + JUMP_ACCELERATION;
	}
	else {
		this->position.x = this->position.x + HORIZONTAL_VELOCITY;
		this->position.y = this->position.y - VERTICAL_ACCELERATION;
	}
} 