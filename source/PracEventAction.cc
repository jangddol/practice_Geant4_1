#include "PracEventAction.hh"
//#include "PracRunAction.hh"

#include "G4Event.hh"
//#include "G4RunManager.hh" 
	// �̰� �� �� �ִ°���?


PracEventAction::PracEventAction(PracRunAction* runAction) : G4UserEventAction(), fRunAction(runAction)
{
	// pass
}


PracEventAction::~PracEventAction() {}


void PracEventAction::BeginOfEventAction(const G4Event*)
{
    // pass
}


void PracEventAction::EndOfEventAction(const G4Event* event)
{
    G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
    G4cout << "Event ID                 : " << event->GetEventID() << G4endl;
    G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
}
