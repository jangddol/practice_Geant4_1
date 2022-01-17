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


void PracRunAction::BeginOfRunAction(const G4Run*)
{
	// pass
}


void PracRunAction::EndOfRunAction(const G4Run*)
{
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;
}