#pragma once

#ifndef PracRunAction_h
#define PracRunAction_h

#include "G4UserRuncAction.hh"
#include "globals.hh"

clas G4Run;

class PracRunAction : public G4RUserRunAction
{
	public:
		PracRunAction();
		virtual ~PracRunAction();

		virtual void BeginOfRunAction(const G4Run*);
		virtual coid EndOfRunAction(const G4Run*);
};

#endif
