/*
 * Particales.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "Particles.h"
#include "../Utilities/Global.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

//Constructors of objects type of Particle
Particales::Particales(float x,float y) {
	Particales(x,y,0);
}
Particales::Particales(float x,float y,float yaw) {
	Particales(x,y,yaw,1.0);
}
Particales::Particales(float x, float y, float yaw, float belief){
	pX = x;
	pY = y;
	pYaw = yaw;
	pBelief = belief;
}

//Method which handles the particle position update
void Particales::UpdateParticle(float delX, float delY, float delYaw, float laserScan[], int laserCount) {

	// moving the particle with the same estimated vector that the robot itself moved
	pX += M_TO_CM(delX);
	pY += M_TO_CM(delY);
	pYaw += delYaw;

	// updating the belief of the new location!
	pBelief *=  /* ProbCalc(delX, delY, delYaw) */ ProbUpdateMapByScan(laserScan,laserCount);
}

//Method which calculate the particle's probability by map
float Particales::ProbUpdateMapByScan(float laserScan[], int laserCount) {
	float xObj,yObj;
	int mismatch = 0;
	int match = 0;
	int i,j;

	for (i=0; i<laserCount; i = i+INDEX_PER_DEGREE) {

		// the sensor detects that the road is open
		if (laserScan[i] > OPEN_PATH_RANGE) {

			for (j=SENSOR_FROM_END; j<=SENSOR_DETECTION_RANGE; j = j+CELL_DIM) {
				xObj = (j * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
				yObj = (j * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
				 if(SimManager::GetInstance()->m_Map->getCell(xObj,yObj)->isCellWalkable()) // the cell is open (like the laser detects)
					 match++;
				 else
					mismatch++;
			}
		// the laser detects that the road is closed
		}else {
			xObj = ((M_TO_CM(laserScan[i])) * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
			yObj = ((M_TO_CM(laserScan[i])) * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
			if (SimManager::GetInstance()->m_Map->getCell(xObj,yObj)->isCellWalkable()) // the cell is open (and the laser detects otherwise)
				mismatch++;
			else
				match++;
		}
	}

	if ((mismatch + match) == 0)
		return (float) 0;
	else
		return ((float)(match))/(mismatch + match);

}

//Method which calculate the particle's probability
float Particales::ProbCalc(float delX, float delY, float delYaw) {
	float distance = sqrt(pow(delX,2)+pow(delY,2));
	if ((delYaw < NORMAL_ACCURATE_ANGLE_TO_MOVE) && (delYaw > -NORMAL_ACCURATE_ANGLE_TO_MOVE)) {
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance + 0.2);
	}
	else if ((delYaw < MAX_ACCURATE_ANGLE_TO_MOVE) && (delYaw > -MAX_ACCURATE_ANGLE_TO_MOVE))
	{
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance - 0.2);
	}
	return 1.0;
}

//Method which return the particle Belief value
double Particales::GetBelief() {
	return pBelief;
}

//Method which return the particle X value
double Particales::GetX() {
	return pX;
}

//Method which return the particle Y value
double Particales::GetY() {
	return pY;
}

//Method which return the particle Yaw value
double Particales::GetYaw() {
	return pYaw;
}

//Method which converts laser index to angle
float Particales::ConverteIndexToAngle(int index, int x, int radius) {
	return ((float)index*((float)radius/x))-radius/2.0;
}

//Destructor of objects type of Particle
Particales::~Particales() {
}
