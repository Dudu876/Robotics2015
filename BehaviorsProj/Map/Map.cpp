/*
 * Map.cpp
 *
 *  Created on: xun 12, 2015
 *      Author: colman
 */

#include <string>
#include <string.h>
#include "Map.h"

using namespace std;

Map::Map() {
	// TODO Auto-generated constructor stub

}

void Map::loadMap() {
	vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	const string filename = ConfigurationManager::getMapLocation();
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;

	int map[height][width];
	int x,y;

	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				map[y][x] = 0;
			else
				map[y][x] = 1;
		}

	int mapResolution = ConfigurationManager::getMapResolution();
	int gridResolution = ConfigurationManager::getGridResolution();
	int robot_x, robot_y;
	ConfigurationManager::getRobotSize(robot_x, robot_y);
	int robotSize = ceil(max(robot_x,robot_y)/mapResolution/2);

	for (y = 1; y < height-1; y++)
		for (x = 1; x < width-1; x++) {
			if (map[y][x] == 1) {
				map[y-1][x-1],map[y-1][x],map[y-1][x+1],
				map[y][x-1],map[y][x+1],
				map[y+1][x-1],map[y+1][x],map[y+1][x+1] = 2;
			}
		}
	for (y = 1; y < height-1; y++)
			for (x = 1; x < width-1; x++) {
				if (!map[y][x])
					map[y][x] = 1;
			}

	int new_height = (height*mapResolution)/gridResolution;
	int new_width = (width*mapResolution)/gridResolution;
	int grid[new_height][new_width];






	x=0;y=0;
	for (y=0;y<height;y++) {
		for (x=0;x<width;x++) {
			cout << map[y][x] << '|';
		}
		cout << endl;
	}

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

