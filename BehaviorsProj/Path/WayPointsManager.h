/*
 * WayPointsManager.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_
#include <vector>
#include "../Utilities/Global.h"
#include "../Utilities/Position.h"

class WayPointsManager {
private:
	vector<Position> _wayPoints;
public:
	WayPointsManager();
	virtual ~WayPointsManager();
	vector<Position> getWayPoints();
	void addWayPoint(Position waypoint);
};

#endif /* WAYPOINTSMANAGER_H_ */
