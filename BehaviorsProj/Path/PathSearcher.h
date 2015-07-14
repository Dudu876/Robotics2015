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
#include "math.h"
#include <queue>

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
	double heuristicCostEstimate(Point point1, Point point2);
	int getLowestValueFrom(vector<Point> vector, double** scores);
	vector<Point> reconstructPath(Point** came_from, Point goalPoint);
	queue<Point> getPointNeighbors(Point point);
};

#endif /* PATHSEARCHER_H_ */
