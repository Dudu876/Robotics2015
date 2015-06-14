#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map/Map.h"

using namespace PlayerCc;

int main()
{
	static ConfigurationManager conf;
	Map map;
	map.loadMap();
	Robot robot("localhost", 6665);
	return 0;
//	static ConfigurationManager conf;
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();
}




