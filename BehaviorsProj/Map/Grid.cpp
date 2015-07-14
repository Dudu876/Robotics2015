/*
 * Grid.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: colman
 */

#include "Grid.h"

Grid::Grid() {
	// TODO Auto-generated constructor stub

}



Grid::Grid(int rows,int cols,double resolution,unsigned height, unsigned width)
{
	this->_height = height;
	this->_width = width;
	this->_gridRows = rows;
	this->_gridCols = cols;
	this->_gridResolution = resolution;

	this->_grid = new int*[rows];

	for(int i = 0; i < rows; ++i)
	{
		this->_grid[i] = new int[cols];
	}

	for (int i = 0; i < this->_gridRows ; i++)
	{
		for (int j = 0; j < this->_gridCols ; j++)
		{
			_grid[i][j] = FREE;
		}
	}
}
int Grid::getRows()
{
	return this->_gridRows;
}

int Grid::getCols()
{
	return this->_gridCols;
}

void Grid::setCellValue(int row, int col, int value) {
	this->_grid[row][col] = value;
}

int Grid::getCellValue(int row, int col) {
	return this->_grid[row][col];
}

void Grid::initGridByMatrix(int** grid) {
	//init _grid by given grid
	for (int row = 0; row < this->_gridRows ; row++)
	{
		for (int col = 0; col < this->_gridCols ; col++)
		{
			setCellValue(row, col, grid[row][col]);
		}
	}
}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}



