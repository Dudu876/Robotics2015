/*
 * PathSearcher.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "PathSearcher.h"

PathSearcher::PathSearcher(Grid grid) {
	this->_grid = grid;

	// Init navigation members
	this->_last_Point = 0;
	this->_last_Direction = MOVE_FORWARD;
}

PathSearcher::~PathSearcher() {
	// TODO Auto-generated destructor stub
}

vector<Point> PathSearcher::searchPath(Point startPoint, Point goalPoint) {

}
