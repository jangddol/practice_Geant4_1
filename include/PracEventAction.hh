#pragma once

#ifndef PracEventAction_h
#define PracEventAction_h

#include "G4Event.hh"
#include "G4UserEventAction.hh"
#include "PracRunAction.hh"

#include <vector>
#include <cassert>
#include <algorithm>

#include "globals.hh"

class PracEventAction : public G4UserEventAction
{
	public:
		PracEventAction(PracRunAction* runAction);
		virtual ~PracEventAction();
        
        G4int GetRunIdVectorSize(){return static_cast<G4int>(fRunIdVector.size());}
        G4bool IsInTrackIdVector(const G4int trackId)
        {
            if(std::find(fTrackIdVector.begin(), fTrackIdVector.end(), trackId) != fTrackIdVector.end())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        void AppendRunIdVector(const G4int runId){fRunIdVector.push_back(runId);}
        void AppendEventIdVector(const G4int eventId){fEventIdVector.push_back(eventId);}
        void AppendTrackIdVector(const G4int trackId){fTrackIdVector.push_back(trackId);}
        void AppendParticleNameVector(const G4String particleName){fParticleNameVector.push_back(particleName);}
        void AppendEnergyDepositVector(const G4double energyDeposit){fEnergyDepositVector.push_back(energyDeposit);}
        void AppendTravelDistanceVector(const G4double stepLength){fTravelDistanceVector.push_back(stepLength);}
        void AddEnergyDepositVector(const G4double energyDeposit){fEnergyDepositVector.back() += energyDeposit;}
        void AddTravelDistanceVector(const G4double stepLength){fTravelDistanceVector.back() += stepLength;}
<<<<<<< HEAD
        void AddEdep(const G4double edep){fEdep += edep;}
        G4double GetEdep(){return fEdep;}
=======
>>>>>>> ac5344fc3196136717d02df5a79fc375af59c22d
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
<<<<<<< HEAD
        G4double fEdep;
=======
>>>>>>> ac5344fc3196136717d02df5a79fc375af59c22d
        PracRunAction* fRunAction;
        G4int fEventID;
};

#endif
