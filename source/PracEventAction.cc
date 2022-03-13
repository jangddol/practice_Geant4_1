#include "PracEventAction.hh"
#include "PracRunAction.hh"
#include "PracCoutModeSingleton.hh"
#include "PracParticleEnergy.hh"

#include "G4Track.hh"
#include "G4Event.hh"
#include "PracAnalysisManager.hh"

#include <cassert>
#include <vector>

#include "G4SystemOfUnits.hh"

PracEventAction::PracEventAction(PracRunAction* runAction) : G4UserEventAction(), 
                                                             fRunIdVector({}),
                                                             fEventIdVector({}),
                                                             fTrackIdVector({}),
                                                             fParticleNameVector({}),
                                                             fEnergyDepositVector({}),
                                                             fTravelDistanceVector({}),
                                                             fRunAction(runAction),
                                                             preStepTrackID(1)
{
	PracCoutModeSingleton* coutmodeinstance = PracCoutModeSingleton::GetInstance();
    coutmode = coutmodeinstance->GetPracCoutMode();
}


PracEventAction::~PracEventAction() {}


void PracEventAction::ManageSecondaryKineticMap(const std::vector<const G4Track*>* secondaryTrackVector)
{
    size_t trackLength = secondaryTrackVector -> size();
    intptr_t elementpointer;
    for (size_t i=0; i < trackLength; i++)
    {
        const G4Track* element = secondaryTrackVector -> at(i);
        elementpointer = reinterpret_cast<intptr_t>(element);
        G4double elementKinetic = element -> GetKineticEnergy();
        secondaryKineticMap[elementpointer] = elementKinetic;
    }
}


void PracEventAction::BeginOfEventAction(const G4Event* event)
{
    fEventID = event->GetEventID();
    fRunIdVector = {};
    fEventIdVector = {};
    fTrackIdVector = {};
    fParticleNameVector = {};
    fEnergyDepositVector = {};
    fTravelDistanceVector = {};
    fEnergyLossInelasticVector = {};
    fEnergyLossLeakVector = {};
    fEdep = 0.;
    fElInel = 0.;
    fEleak = 0.;
    fBEdif = 0.;
    preStepTrackID = 1;
    preStepKineticEnergy = PracParticleEnergy().GetParticleEnergy();
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
        G4cout << "Energy Loss in Inelastic    : " << fElInel << G4endl;
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
        anaMan -> FillNtupleDColumn(6, fEnergyLossInelasticVector.at(i));
        anaMan -> FillNtupleDColumn(7, fEnergyLossLeakVector.at(i));
        anaMan -> FillNtupleDColumn(8, fBindingEnergyDifferenceVector.at(i));
        anaMan -> AddNtupleRow();
    }
    anaMan -> FillH1(0, fEdep);
    anaMan -> FillH1(1, fElInel);
    anaMan -> FillH1(2, fEleak);
    anaMan -> FillH1(3, fEdep + fElInel + fEleak);
    anaMan -> FillH1(4, fBEdif);
    anaMan -> FillH1(5, fElInel - fBEdif);
    anaMan -> FillH1(6, fEdep + fBEdif + fEleak);
    anaMan -> FillH2(0, fEdep, fElInel);
}
