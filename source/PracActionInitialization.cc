#include "PracActionInitialization.hh"
#include "PracPrimaryGeneratorAction.hh"
#include "PracRunAction.hh"
#include "PracEventAction.hh"
#include "PracSteppingAction.hh"

PracActionInitialization::PracActionInitialization() : G4VUserActionInitialization() {}


PracActionInitialization::~PracActionInitialization() {}


void PracActionInitialization::BuildForMaster() const
{
	PracRunAction* runAction = new PracRunAction;
	SetUserAction(runAction);
}


void PracActionInitialization::Build() const
{
	SetUserAction(new PracPrimaryGeneratorAction);

	PracRunAction* runAction = new PracRunAction;
	SetUserAction(runAction);

	PracEventAction* eventAction = new PracEventAction(runAction);
	SetUserAction(eventAction);

	SetUserAction(new PracSteppingAction(eventAction));
}