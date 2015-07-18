/*
 * Particle.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#define DEGREES_TO_RADIANS(degree)		((degree) * M_PI / 180)
#define METER_TO_CM(meter)				(meter * 100)

#include <math.h>
#include <iostream>
#include <stdlib.h>

#include "Utilities/Global.h"
#include "Utilities/Position.h"
#include "Map/Map.h"

class Particle {
private:
	Position _position;
	Map _map;
	float _belief;

public:
	Particle(double row, double col, double yaw, float belief, Map map);
	Particle(Position pos, float belief, Map map);
	virtual ~Particle();

	float getBelief();
	Position Particle::createPositionRandomly(Position currentPosition);
	vector<Particle> createParticles(int amount);

};

#endif /* PARTICLE_H_ */
