/*
 * PathSearcher.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef PATHSEARCHER_H_
#define PATHSEARCHER_H_
#include "../Map/Grid.h"

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
};

#endif /* PATHSEARCHER_H_ */
