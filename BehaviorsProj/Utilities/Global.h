/*
 * Global.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

using namespace std;

// movement
#define ROTATION_SPEED 0.02
#define FORWARD_SPEED_SLOW 0.2
#define FORWARD_SPEED 0.4
#define MINIMUM_DISTANCE 1.7

// robot movement directions
#define MOVE_FORWARD 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define STOP 9

// Grid
#define FREE 0
#define BLOCK 1
#define PATH_CELL 2
#define START_CELL 3
#define GOAL_CELL 4

// robot angle directions
#define ANGLE_UP 1.57
#define ANGLE_DOWN -1.57
#define ANGLE_RIGHT 0
#define ANGLE_LEFT -3.14
#define ANGLE_UP_LEFT 2.425
//#define ANGLE_UP_LEFT 2.356
#define ANGLE_UP_RIGHT 0.785
#define ANGLE_DOWN_LEFT -2.356
#define ANGLE_DOWN_RIGHT -0.785

class Global {
public:
	Global();
	virtual ~Global();
};

#endif /* GLOBAL_H_ */
