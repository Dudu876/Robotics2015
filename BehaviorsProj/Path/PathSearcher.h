/*
 * PathSearcher.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef PATHSEARCHER_H_
#define PATHSEARCHER_H_
#include "../Map/Grid.h"
#include <vector>
#include "../Utilities/Point.h"
using namespace std;

class PathSearcher {
private:
	// data members for navigation
	unsigned _last_Point;
	int _last_Direction;

	// Grid of the surface
	Grid _grid;
public:
	PathSearcher(Grid grid);
	virtual ~PathSearcher();

	vector<Point> searchPath(Point startPoint, Point goalPoint);
};

#endif /* PATHSEARCHER_H_ */
