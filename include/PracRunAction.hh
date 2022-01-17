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

		virtual void BeginOfRunAction(const G4Run*);
		virtual void EndOfRunAction(const G4Run*);
};

#endif
