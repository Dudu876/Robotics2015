/*
 * Map.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Map.h"

using namespace std;

Map::Map() {
	// TODO Auto-generated constructor stub

}

void Map::loadMap() {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	const string filename = ConfigurationManager::getMapLocation();
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;

	char grid[width][height];

	for (int i=0;i<width;i++) {
		for (int j=0;j<height;j++) {
			if(image[(i*4)+((j*width)*4)]) grid[i][j] = 'X';
			else grid[i][j] = 'O';
		}
	}

	for (int i=0;i<width;i++) {
		for (int j=0;j<height;j++) {
			cout << grid[i][j] << '|';
		}
		cout << endl;
	}

	cout << "What" << endl;

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

