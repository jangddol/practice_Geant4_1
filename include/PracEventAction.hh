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

		virtual void BeginOfEventAction(const G4Event* event);
		virtual void EndOfEventAction(const G4Event* event);
	
	private:
		PracRunAction* fRunAction;
};

#endif
