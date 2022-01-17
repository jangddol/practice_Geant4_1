#pragma once

#ifndef PracPrimaryGeneratorAction_h
#define PracPrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PracPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		PracPrimaryGeneratorAction();
		virtual ~PracPrimaryGeneratorAction();

		virtual void GeneratePrimaries(G4Event*);

		const G4ParticleGun* GetParticlaGun() const { return fParticleGun; }
	
	private:
		G4ParticleGun* fParticleGun;
};

#endif
