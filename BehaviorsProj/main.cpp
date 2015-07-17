#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map/Map.h"
#include "Map/Grid.h"
#include "Path/PathSearcher.h"
#include "Manager.h"

using namespace PlayerCc;

int main() {
	static ConfigurationManager conf;
	Map map = Map();
	Grid grid = map.getGrid();

	//TODO: add start location & fix
	Robot robot("localhost", 6665);

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

	// sets path in grid matrix
	for (int i = 0; i < path.size(); i++)
	{
		grid.setCellValue(path[i].getRow(),path[i].getCol(),PATH_CELL);
	}

	grid.setCellValue(grid.getStartPoint().getRow(),grid.getStartPoint().getCol(),START_CELL);
	grid.setCellValue(grid.getGoalPoint().getRow(),grid.getGoalPoint().getCol(),GOAL_CELL);

	//TODO: bonus: grid.printMeSimanKria();

	vector<Position> waypoint = ps->getWayPoints();

	//TODO: what the fuck is that?
	// Print to file (image type) the grid with the way point on it
	//grid.setColorizeWaypoints(map.getPuffedMap(),map.getWidth(),map.getHeight(), ps->getRealPath());

	//TODO:: delete this code
	// print waypoint for debug
	for (unsigned i = 0; i < waypoint.size(); i++)
	{
		cout << "( " << waypoint[i].getRow()  << " , " << waypoint[i].getCol() << " )" << endl;
	};


	robot.Read();
	std::cout<< "test"<<endl;
	cout<< robot.getX()<<endl;
	cout<< robot.getY()<<endl;
	cout<< robot.getYaw()<<endl;

	Manager mgr = Manager(&robot, ps->getWayPoints());
	mgr.run();

//	static ConfigurationManager conf;
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();


	//TODO: remove this print (for debug only)
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


	return 0;
}
