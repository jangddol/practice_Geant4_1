#include "PracEventAction.hh"
#include "PracRunAction.hh"
#include "PracCoutModeSingleton.hh"

#include "G4Event.hh"
#include "PracAnalysisManager.hh"

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
	PracCoutModeSingleton* coutmodeinstance = PracCoutModeSingleton::GetInstance();
    coutmode = coutmodeinstance->GetPracCoutMode();
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
    fEdep = 0.;
    fEleak = 0.;
    fEnonIon = 0.;
}


void PracEventAction::EndOfEventAction(const G4Event* event)
{
    size_t vectorSize = fRunIdVector.size();

    if (coutmode)
    {
        G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
        G4cout << "Event ID                    : " << event->GetEventID() << G4endl;
        G4cout << "Total Energy Deposit        : " << fEdep << G4endl;
        G4cout << "Leaked Particle Energy      : " << fEleak << G4endl;
        G4cout << "Non-ionizing Energy Deposit : " << fEnonIon << G4endl;
        G4cout << "Total Step Length           : " << fTravelDistanceVector.at(0) << G4endl;
        G4cout << "====================  End of Event Information (Manual)  ====================" << G4endl;
        G4cout << G4endl;
    }
    
    G4VAnalysisManager* anaMan = PracAnalysisManager().GetInstance();
    
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
    anaMan -> FillH1(0, fEdep);
    anaMan -> FillH1(1, fEdep + fEleak);
    anaMan -> FillH1(2, fEdep - fEleak);
    anaMan -> FillH1(3, fEleak);
    anaMan -> FillH1(4, fEnonIon);
    anaMan -> FillH1(5, fEdep - fEnonIon);
    anaMan -> FillH2(0, fEdep, fEdep + fEleak);
}
