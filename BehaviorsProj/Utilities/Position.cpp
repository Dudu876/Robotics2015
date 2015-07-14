/*
 * Position.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "Position.h"

Position::Position()
{
	this->_x = 0;
	this->_y = 0;
	this->_yaw = 0;
}

Position::Position(double x, double y, double yaw)
{
	this->_x = x;
	this->_y = y;
	this->_yaw = yaw;
}

Position::~Position()
{
}

double Position::getX()
{
	return this->_x;
}

double Position::getY()
{
	return this->_y;
}

double Position::getYaw()
{
	return this->_yaw;
}

void Position::setX(double x)
{
	this->_x = x;
}

void Position::setY(double y)
{
	this->_y = y;
}
void Position::setYaw(double yaw)
{
	this->_yaw = yaw;
}
