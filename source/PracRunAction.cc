#include "PracRunAction.hh"
#include "PracPrimaryGeneratorAction.hh"
#include "PracDetectorConstruction.hh"

//#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4LogicalVolumeStore.hh"
//#include "G4LogicalVolume.hh"
//#include "G4UnitsTable.hh"
//#include "G4SystemOfUnits.hh"


PracRunAction::PracRunAction() : G4UserRunAction(), stepLengthData({}), sumStepLength(0), sqsumStepLength(0), meanStepLength(0), stdvStepLength(0)
{
	// pass
}


PracRunAction::~PracRunAction() {}


void PracRunAction::PutStepLengthData(G4double stepLength)
{
    this->stepLengthData.push_back(stepLength);
    this->sumStepLength += stepLength;
    this->sqsumStepLength += stepLength * stepLength;
    G4int datanumber = this->stepLengthData.size();
    this->meanStepLength = this->sumStepLength / datanumber;
    G4double stdv2StepLength = this->sqsumStepLength / datanumber - this->meanStepLength * meanStepLength;
    this->stdvStepLength = std::sqrt(stdv2StepLength);
}

void PracRunAction::BeginOfRunAction(const G4Run*)
{
    // pass
}


void PracRunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;
    
    G4cout << "==================== Start of Run Information (Manual) ====================" << G4endl;
    G4cout << "Run ID : " << run->GetRunID() << G4endl;
    G4cout << "Cummulated Data Number : " << stepLengthData.size() << G4endl;
    G4cout << "Mean Value of Travel Distance : " << meanStepLength << G4endl;
    G4cout << "Stdv Value of Travel Distance : " << stdvStepLength << G4endl;
    G4cout << "====================  End of Run Information (Manual)  ====================" << G4endl;
}
