/*
 * Particle.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "Particle.h"

Particle::Particle(double row, double col, double yaw, float belief, Map map) {
	this->_position = Position(row, col, yaw);
	this->_belief = belief;
	this->_map = map;
}

Particle::Particle(Position pos, float belief, Map map) {
	this->_position = pos;
	this->_belief = belief;
	this->_map = map;

	this->_position = createPositionRandomly(pos);
}

float Particle::getBelief() {
	return this->_belief;
}

Position Particle::createPositionRandomly(Position currentPosition) {

	// Calc range of delta particle
	int rowRange = floor(_map.getHeight() / 2 * 0.015);
	int colRange = floor(_map.getWidth() / 2 * 0.015);
	int YawRange = floor(M_PI * 2 / 2 * 0.1);

	int deltaRow = (rand() % 2 * rowRange) - rowRange;
	int deltaCol = (rand() % 2 * colRange) - colRange;
	int deltaYaw = (rand() % 2 * YawRange) - YawRange;

	Position randomLocation = Position(currentPosition.getRow() + deltaRow,
			currentPosition.getCol() + deltaCol,
			currentPosition.getYaw() + deltaYaw);

	return randomLocation;
}

vector<Particle> Particle::createParticles(int amount) {
	vector<Particle> vecPar;

	// Generate particles (the constructor of particle(position) creates random particle
	for (int index = 0; index < amount; index++) {
		vecPar.push_back(Particle(_position, _belief * 0.9, _map));
	}

	return vecPar;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

