/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port) :
		_pc(ip, port), _pp(&_pc), _lp(&_pc) {
	// TODO Auto-generated constructor stub
	_lastX = _pp.GetXPos();
	_lastY = _pp.GetYPos();
	_lastYaw = _pp.GetYaw();
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::setSpeed(float linear, float angular) {
	_pp.SetSpeed(linear, angular);
}

void Robot::setXAndY(float x, float y) {
	_lastX = x;
	_lastY = y;
}


float Robot::getCol() {
	return _pp.GetXPos() * 40 + 275;
}

float Robot::getRow() {
	return _pp.GetYPos() * 40 * (-1) + 190;
}

float Robot::getX() {
	return _pp.GetXPos() * 40 + 275;
}

float Robot::getY() {
	return _pp.GetYPos() * 40 * (-1) + 190;
}

float Robot::getYaw() {
	return _pp.GetYaw();
}

float Robot::getRealX() {
	return _pp.GetXPos();
}

float Robot::getRealY() {
	return _pp.GetYPos();
}

float Robot::getRealYaw() {
	return _pp.GetYaw();
}

float* Robot::getLaserScan() {
	float *scan = new float[_lp.GetCount()];
	for (unsigned int i = 0; i < _lp.GetCount(); i++) {
		scan[i] = _lp[i];
	}
	return scan;
}

int Robot::deg_to_index(double deg) {
	return (deg + 120) / 0.36;
}

Position Robot::getPosition() {
	return Position(this->getY(), this->getX(), this->getYaw());
}

void Robot::ChangeYawRobotPlayer(double dYaw) {
	this->Read();
	double currYaw = this->getYaw();
	double wantedYaw = dYaw;

	//currYaw += M_PI;
	double absOffsetOne;

	int side = 0;

	absOffsetOne = currYaw - dYaw;
	if (absOffsetOne < 0) {
		absOffsetOne += M_PI * 2;
	}

	if (absOffsetOne < M_PI) {
		side = -1;
	} else {
		side = 1;
	}

	this->setSpeed(0.0, 0.10 * side);

	while (true) {
		this->Read();
		currYaw = this->getYaw();

		// Change the curr yaw :@
		if(currYaw < 0){
			currYaw = M_PI + (M_PI + currYaw);
		}
		cout<<"Wanted angle: "<< wantedYaw << " Robot Yaw: " <<currYaw<< endl;
		//currYaw += M_PI;

		//if (currYaw > dYaw - 0.06 && currYaw < dYaw + 0.06) {
		if (currYaw > wantedYaw - 0.02 && currYaw < wantedYaw + 0.02) {
			this->setSpeed(0.0, 0.0);
			break;
		}

	}
}

void Robot::UpdatePosition(double row, double col, double yaw) {
	double x = col;
	double y = row;

	//while (_pp.GetXPos() != x || _pp.GetYPos() != y || _pp.GetYPos() != yaw) {
		_pp.SetOdometry(x, y, yaw);
		this->Read();
	//
}
