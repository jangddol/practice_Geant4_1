#pragma once

#ifndef PracRunAction_h
#define PracRunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class PracRunAction : public G4UserRunAction
{
	public:
		PracRunAction();
		virtual ~PracRunAction();
        
        G4int GetRunID(){return runID;}

		virtual void BeginOfRunAction(const G4Run* run);
		virtual void EndOfRunAction(const G4Run* run);

    private:
        G4int runID;
};

#endif
