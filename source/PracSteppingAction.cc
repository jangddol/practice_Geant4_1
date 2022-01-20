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


void PracSteppingAction::UserSteppingAction(const G4Step*)
{
    G4cout << "Step is stepping." << G4endl;
}
