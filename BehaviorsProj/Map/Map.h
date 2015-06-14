/*
 * Map.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "lodepng.h"
#include "../ConfigurationManager.h"

class Map {
public:
	Map();
	void loadMap();
	virtual ~Map();
};

#endif /* MAP_H_ */
