#pragma once

#ifndef PracEventAction_h
#define PracEventAction_h

#include "G4Event.hh"
#include "G4UserEventAction.hh"
#include "PracRunAction.hh"

#include <vector>
#include <cassert>
#include <algorithm>
#include <map>

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
        void AppendEnergyLossInelasticVector(const G4double elInel){fEnergyLossInelasticVector.push_back(elInel);}
        void AppendEnergyLossLeakVector(const G4double eleak){fEnergyLossLeakVector.push_back(eleak);}
        void AppendBindingEnergyDifferenceVector(const G4double bindingEnergyDif){fBindingEnergyDifferenceVector.push_back(bindingEnergyDif);}

        void ManageSecondaryKineticMap(const std::vector<const G4Track*>*);
        G4double GetSecondaryKineticEnergy(const G4Track* track)
        {
            intptr_t trackpointer = reinterpret_cast<intptr_t>(track);
            return secondaryKineticMap[trackpointer];
        }
        
        void AddEnergyDepositVector(const G4double energyDeposit){fEnergyDepositVector.back() += energyDeposit;}
        void AddTravelDistanceVector(const G4double stepLength){fTravelDistanceVector.back() += stepLength;}
        void AddEnergyLossInelasticVector(const G4double elInel){fEnergyLossInelasticVector.back() += elInel;}
        void AddEnergyLossLeakVector(const G4double eleak){fEnergyLossLeakVector.back() += eleak;}
        void AddBindingEnergyDifferenceVector(const G4double bindingEnergyDif){fBindingEnergyDifferenceVector.back() += bindingEnergyDif;}
        void AddEdep(const G4double edep){fEdep += edep;}
        void AddElInel(const G4double elInel){fElInel += elInel;}
        void AddEleak(const G4double eleak){fEleak += eleak;}
        void AddBEdif(const G4double bindingEnergyDif){fBEdif += bindingEnergyDif;}

        G4double GetEdep(){return fEdep;}
        G4double GetElInel(){return fElInel;}
        G4double GetEleak(){return fEleak;}
        G4double GetBEdif(){return fBEdif;}
        G4int GetEventID(){return fEventID;}
        PracRunAction* GetRunAction(){return fRunAction;}
        
        G4int GetPreStepTrackID(){return preStepTrackID;}
        void SetPreStepTrackID(const G4int trackID){preStepTrackID = trackID;}
        
        G4double GetPreStepKineticEnergy(){return preStepKineticEnergy;}
        void SetPreStepKineticEnergy(const G4double energy){preStepKineticEnergy = energy;}

		virtual void BeginOfEventAction(const G4Event* event);
		virtual void EndOfEventAction(const G4Event* event);

    private:
        std::vector<G4int> fRunIdVector;
        std::vector<G4int> fEventIdVector;
        std::vector<G4int> fTrackIdVector;
        std::vector<G4String> fParticleNameVector;
        std::vector<G4double> fEnergyDepositVector;
        std::vector<G4double> fTravelDistanceVector;
        std::vector<G4double> fEnergyLossInelasticVector;
        std::vector<G4double> fEnergyLossLeakVector;
        std::vector<G4double> fBindingEnergyDifferenceVector;

        std::map<intptr_t, G4double> secondaryKineticMap;

        G4double fEdep;
        G4double fElInel;
        G4double fEleak;
        G4double fBEdif;

        PracRunAction* fRunAction;
        G4int fEventID;
        G4int preStepTrackID;
        G4double preStepKineticEnergy;
        G4bool coutmode;
};

#endif
