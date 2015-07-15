/*
 * Point.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
private:
	int _col;
	int _row;
public:
	Point();
	Point(int col, int row);
	void setCol(int col);
	void setRow(int row);
	int getCol();
	int getRow();
	bool isEqual(Point point);
	virtual ~Point();
};

#endif /* POINT_H_ */
