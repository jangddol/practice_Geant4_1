#pragma once

#ifndef PracRunAction_h
#define PracRunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <vector>
#include <algorithm>

class G4Run;

class PracRunAction : public G4UserRunAction
{
	public:
		PracRunAction();
		virtual ~PracRunAction();
        
        G4int GetRunID(){return runID;}
        
        void ManageProcessNameVector(const G4String processName)
        {
            if (std::find(processNameVector.begin(), processNameVector.end(), processName) == processNameVector.end())
            {
                processNameVector.push_back(processName);
            }
        }
        std::vector<G4String> GetProcessNameVector(){return processNameVector;}

		virtual void BeginOfRunAction(const G4Run* run);
		virtual void EndOfRunAction(const G4Run* run);

    private:
        G4int runID;
        std::vector<G4String> processNameVector;
};

#endif
