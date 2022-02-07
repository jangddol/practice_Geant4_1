#include "PracRunAction.hh"
#include "PracPrimaryGeneratorAction.hh"
#include "PracDetectorConstruction.hh"

#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include <vector>

#include "PracAnalysis.hh"

PracRunAction::PracRunAction() : G4UserRunAction(), stepLengthNumber(0), sumStepLength(0.), sqsumStepLength(0.), meanStepLength(0), stdvStepLength(0)
{
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(stepLengthNumber);
    accumulableManager->RegisterAccumulable(sumStepLength);
    accumulableManager->RegisterAccumulable(sqsumStepLength);

    G4VAnalysisManager* anaMan = G4CsvAnalysisManager::Instance();
    anaMan -> OpenFile("output");
    anaMan -> CreateNtuple("data", "data");
    anaMan -> CreateNtupleIColumn("RunID");
    anaMan -> CreateNtupleIColumn("EventID");
    anaMan -> CreateNtupleIColumn("TrackID");
    anaMan -> CreateNtupleSColumn("Particle_Name");
    anaMan -> CreateNtupleDColumn("ed");
    anaMan -> CreateNtupleDColumn("distance");
    anaMan -> FinishNtuple();
    anaMan -> CreateH1("0", "Edep", 1000, 0., 120.);
}


PracRunAction::~PracRunAction()
{
    G4VAnalysisManager* anaMan = G4CsvAnalysisManager::Instance();
    anaMan -> Write();
    anaMan -> CloseFile();
}


void PracRunAction::PutStepLengthData(G4double stepLength)
{
    stepLengthNumber += 1;
    sumStepLength += stepLength;
    sqsumStepLength += stepLength * stepLength;
}

void PracRunAction::BeginOfRunAction(const G4Run* run)
{
    runID = run->GetRunID();
    if (!(IsMaster()))
    {
        stepLengthNumber = 0;
        sumStepLength = 0;
        sqsumStepLength = 0 ;
    }

}


void PracRunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;
    
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4double mStepLengthNumber = stepLengthNumber.GetValue();
    G4double mSumStepLength = sumStepLength.GetValue();
    G4double mSqSumStepLength = sqsumStepLength.GetValue();
    
    meanStepLength = mSumStepLength / mStepLengthNumber;
    G4double stdv2StepLength = mSqSumStepLength / mStepLengthNumber - meanStepLength * meanStepLength;
    stdvStepLength = std::sqrt(stdv2StepLength);

    if (IsMaster())
    {
        G4cout << "==================== Start of Run Information (Manual) ====================" << G4endl;
        G4cout << "Run ID : " << run->GetRunID() << G4endl;
        G4cout << "Cummulated Data Number : " << mStepLengthNumber << G4endl;
        G4cout << "Mean Value of Travel Distance : " << meanStepLength << G4endl;
        G4cout << "Stdv Value of Travel Distance : " << stdvStepLength << G4endl;
        G4cout << "====================  End of Run Information (Manual)  ====================" << G4endl;
    }
}
