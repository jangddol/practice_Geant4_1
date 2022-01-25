#include "PracSteppingAction.hh"
//#include "PracEventAction.hh"
//#include "PracDetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4Event.hh"
//#include "G4RunManager.hh"
//#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction)
{
    // pass
}


PracSteppingAction::~PracSteppingAction()
{
    // pass
}


void PracSteppingAction::UserSteppingAction(const G4Step* step)
{
    G4cout << "==================== Start of Step Information (Manual) ====================" << G4endl;
    G4cout << "Track - TrackID             : " << step->GetTrack()->GetTrackID() << G4endl;
    G4cout << "Track - Particle Name       : " << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
    G4cout << "Track - Position            : " << (step->GetTrack()->GetPosition())/cm << G4endl;
    G4cout << "Track - Kinetic Energy      : " << step->GetTrack()->GetKineticEnergy() << G4endl;
    G4cout << "Step Length                 : " << (step->GetStepLength())/cm << G4endl;
    G4cout << "Total Energy Deposit        : " << step->GetTotalEnergyDeposit() << G4endl;
    G4cout << "Delta Position              : " << step->GetDeltaPosition() << G4endl;
    G4cout << "====================  End of Step Information (Manual)  ====================" << G4endl;
}
