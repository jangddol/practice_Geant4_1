#pragma once

#ifndef PracSteppingAction_h
#define PracSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class PracEventAction;

class G4LogicalVolume;

class PracSteppingAction : public G4UserSteppingAction
{
	public:
		PracSteppingAction(PracEventAction* eventAction);
		virtual ~PracSteppingAction();

		virtual void UserSteppingAction(const G4Step*);
	
	private:
		PracEventAction* fEventAction;
        G4LogicalVolume* fScoringVolume;
};

#endif
