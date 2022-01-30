#pragma once

#ifndef PracEventAction_h
#define PracEventAction_h

#include "G4Event.hh"
#include "G4UserEventAction.hh"
#include "PracRunAction.hh"

#include <vector>
#include <cassert>

#include "globals.hh"

class PracEventAction : public G4UserEventAction
{
	public:
		PracEventAction(PracRunAction* runAction);
		virtual ~PracEventAction();
        
        G4int GetRunIdVectorSize(){return static_cast<G4int>(fRunIdVector.size());}
        void AppendRunIdVector(const G4int runId){fRunIdVector.push_back(runId);}
        void AppendEventIdVector(const G4int eventId){fEventIdVector.push_back(eventId);}
        void AppendTrackIdVector(const G4int trackId){fTrackIdVector.push_back(trackId);}
        void AppendParticleNameVector(const G4String particleName){fParticleNameVector.push_back(particleName);}
        void AddEnergyDepositVector(const G4double energyDeposit, const G4int trackId)
        {
            G4int vectorSize = static_cast<G4int>(fEnergyDepositVector.size());
            if(vectorSize >= trackId)
            {
                fEnergyDepositVector[trackId-1] += energyDeposit;
            }
            else if(vectorSize + 1 == trackId)
            {
                fEnergyDepositVector.push_back(energyDeposit);
            }
            else
            {
                assert(true && "EnergyDeposit : vectorSize + 1 < trackId");
            }
        }
        void AddTravelDistanceVector(const G4double stepLength, const G4int trackId)
        {
            G4int vectorSize = static_cast<G4int>(fTravelDistanceVector.size());
            if(vectorSize >= trackId)
            {
                fTravelDistanceVector[trackId-1] += stepLength;
            }
            else if(vectorSize + 1 == trackId)
            {
                fTravelDistanceVector.push_back(stepLength);
            }
            else
            {
                assert(true && "TravelDistance : vectorSize + 1 < trackId");
            }
        }
        G4int GetEventID(){return fEventID;}
        PracRunAction* GetRunAction(){return fRunAction;}
        
		virtual void BeginOfEventAction(const G4Event* event);
		virtual void EndOfEventAction(const G4Event* event);

    private:
        std::vector<G4int> fRunIdVector;
        std::vector<G4int> fEventIdVector;
        std::vector<G4int> fTrackIdVector;
        std::vector<G4String> fParticleNameVector;
        std::vector<G4double> fEnergyDepositVector;
        std::vector<G4double> fTravelDistanceVector;
        PracRunAction* fRunAction;
        G4int fEventID;
};

#endif
