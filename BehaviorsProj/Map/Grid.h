/*
 * Grid.h
 *
 *  Created on: Jul 13, 2015
 *      Author: colman
 */

#ifndef GRID_H_
#define GRID_H_
#include "../Utilities/Global.h"

class Grid {

	int** _grid;
	int _gridRows,_gridCols;
	double _gridResolution;
	double _cellSizeInMap;
	unsigned _height;
	unsigned _width;

public:
	Grid();
	Grid(int rows, int cols, double resolution,unsigned height, unsigned width);
	virtual ~Grid();
	void initGridByMatrix(int** grid);
	int getRows();
	int getCols();
	void setCellValue(int row, int col, int value);
	int getCellValue(int row, int col);
};

#endif /* GRID_H_ */