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
    anaMan -> CreateNtupleDColumn("BEdif");
    anaMan -> FinishNtuple();
    anaMan -> CreateH1("0", "Energy Deposit", 1000, 0., 120.);
    anaMan -> CreateH1("1", "Energy Loss in Inelastic", 1000, -20., 120.);
    anaMan -> CreateH1("2", "Energy Leak", 1000, 0., 120.);
    anaMan -> CreateH1("3", "Total Energy Loss", 1000, 0., 120.);
    anaMan -> CreateH1("4", "Energy Loss By E=mc^2", 1000, -20., 120.);
    anaMan -> CreateH1("5", "ElInel - ElBM", 1000, -20., 20.);
    anaMan -> CreateH1("6", "Edep + ElBM + leak", 1000, 0., 120.);
    anaMan -> CreateH2("0", "Edep vs ElInel", 1000, 0., 120., 1000, 0., 120.);
    anaMan -> CreateH2("1", "ElInel vs ElBM", 1000, 0., 120., 1000, 0., 120.);
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
    processNameVector = {};
}


void PracRunAction::EndOfRunAction(const G4Run*)
{
    for (size_t i=0; i<processNameVector.size(); i++)
    {
        G4cout << " processName : " << processNameVector.at(i) << G4endl;
    }
    G4cout << "Total : " << processNameVector.size() << G4endl;
}
