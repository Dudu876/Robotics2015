/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(Position startPosition, Map map) {
	_map = map;
	srand(time(NULL));

	// add start position
	this->_particles.push_back(
			Particle(startPosition.getRow(), startPosition.getCol(),
					startPosition.getYaw(), (float) 1, map));

	// Initializing the particles list by the PARTICLES_AMOUNT value
	vector<Particle> childParticles =
			getHighestBeliefParticle().createParticles(
			MAX_PARTICLE - 1);

	// Add childParticles to _particles
	addParticleFromVector(childParticles);
}

void LocalizationManager::addParticleFromVector(
		const vector<Particle>& childParticles) {
	// Add child particles to _particles
	for (int index = 0; index < childParticles.size(); index++) {
		this->_particles.push_back(childParticles[index]);
	}
}

Particle LocalizationManager::getHighestBeliefParticle() {
	list<Particle>::iterator particlesIterator = _particles.begin();
	Particle * highestBeliefParticle = particlesIterator.operator ->();

	for (particlesIterator = _particles.begin();
			particlesIterator != _particles.end(); ++particlesIterator) {
		if (particlesIterator->getBelief() > highestBeliefParticle->getBelief())
			highestBeliefParticle = particlesIterator.operator ->();
	}

	return highestBeliefParticle;
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

