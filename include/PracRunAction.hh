#pragma once

#ifndef PracRunAction_h
#define PracRunAction_h

#include "G4UserRunAction.hh"
#include <vector>
#include "globals.hh"

class G4Run;

class PracRunAction : public G4UserRunAction
{
	public:
		PracRunAction();
		virtual ~PracRunAction();
        
        void PutStepLengthData(G4double stepLength);

		virtual void BeginOfRunAction(const G4Run* run);
		virtual void EndOfRunAction(const G4Run* run);

    private:
        std::vector<G4double> stepLengthData;
        G4double sumStepLength;
        G4double sqsumStepLength;
        G4double meanStepLength;
        G4double stdvStepLength;
};

#endif
