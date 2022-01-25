#include "PracSteppingAction.hh"
//#include "PracEventAction.hh"
//#include "PracDetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4Event.hh"
//#include "G4RunManager.hh"
//#include "G4LogicalVolume.hh"


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
    G4cout << "==================== Start of Step Information (Manual) ====================" << G4endldd;
    G4cout << "Track - TrackID             : " << step->GetTrack()->GetTrackID() << G4endl;
    G4cout << "Track - Particle Name       : " << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
    G4cout << "Track - Position            : " << step->GetTrack()->GetPosition() << G4endl;
    G4cout << "Track - Momentum            : " << step->GetTrack()->GetMomentum() << G4endl;
    G4cout << "Track - Velocity            : " << step->GetTrack()->GetVelocity() << G4endl;
    G4cout << "Track - Kinetic Energy      : " << step->GetTrack()->GetKineticEnergy() << G4endl;
    G4cout << "Track - Total Energy        : " << step->GetTrack()->GetTotalEnergy() << G4endl;
    G4cout << "Pre Step Point              : " << step->GetPreStepPoint() << G4endl;
    G4cout << "Post Step Point             : " << step->GetPostStepPoint() << G4endl;
    G4cout << "Step Length                 : " << step->GetStepLength() << G4endl;
    G4cout << "Total Energy Deposit        : " << step->GetTotalEnergyDeposit() << G4endl;
    G4cout << "Non-Ionizing Energy Deposit : " << step->GetNonIonizingEnergyDeposit() << G4endl;
    G4cout << "Control Flag                : " << step->GetControlFlag() << G4endl;
    G4cout << "Is First Step in Volume ?   : " << step->IsFirstStepInVolume() << G4endl;
    G4cout << "Is Last Step in Volume ?    : " << step->IsLastStepInVolume() << G4endl;
    G4cout << "Delta Position              : " << step->GetDeltaPosition() << G4endl;
    G4cout << "Delta Time                  : " << step->GetDeltaTime() << G4endl;
    G4cout << "Delta Momentum              : " << step->GetDeltaMomentum() << G4endl;
    G4cout << "Delta Energy                : " << step->GetDeltaEnergy() << G4endl;
    G4cout << "====================  End of Step Information (Manual)  ====================" << G4endl;
}
