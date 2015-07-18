/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, vector<Position> waypoints) {
	_robot = robot;
	_waypoints = waypoints;
}
void Manager::run() {
	unsigned wayPointIndex = 0;

	for (int i = 0; i < 20; i++)
		this->_robot->Read();

	// Get the first position of the robot (the start position)
	Position currentPosition = this->_waypoints[wayPointIndex];

	// Get the next waypoint position
	wayPointIndex++;
	Position nextPosition = this->_waypoints[wayPointIndex];

	// Change the movement direction of the robot
	double angle = this->calcAngleDelta(this->_robot->getPosition(),
			nextPosition);
	this->_robot->ChangeYawRobotPlayer(angle);

	//changeDirection(currentPosition, nextPosition, true);

	double distance, currentDistance;

	// Run until we didnt reached the last waypoint (goal)
	while (wayPointIndex < this->_waypoints.size()) {
		this->_robot->Read();

		// Calcuate the metric distance between the robot and next position
		distance = this->calcDistance(this->_robot->getPosition(),
				nextPosition);

		cout << "Distance between Waypoint (" << nextPosition.getRow() << ","
				<< nextPosition.getCol() << ") to Robot ("
				<< this->_robot->getY() << ", " << this->_robot->getX()
				<< "," <<this->_robot->getYaw()<< ") is " << distance << endl;

		// Check if the distance of the robot the next waypoint is less than the minimum distance
		if (distance <= MINIMUM_DISTANCE) {

			// move forawrd
			this->_robot->setSpeed(FORWARD_SPEED_SLOW, 0);

			//
			currentDistance = distance;
			distance = this->calcDistance(this->_robot->getPosition(),
					nextPosition);
			/*
			// Run until we reach waypoint
			while (distance <= currentDistance) {
				// Read and set speed
				this->_robot->Read();
				this->_robot->setSpeed(FORWARD_SPEED, 0);

				// Calc the next distance
				currentDistance = distance;
				distance = this->calcDistance(this->_robot->getPosition(),
						nextPosition);
			}*/

			// Stop the robot to change angle
			this->_robot->setSpeed(0, 0);

			// Get the current waypoint (we just reached there)
			currentPosition = this->_waypoints[wayPointIndex];

			// Get the next waypoint
			wayPointIndex++;
			nextPosition = this->_waypoints[wayPointIndex];

			//TODO: check why we send true?! we are not at the start
			changeDirection(currentPosition, nextPosition, true);
		} else {
			this->_robot->setSpeed(FORWARD_SPEED, 0);
		}
	}

	cout << "Goal point reached successfully" << endl;

	/*
	 * OLD CODE
	 _robot->Read();
	 if(!(_curr->startCond()))
	 return;
	 _curr->action();
	 while(_curr !=NULL)
	 {
	 while(_curr->stopCond() == false)
	 {
	 _curr->action();
	 _robot->Read();
	 }
	 _curr = _curr->selectNext();
	 _robot->Read();
	 }*/
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

double Manager::calcDistance(Position currentPosition, Position nextPosition) {
	double deltaRow = abs(currentPosition.getRow() - nextPosition.getRow());
	double deltaCol = abs(currentPosition.getCol() - nextPosition.getCol());

	return sqrt((pow(deltaRow, 2)) + (pow(deltaCol, 2)));
}

void Manager::changeDirection(Position currentPosition, Position nextPosition,
		bool isStartPoint) {
	// Get the angle we need to rotate the robot so the robot will be at the wanted angle
	double angleDelta = this->calcAngleDelta(currentPosition, nextPosition);

	// Run until the angel delta will be lower then 0.005
	// Rotating the robot
	while (abs(angleDelta) >= 0.005) {
		this->_robot->Read();

		// Rotate
		this->_robot->setSpeed(0,
				this->calcAngleDelta(currentPosition, nextPosition));

		// Get the angle we need to rotate the robot so the robot will be at the wanted angle
		angleDelta = this->calcAngleDelta(currentPosition, nextPosition);

	}

	// If we are on the start point set angle to 0
	if (isStartPoint) {
		this->_robot->setSpeed(0, 0);
	}

}

double Manager::calcAngleDelta(Position currentPosition,
		Position nextPosition) {

	// calculate the next movement
	int nextDirection = this->calcNextMovement(currentPosition, nextPosition);
	float ang;
	this->_robot->Read();
	float currentYawInDegree = (this->_robot->getYaw() * 180) / M_PI;

	switch (nextDirection) {
	case UP_LEFT:
		// get the angle in radian
		ang = atan2(abs(currentPosition.getRow() - nextPosition.getRow()),
				abs(currentPosition.getCol() - nextPosition.getCol()));
		// change angle to degree
		ang = (ang * 180) / M_PI;
		// calc the delta degree
		ang = 180 - currentYawInDegree - ang;
		// change the degree to radian
		ang = (ang * M_PI) / 180;
		break;
	default:
		return -1;
	}

	return ang;

	// calculate the next movement
//	int nextDirection = this->calcNextMovement(currentPosition, nextPosition);
//	double nextAngle;
//
//	// Choose the next angle by the next direction
//	switch (nextDirection) {
//	case UP:
//		nextAngle = ANGLE_UP;
//		break;
//	case DOWN:
//		nextAngle = ANGLE_DOWN;
//		break;
//	case RIGHT:
//		nextAngle = ANGLE_RIGHT;
//		break;
//	case LEFT:
//		nextAngle = ANGLE_LEFT;
//		break;
//	case UP_LEFT:
//		nextAngle = ANGLE_UP_LEFT;
//		break;
//	case UP_RIGHT:
//		nextAngle = ANGLE_UP_RIGHT;
//		break;
//	case DOWN_LEFT:
//		nextAngle = ANGLE_DOWN_LEFT;
//		break;
//	case DOWN_RIGHT:
//		nextAngle = ANGLE_DOWN_RIGHT;
//		break;
//	default:
//		return -1;
//	}
//
//	this->_robot->Read();
//	double deltaAngle = nextAngle - this->_robot->getYaw();

//	return (deltaAngle);
}

int Manager::calcNextMovement(Position currentPosition, Position nextPosition) {
	int direction;

	// Check if the next row is above the current (the direction will be DOWN* because the rows grows downward)
	if (nextPosition.getRow() > currentPosition.getRow()) {
		// Check if the next col is right from current
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = DOWN_RIGHT;
		}
		// Check if the next col is left from current
		else if (nextPosition.getCol() < currentPosition.getCol()) {
			direction = DOWN_LEFT;
		} else {
			// Same column
			direction = DOWN;
		}
	}

	// Check if the next row is below the current (the direction will be UP* because the rows grows downward)
	else if (nextPosition.getRow() < currentPosition.getRow()) {
		// Check if the next col is right from current
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = UP_RIGHT;
		}
		// Check if the next col is left from current
		else if (nextPosition.getCol() < currentPosition.getCol()) {
			direction = UP_LEFT;
		} else {
			// Same column
			direction = UP;
		}
	}
	// If we reached to here, that means we are on the same row,
	// so lets check if the next position is right/left from current position
	else {
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = RIGHT;
		} else {
			direction = LEFT;
		}
	}

	return direction;
}

