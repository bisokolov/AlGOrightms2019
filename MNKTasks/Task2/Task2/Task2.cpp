#include <iostream>
#include <cstdlib>
#include <ctime>

struct Disk {
	float x, y;
	float radius;
};

struct Point {
	Point();
	float x, y;
	bool isInsideDisk(const Disk &d);
};
bool Point::isInsideDisk(const Disk & d) {

	return sqrt((this->x - d.x) * (this->x - d.x) + (this->y - d.y) * (this->y - d.y)) <= d.radius;

}

Point::Point() {
	srand(time(nullptr));
	float randomX = rand() / (double)(RAND_MAX);
	float randomY = rand() / (double)(RAND_MAX);
	this->x = randomX;
	this->y = randomY;

}
 
float coveredArea(Disk disks[5]) {
	int numberOfIterations = 1000;
	int pointsInsideADisk = 0;
	while (numberOfIterations>0) {
		--numberOfIterations;
		Point generated;
		bool isInside = false;
		for (int i = 0;i < 5;++i) {
			if (generated.isInsideDisk(disks[i])) {
				isInside = true;
			}	
		}

		if (isInside) {
			++pointsInsideADisk;
		}
		

	}
	return numberOfIterations / (float)pointsInsideADisk;
}

int main() {

}