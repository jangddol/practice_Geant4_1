#pragma once

#ifndef PracSteppingAction_h
#define PracSteppingAction_h

#include "G4Track.hh"

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

#include <vector>

class PracEventAction;

class G4LogicalVolume;

class PracSteppingAction : public G4UserSteppingAction
{
	public:
		PracSteppingAction(PracEventAction* eventAction);
		virtual ~PracSteppingAction();
        
        G4double GetBindingEnergyDifference(const G4Step* step,
                                            const std::vector<const G4Track*>* vectorSecondaryTrack,
                                            const G4double energyLossInelastic);

		virtual void UserSteppingAction(const G4Step*);
	
	private:
		PracEventAction* fEventAction;
        G4LogicalVolume* fScoringVolume;
        G4double preStepKineticEnergy;
        G4bool coutmode;
};

#endif
