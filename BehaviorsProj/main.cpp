#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map/Map.h"
#include "Map/Grid.h"
#include "Path/PathSearcher.h"

using namespace PlayerCc;

int main() {
	static ConfigurationManager conf;
	Map map = Map();
	Grid grid = map.getGrid();

	PathSearcher* ps = new PathSearcher(grid);

	vector<Point> path = ps->searchPath(grid.getStartPoint(),
			grid.getGoalPoint());

	Robot robot("localhost", 6665);
	return 0;
//	static ConfigurationManager conf;
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();
}

