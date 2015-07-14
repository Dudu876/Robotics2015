/*
 * Map.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <algorithm>
#include <math.h>
#include "lodepng.h"
#include "../ConfigurationManager.h"
#include "Grid.h"
#include "../Utilities/Global.h"

class Map {
private:
	Grid _grid;
	string _filename;


public:
	Map();
	void loadMap();
	virtual ~Map();

	Grid getGrid();
};

#endif /* MAP_H_ */
