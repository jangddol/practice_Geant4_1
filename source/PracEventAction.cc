#include "PracEventAction.hh"
#include "PracRunAction.hh"
#include "PracCoutModeSingleton.hh"

#include "G4Event.hh"
//#include "G4RunManager.hh" 
#include "g4csv.hh"

#include <cassert>

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

    size_t vectorSize = fRunIdVector.size();

    if (coutmode)
    {
        G4double totalEnergyDeposit = 0;
        for (size_t i=0; i < vectorSize; ++i)
        {
            totalEnergyDeposit += fEnergyDepositVector[i];
        }
        G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
        G4cout << "Event ID                 : " << event->GetEventID() << G4endl;
        G4cout << "Total Energy Deposit     : " << totalEnergyDeposit << G4endl;
        G4cout << "Total Step Length        : " << fTravelDistanceVector.at(0) << G4endl;
        G4cout << "====================  End of Event Information (Manual)  ====================" << G4endl;
        G4cout << G4endl;
    }

    G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
    
    if(fRunIdVector.size() != fEventIdVector.size())
    {
        G4cout << "1" << G4endl;
    }
    if(fRunIdVector.size() != fTrackIdVector.size())
    {
        G4cout << "2" << G4endl;
    }
    if(fRunIdVector.size() != fParticleNameVector.size())
    {
        G4cout << "3" << G4endl;
    }
    if(fRunIdVector.size() != fEnergyDepositVector.size())
    {
        G4cout << "fRunIdVector.size : " << fRunIdVector.size() << G4endl;
        G4cout << "fEnergyDepositVector.size : " << fEnergyDepositVector.size() << G4endl;
    }
    if(fRunIdVector.size() != fTravelDistanceVector.size())
    {
        G4cout << "5" << G4endl;
    }

    for (size_t i=0; i < vectorSize; ++i)
    {
        anaMan -> FillNtupleIColumn(0, fRunIdVector.at(i));
        anaMan -> FillNtupleIColumn(1, fEventIdVector.at(i));
        anaMan -> FillNtupleIColumn(2, fTrackIdVector.at(i));
        anaMan -> FillNtupleSColumn(3, fParticleNameVector.at(i));
        anaMan -> FillNtupleDColumn(4, fEnergyDepositVector.at(i));
        anaMan -> FillNtupleDColumn(5, fTravelDistanceVector.at(i));
        anaMan -> AddNtupleRow();
    }
}
