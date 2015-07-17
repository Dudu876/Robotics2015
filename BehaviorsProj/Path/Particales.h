/*
 * Particales.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef PARTICALES_H_
#define PARTICALES_H_

class Particales {
public:
	double pX;
	double pY;
	double pYaw;
	double pBelief;

	//Constructors of objects type of Particle
	Particales(float x, float y);
	Particales(float x, float y, float yaw);
	Particales(float x, float y, float yaw, float belief);

	//Method which handles the particle position update
	void UpdateParticle(float delX, float delY, float delYaw, float laserScan[],
			int laserCount);

	//Method which calculate the particle's probability by map
	float ProbUpdateMapByScan(float laserScan[], int laserCount);

	//Method which calculate the particle's probability
	float ProbCalc(float delX, float delY, float delTetha);

	double GetBelief();

	double GetX();

	double GetY();

	double GetYaw();

	//Method which converts laser index to angle
	float ConverteIndexToAngle(int index, int x, int radius);

	// Destructor of objects type of Particle
	//~Particales();
	virtual ~Particales();
};

#endif /* PARTICALES_H_ */
