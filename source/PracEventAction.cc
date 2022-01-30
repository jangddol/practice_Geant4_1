#include "PracEventAction.hh"
#include "PracRunAction.hh"
#include "PracCoutModeSingleton.hh"

#include "G4Event.hh"
//#include "G4RunManager.hh" 
#include "g4csv.hh"

#include "G4SystemOfUnits.hh"

PracEventAction::PracEventAction(PracRunAction* runAction) : G4UserEventAction(), 
                                                             fRunIdVector({}),
                                                             fEventIdVector({}),
                                                             fTrackIdVector({}),
                                                             fParticleNameVector({}),
                                                             fEnergyDepositVector({}),
                                                             fTravelDistanceVector({}),
                                                             fRunAction(runAction)
{
	// pass
}


PracEventAction::~PracEventAction() {}


void PracEventAction::BeginOfEventAction(const G4Event* event)
{
    fEventID = event->GetEventID();
    fRunIdVector = {};
    fEventIdVector = {};
    fTrackIdVector = {};
    fParticleNameVector = {};
    fEnergyDepositVector = {};
    fTravelDistanceVector = {};
}


void PracEventAction::EndOfEventAction(const G4Event* event)
{
    PracCoutModeSingleton* coutmodeinstance = PracCoutModeSingleton::GetInstance();
    G4bool coutmode = coutmodeinstance->GetPracCoutMode();

    if (coutmode)
    {
        // G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
        // G4cout << "Event ID                 : " << event->GetEventID() << G4endl;
        // G4cout << "Total Energy Deposit     : " << fEnergyDeposit << G4endl;
        // G4cout << "Total Step Length        : " << fStepLength << G4endl;
        // G4cout << "====================  End of Event Information (Manual)  ====================" << G4endl;
        // G4cout << G4endl;
    }

    G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
    size_t vectorSize = fRunIdVector.size();
    for (size_t i=0; i < vectorSize; ++i)
    {
        anaMan -> FillNtupleIColumn(0, fRunIdVector[i]);
        anaMan -> FillNtupleIColumn(1, fEventIdVector[i]);
        anaMan -> FillNtupleIColumn(2, fTrackIdVector[i]);
        anaMan -> FillNtupleSColumn(3, fParticleNameVector[i]);
        anaMan -> FillNtupleDColumn(4, fEnergyDepositVector[i]);
        anaMan -> FillNtupleDColumn(5, fTravelDistanceVector[i]);
        anaMan -> AddNtupleRow();
    }
}
