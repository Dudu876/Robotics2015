/*
 * WayPointsManager.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "WayPointsManager.h"

WayPointsManager::WayPointsManager() {
	// TODO Auto-generated constructor stub

}


void WayPointsManager::addWayPoint(Position waypoint)
{
	WayPointsManager::_wayPoints.push_back(waypoint);
}


WayPointsManager::~WayPointsManager() {
	// TODO Auto-generated destructor stub
}

