#include "PracRunAction.hh"
#include "PracPrimaryGeneratorAction.hh"
#include "PracDetectorConstruction.hh"

#include "G4Run.hh"

#include "PracAnalysisManager.hh"

PracRunAction::PracRunAction() : G4UserRunAction() 
{
    G4VAnalysisManager* anaMan = PracAnalysisManager().GetInstance();
    anaMan -> OpenFile("output");
    anaMan -> CreateNtuple("data", "data");
    anaMan -> CreateNtupleIColumn("RunID");
    anaMan -> CreateNtupleIColumn("EventID");
    anaMan -> CreateNtupleIColumn("TrackID");
    anaMan -> CreateNtupleSColumn("Particle_Name");
    anaMan -> CreateNtupleDColumn("ed");
    anaMan -> CreateNtupleDColumn("distance");
    anaMan -> CreateNtupleDColumn("elInel");
    anaMan -> CreateNtupleDColumn("eleak");
    anaMan -> FinishNtuple();
    anaMan -> CreateH1("0", "Edep", 1000, 0., 120.);
    anaMan -> CreateH1("1", "ElInel", 1000, 0., 120.);
    anaMan -> CreateH1("2", "leak", 1000, 0., 120.);
    anaMan -> CreateH1("3", "E_tot", 1000, 0., 120.);
}


PracRunAction::~PracRunAction()
{
    G4VAnalysisManager* anaMan = PracAnalysisManager().GetInstance();
    anaMan -> Write();
    anaMan -> CloseFile();
}


void PracRunAction::BeginOfRunAction(const G4Run* run)
{
    if (IsMaster())
    {
        runID = run->GetRunID();
    }
}


void PracRunAction::EndOfRunAction(const G4Run*)
{
    // pass
}
