#include "PracRunAction.hh"
#include "PracPrimaryGeneratorAction.hh"
#include "PracDetectorConstruction.hh"

//#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4LogicalVolumeStore.hh"
//#include "G4LogicalVolume.hh"
//#include "G4UnitsTable.hh"
//#include "G4SystemOfUnits.hh"


PracRunAction::PracRunAction() : G4UserRunAction()
{
	// pass
}


PracRunAction::~PracRunAction() {}


void PracRunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "==================== Start of Run Information before start Run (Manual) ====================" << G4endl;
    G4cout << "Number of Event : " << run->GetNumberOfEvent() << G4endl;
    G4cout << "Number of Event to be Processed : " << run->GetNumberOfEventToBeProcessed() << G4endl;
    G4cout << "====================  End of Run Information before start Run (Manual)  ====================" << G4endl;
}


void PracRunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;
    
    G4cout << "==================== Start of Run Information (Manual) ====================" << G4endl;
    G4cout << "Number of Event : " << nofEvents << G4endl;
    G4cout << "Number of Event to be Processed : " << run->GetNumberOfEventToBeProcessed() << G4endl;
    G4cout << "Run ID : " << run->GetRunID() << G4endl;
    G4cout << "HCtable : "  << run->GetHCtable() << G4endl;
    G4cout << "DCtable : " << run->GetDCtable() << G4endl;
    G4cout << "Random Number Status : " << run->GetRandomNumberStatus() << G4endl;
    G4cout << "====================  End of Run Information (Manual)  ====================" << G4endl;
}
