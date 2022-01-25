#pragma once

#ifndef PracEventAction_h
#define PracEventAction_h

#include "G4UserEventAction.hh"
#include "globals.hh"

class PracRunAction;

class PracEventAction : public G4UserEventAction
{
	public:
		PracEventAction(PracRunAction* runAction);
		virtual ~PracEventAction();
        
        void AddEnergyDeposit(const G4double energyDeposit){fEnergyDeposit += energyDeposit;}
        void AddStepLength(const G4double stepLength){fStepLength += stepLength;}

		virtual void BeginOfEventAction(const G4Event* event);
		virtual void EndOfEventAction(const G4Event* event);

    private:
        G4double fEnergyDeposit;
        G4double fStepLength;
        PracRunAction* fRunAction;
};

#endif
