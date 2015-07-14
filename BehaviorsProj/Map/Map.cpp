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
	//the raw pixels
	vector<unsigned char> image;

	unsigned width, height;

	// Geting the file path
	this->_filename = ConfigurationManager::getMapLocation();

	// Decoding the image from the path we got earlier
	unsigned error = lodepng::decode(image, width, height, this->_filename);

	// If there's an error loading the image, display it
	if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;

	int map[height][width];

	// Running over the image and transform it to matrix
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				map[y][x] = FREE;
			else
				map[y][x] = BLOCK;
		}
	}

	// Getting the map resolution
	double mapResolution = ConfigurationManager::getMapResolution();
	// Getting the grid resolution
	int gridResolution = ConfigurationManager::getGridResolution();

	// Getting the robot size x,y
	int robot_size_x, robot_size_y;
	ConfigurationManager::getRobotSize(robot_size_x, robot_size_y);

	// creating the the puff size
	int puffSize = ceil(max(robot_size_x,robot_size_y)/mapResolution/2);

	// Creating large map for puff the original map
	int largeMap[height][width];

	/*// Running over the matrix map and puffy it
	for (y = 1; y < height-1; y++){
		for (x = 1; x < width-1; x++) {
			if (map[y][x] == 1) {
				largeMap[y-1][x-1] = 1;
				largeMap[y-1][x] = 1;
				largeMap[y-1][x+1] = 1;
				largeMap[y][x-1] = 1;
				largeMap[y][x+1] = 1;
				largeMap[y+1][x-1] = 1;
				largeMap[y+1][x] = 1;
				largeMap[y+1][x+1] = 1;
			}
		}
	}*/

	// Running over the matrix map and puffy it
	//TODO: ask dudu why y and x start from 1 and not from 0
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++) {
			// Check if there is black cell
			if (map[y][x] == 1) {

				// Run over the cell to puff
				for(int pY=y-puffSize/2;pY< y+puffSize/2;pY++){
					// Check if we didnt exceed the matrix
					if(pY>=0 && pY<height){
						for(int pX=x-puffSize/2;pX< x+puffSize/2;pX++){
							// Check if we didnt exceed the matrix
							if(pX>=0 && pX<width){
								largeMap[pY][pX]=BLOCK;
							}
						}
					}
				}
			}
			else{
				largeMap[y][x]=FREE;
			}
		}
	}


	//printing the large matrix to file to check it
	FILE* f = fopen("mapPuffy.txt", "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fprintf(f, "%d", largeMap[y][x]);
			//cout << map[y][x];
		}
		fprintf(f, "\n");
		//cout << endl;
	}
	fclose(f);

	int grid_height = (height*mapResolution)/gridResolution;
	int grid_width = (width*mapResolution)/gridResolution;

	int** grid = new int*[grid_height];

	// init grid
	for(int i = 0; i < grid_height; ++i)
	{
		grid[i] = new int[grid_width];
	}

	//int grid[grid_height][grid_width];

	int scaleLargeToGrid = gridResolution/mapResolution;

	// Running over the puff map and transform it to grid
	for (int y = 0; y < grid_height; y++){
		for (int x = 0; x < grid_width; x++) {
			bool isBlack=false;

			// Run over the cell to check if there is any black cell
			for(int pY=y*scaleLargeToGrid;pY< y*scaleLargeToGrid+scaleLargeToGrid;pY++){
				// Check if we didnt exceed the matrix
				if(pY>=0 && pY<height && isBlack==false){
					for(int pX=x*scaleLargeToGrid;pX< x*scaleLargeToGrid+scaleLargeToGrid;pX++){
						// Check if we didnt exceed the matrix
						if(pX>=0 && pX<width){
							if(largeMap[pY][pX] == BLOCK)
							{
								isBlack = true;
								break;
							}
						}
					}
				}
			}

			// if one of the 4 (scaleLargeToGrid) is black, we paint the grid cell to black
			if (isBlack){
				grid[y][x] = BLOCK;
			}
			else{
				grid[y][x] = FREE;
			}
		}
	}

	this->_grid = Grid(grid_height,grid_width,gridResolution,height,width);
	this->_grid.initGridByMatrix(grid);


	//printing the grid to file to check it
	FILE* fgrid = fopen("grid.txt", "w");
	if (fgrid == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	for (int y = 0; y < grid_height; y++) {
		for (int x = 0; x < grid_width; x++) {
			fprintf(fgrid, "%d", grid[y][x]);
			//cout << map[y][x];
		}
		fprintf(fgrid, "\n");
		//cout << endl;
	}
	fclose(fgrid);
}

Grid Map::getGrid()
{
	return this->_grid;
}

void Map::loadMap() {

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

