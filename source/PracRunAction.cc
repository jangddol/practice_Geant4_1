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
    anaMan -> FinishNtuple();
    anaMan -> CreateH1("0", "Edep", 1000, 0., 0.02);
    anaMan -> CreateH1("1", "Edep+gamma", 1000, 0., 0.02);
    anaMan -> CreateH2("0", "Edep vs. Edep+gamma", 1000, 0., 0.02, 1000, 0., 0.02, "MeV", "MeV");
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
