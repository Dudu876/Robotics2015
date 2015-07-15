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

	//Test the A* path
	for (int i = 0; i < path.size(); i++) {
		grid.setCellValue(path[i].getRow(), path[i].getCol(), 8);
	}

	//printing the grid to file to check it
	FILE* fgrid = fopen("grid.txt", "w");
	if (fgrid == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	for (int y = 0; y < grid.getRows(); y++) {
		for (int x = 0; x < grid.getCols(); x++) {
			if(grid.getCellValue(y,x) == 8)
				fprintf(fgrid, "*");
			else
				fprintf(fgrid, "%d", grid.getCellValue(y,x));
			//cout << map[y][x];
		}
		fprintf(fgrid, "\n");
		//cout << endl;
	}
	fclose(fgrid);

	Robot robot("localhost", 6665);
	return 0;
//	static ConfigurationManager conf;
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();
}

