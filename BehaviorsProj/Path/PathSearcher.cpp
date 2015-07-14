/*
 * PathSearcher.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "PathSearcher.h"

PathSearcher::PathSearcher(Grid grid) {
	this->_grid = grid;

	// Init navigation members
	this->_last_Point = 0;
	this->_last_Direction = MOVE_FORWARD;
}

PathSearcher::~PathSearcher() {
	// TODO Auto-generated destructor stub
}

// A* implementation
vector<Point> PathSearcher::searchPath(Point startPoint, Point goalPoint) {

	// The set of tentative nodes to be evaluated, initially containing the start node
	vector<Point> open_set;
	open_set.push_back(startPoint);

	// The set of nodes already evaluated.
	vector<Point> closed_set;

	// The map of navigated nodes.
	Point* came_from[this->_grid.getRows()];

	// Init the navigated nodes
	for (int i = 0; i < this->_grid.getRows(); i++) {
		came_from[i] = new Point[this->_grid.getCols()];
	}

	// Insert the startPoint
	came_from[(int) startPoint.getRow()][(int) startPoint.getCol()] =
			startPoint;

	// Cost from start along best known path.
	//g_score(n) is the known cost of getting from the initial node(start) to n
	double* g_score[this->_grid.getRows()];

	// Init g score
	for (int i = 0; i < this->_grid.getRows(); i++) {
		g_score[i] = new double[this->_grid.getCols()];
	}

	// Sets the g score of start point
	g_score[startPoint.getRow()][startPoint.getCol()] = 0;

	// Estimated total cost from start to goal through y.
	//f_score(n) is sum of the known cost + heuristic cost of getting from the initial node(start) to n
	double* f_score[this->_grid.getRows()];

	// Init f score
	for (int i = 0; i < this->_grid.getRows(); i++) {
		f_score[i] = new double[this->_grid.getCols()];
	}

	// Sets the f score of start point
	f_score[startPoint.getRow()][startPoint.getCol()] =
			g_score[startPoint.getRow()][startPoint.getCol()]
					+ heuristicCostEstimate(startPoint, goalPoint);

	// Creating the path holder
	vector<Point> path;

	// Run until not more tentative nodes to be evaluated
	while (open_set.empty() == false) {
		// Get the index of the node in open_set having the lowest f_score[] value
		int lowestValueIndex = getLowestValueFrom(open_set, f_score);
		Point currentPoint = open_set[lowestValueIndex];

		// Check if the current point is the goal point
		if (currentPoint.isEqual(goalPoint)) {
			path = reconstructPath(came_from, goalPoint);
			break;
		}

		// Pop out the node that has the lowest score
		open_set.erase(open_set.begin() + lowestValueIndex);

		// Add the current point to the end of the vector
		closed_set.push_back(currentPoint);

		// Get neighbors of point
		queue<Point> neighbors = getPointNeighbors(currentPoint);

	}

}

// Calc the geometric distance between two points
double PathSearcher::heuristicCostEstimate(Point point1, Point point2) {
	double deltaX = point1.getCol() - point2.getCol();
	double deltaY = point1.getRow() - point2.getRow();

	return (sqrt(pow(deltaX, 2.0) + pow(deltaY, 2.0)));
}

// Return the index of the node in vector having the lowest score[] value
int PathSearcher::getLowestValueFrom(vector<Point> vector, double** scores) {
	int bestIndex = 0;
	Point lowest = vector[bestIndex];

	// Run over the vector of nodes
	for (unsigned int index = 1; index < vector.size(); index++) {
		Point temp = vector[index];
		if (scores[lowest.getRow()][lowest.getCol()]
				> scores[temp.getRow()][temp.getCol()]) {
			lowest = temp;
			bestIndex = index;
		}
	}

	return bestIndex;
}

vector<Point> PathSearcher::reconstructPath(Point** came_from,
		Point goalPoint) {
	vector<Point> path;
	vector<Point> fixedPath;

	Point current = goalPoint;
	Point pCamefrom = came_from[current.getRow()][current.getCol()];

	// Push the goal point to the path
	path.push_back(current);

	// Run until we reached the start
	while (!current.isEqual(pCamefrom)) {
		path.push_back(pCamefrom);
		current = pCamefrom;
		pCamefrom = came_from[current.getRow()][current.getCol()];
	}

	// Reverse the path
	for (int i = path.size() - 1; i >= 0; i--) {
		fixedPath.push_back(path[i]);
	}

	return fixedPath;
}

// Check point's neighbors
queue<Point> PathSearcher::getPointNeighbors(Point point)
{
	queue<Point> q_neighbors;
	int row = point.getRow();
	int col = point.getCol();

	// TOP BOTTOM LEFT RIGHT check

	// Check if we dont cross the TOP edge
	if (row - 1 > 0)
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row - 1, col) == FREE)
		{
			q_neighbors.push(Point(row - 1,col));
		}
	}

	// Check if we dont cross the BOTTOM edge
	if (row + 1 < this->_grid.getRows())
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row + 1, col) == FREE)
		{
			q_neighbors.push(Point(row + 1,col));
		}
	}

	// Check if we dont cross the LEFT edge
	if (col - 1 > 0)
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row, col - 1) == FREE)
		{
			q_neighbors.push(Point(row,col - 1));
		}
	}

	// Check if we dont cross the RIGHT edge
	if (col + 1 < this->_grid.getCols())
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row, col + 1) == FREE)
		{
			q_neighbors.push(Point(row,col + 1));
		}
	}

	// DIAGONAL check

	// Check if we dont cross the TOP LEFT edge
	if ((row - 1 > 0) && (col - 1 > 0))
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row - 1, col - 1) == FREE)
		{
			q_neighbors.push(Point(row - 1,col - 1));
		}
	}

	// Check if we dont cross the TOP RIGHT edge
	if ((row - 1 > 0) && (col + 1 < this->_grid.getCols()))
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row - 1, col - 1) == FREE)
		{
			q_neighbors.push(Point(row - 1,col - 1));
		}
	}
	// Check if we dont cross the BOTTOM LEFT edge
	if ((row + 1 < this->_grid.getRows()) && (col - 1 > 0))
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row - 1, col - 1) == FREE)
		{
			q_neighbors.push(Point(row - 1,col - 1));
		}
	}

	// Check if we dont cross the BOTTOM RIGHT edge
	if ((row + 1 < this->_grid.getRows()) && (col + 1 < this->_grid.getCols()))
	{
		// Check if the cell is free (empty), if it is, add it to neighbors
		if (this->_grid.getCellValue(row - 1, col - 1) == FREE)
		{
			q_neighbors.push(Point(row - 1,col - 1));
		}
	}

	return q_neighbors;
}
