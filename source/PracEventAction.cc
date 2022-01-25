#include "PracEventAction.hh"
//#include "PracRunAction.hh"

#include "G4Event.hh"
//#include "G4RunManager.hh" 
	// 이건 왜 들어가 있는거지?


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
    G4cout << "Number of Primary Vertex : " << event->GetNumberOfPrimaryVertex() << G4endl;
    G4cout << "HC of this Event         : " << event->GetHCofThisEvent() << G4endl;
    G4cout << "DC of this Event         : " << event->GetDCofThisEvent() << G4endl;
    G4cout << "Trajectory Container     : " << event->GetTrajectoryContainer() << G4endl;
    G4cout << "User Event Information   : " << event->GetUserInformation() << G4endl;
    // G4cout << "Random Number Status : " << event->GetRandomNumberStatus() << G4endl;
    // G4cout << "Random Number Status for Processing : " << event->GetRandomNumberStatusForProcessing() << G4endl;
    G4cout << "==================== Start of Event Information (Manual) ====================" << G4endl;
}
