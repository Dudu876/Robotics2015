/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(Position startPosition, Map * map) {
	_map = map;
	srand(time(NULL));

	_storePosition = Position(startPosition.getRow(), startPosition.getCol(),
			startPosition.getYaw());

	// create particles from start position
	Particle startParticle = Particle(startPosition.getRow(),
			startPosition.getCol(), startPosition.getYaw(), (float) (1),
			this->_map);
	this->createParticlesFromParticle(startParticle, true);
	//_particles.insert(_particles.end(), childParticles.begin(), childParticles.end());
}

void LocalizationManager::createParticlesFromParticle(Particle fromParticle,
		bool isVectorEmpty) {

	if (isVectorEmpty == true) {
		// add start position
		this->_particles.push_back(fromParticle);
	}

	// create particles from best particle, the amount will be (MAX_PARTICLE - amount we have)
	vector<Particle> childParticles =
			getHighestBeliefParticle().createParticles(
			MAX_PARTICLE - this->_particles.size());

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

	Particle bestParticle = _particles[0];

	// run over the particles
	//for (particlesIterator = _particles.begin(); particlesIterator != _particles.end(); ++particlesIterator) {
	for (int index = 0; index < _particles.size(); index++) {
		// check if we got better particle
		if (_particles[index].getBelief() > bestParticle.getBelief())
			bestParticle = _particles[index];
	}

	return bestParticle;
}

void LocalizationManager::updateParticles(Position deltaPosition,
		float laserScan[]) {

	// store the position for restore
	_storePosition.setRow(_storePosition.getRow() + deltaPosition.getRow());
	_storePosition.setCol(_storePosition.getCol() + deltaPosition.getCol());
	_storePosition.setYaw(_storePosition.getYaw() + deltaPosition.getYaw());

	//vector<Particle> particlesForDelete;
	vector<Particle> goodParticles;

	for (int index = 0; index < this->_particles.size(); index++) {
		float currentParticleBelief;

		// update particle belief and get his new belief
		currentParticleBelief = this->_particles[index].UpdateParticle(
				deltaPosition.getRow(), deltaPosition.getCol(),
				deltaPosition.getYaw(), laserScan);

		// check if particle bellief is too low
		if (currentParticleBelief < BELIEF_TRASHHOLD) {
			//particlesForDelete.push_back(this->_particles[index]);
		} else {
			goodParticles.push_back(this->_particles[index]);
		}
	}

	// all particle died, so we need to create new particle from storePosition
	if (goodParticles.size() == 0) {
		// create particles from start position
		Particle startParticle = Particle(this->_storePosition.getRow(),
				this->_storePosition.getCol(), this->_storePosition.getYaw(), (float) (1),
				this->_map);
		this->createParticlesFromParticle(startParticle, true);
	} else {
		this->_particles = goodParticles;
		this->createParticlesFromParticle(getHighestBeliefParticle(), false);
	}
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

