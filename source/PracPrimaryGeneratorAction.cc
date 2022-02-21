#include "PracPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4ParticleGun.hh" // gun
#include "G4ParticleTable.hh" // to define the type of particle, you need this
#include "G4ParticleDefinition.hh" // to generate an instance of particle, you need this
#include "G4SystemOfUnits.hh"


PracPrimaryGeneratorAction::PracPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);

	// default particle kinematic
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "proton");
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	fParticleGun->SetParticleEnergy(100. * MeV);
}


PracPrimaryGeneratorAction::~PracPrimaryGeneratorAction()
{
	delete fParticleGun;
}


void PracPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4double x0 = 0*m;
	G4double y0 = 0*m;
	G4double z0 = -0.5*m;

	fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

	fParticleGun->GeneratePrimaryVertex(anEvent);
}
