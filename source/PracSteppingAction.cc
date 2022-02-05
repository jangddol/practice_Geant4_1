#include "PracSteppingAction.hh"
#include "PracEventAction.hh"
#include "PracDetectorConstruction.hh"
#include "PracCoutModeSingleton.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction) : G4UserSteppingAction(), fEventAction(eventAction), fScoringVolume(0)
{
    // pass
}


PracSteppingAction::~PracSteppingAction()
{
    // pass
}


void PracSteppingAction::UserSteppingAction(const G4Step* step)
{
    PracCoutModeSingleton* coutModeSingleton = PracCoutModeSingleton::GetInstance();
    G4bool coutMode = coutModeSingleton->GetPracCoutMode();
    if (coutMode)
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
        G4cout << G4endl;
    }
    
    if (!fScoringVolume)
    {
        const PracDetectorConstruction* detectorConstruction = static_cast<const PracDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();
    }
    G4LogicalVolume* currentLogicalVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    if (currentLogicalVolume == fScoringVolume) 
    {
        G4int trackId = step->GetTrack()->GetTrackID();
        if (fEventAction->IsInTrackIdVector(trackId) == false)
        {
            fEventAction->AppendRunIdVector(fEventAction->GetRunAction()->GetRunID());
            fEventAction->AppendEventIdVector(fEventAction->GetEventID());
            fEventAction->AppendTrackIdVector(trackId);
            fEventAction->AppendParticleNameVector(step->GetTrack()->GetParticleDefinition()->GetParticleName());
            fEventAction->AppendEnergyDepositVector(step->GetTotalEnergyDeposit());
            fEventAction->AppendTravelDistanceVector(step->GetStepLength());
        }
        else
        {
            fEventAction->AddEnergyDepositVector(step->GetTotalEnergyDeposit());
            fEventAction->AddTravelDistanceVector(step->GetStepLength());
        }
        fEventAction->AddEdep(step->GetTotalEnergyDeposit());
    }
}
