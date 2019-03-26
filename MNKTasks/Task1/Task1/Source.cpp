#include <iostream>
#include <stack>

bool findPath(char ** maze, int width, int height, int x, int y) {
	struct Point {
		int x;
		int y;
		bool isWall;
	};
	 
	if (maze[x][y] == 'X') {
		return true;
	} 
	std::stack<Point> mazeStack;
	Point start = { x,y,false };
	
	mazeStack.push(start);

	while (!mazeStack.empty()) {
		Point p = mazeStack.top();
		mazeStack.pop();

		if (maze[p.x][p.y] == 'X') {
			return true;
			continue;
		}

		if (p.isWall == true) {
			p.isWall = false;
		}

		if (maze[p.x][p.y] == '#' || p.x < 0 || p.y < 0 || p.x > width , p.y > height) {
			continue;
		}

		maze[p.x][p.y] = '#';
		p.isWall = true;
		mazeStack.push(p);

		if (maze[p.x][p.y] == '-') {
			Point childOne = { x - 1,y,false };
			Point childTwo = { x + 1,y,false };
			mazeStack.push(childOne);
			mazeStack.push(childTwo);
		} 

		if (maze[p.x][p.y] == '|') {
			Point childThree = { x,y - 1,false };
			Point childFour = { x,y + 1,false };
			mazeStack.push(childThree);
			mazeStack.push(childFour);

		}

		if (maze[p.x][p.y] == '+') {
			Point childOne = { x - 1,y,false };
			Point childTwo = { x + 1,y,false };
			Point childThree = { x,y - 1,false };
			Point childFour = { x,y + 1,false };
			mazeStack.push(childOne);
			mazeStack.push(childTwo);
			mazeStack.push(childThree);
			mazeStack.push(childFour);
		}


	}




	return false;
}

int main() {


	return 0;
}