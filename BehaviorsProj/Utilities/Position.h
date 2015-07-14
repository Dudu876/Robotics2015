/*
 * Position.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
private:
	double _x;
	double _y;
	double _yaw;
public:
	Position();
	Position(double x, double y, double yaw);
	virtual ~Position();

	double getX();
	double getY();
	double getYaw();
	void setX(double x);
	void setY(double y);
	void setYaw(double yaw);
};

#endif /* POSITION_H_ */
