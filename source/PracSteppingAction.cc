#include "PracSteppingAction.hh"
#include "PracEventAction.hh"
#include "PracDetectorConstruction.hh"
#include "PracCoutModeSingleton.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction) : G4UserSteppingAction(), 
                                                                       fEventAction(eventAction), 
                                                                       preStepKineticEnergy(0) 
{
    PracCoutModeSingleton* coutModeSingleton = PracCoutModeSingleton::GetInstance();
    coutmode = coutModeSingleton->GetPracCoutMode();

    const PracDetectorConstruction* detectorConstruction = static_cast<const PracDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
}


PracSteppingAction::~PracSteppingAction()
{
    // pass
}


void PracSteppingAction::UserSteppingAction(const G4Step* step)
{
    
    G4ProcessManager* processManager = step->GetTrack()->GetParticleDefinition()->GetProcessManager();
    G4ProcessVector*  processList    = processManager->GetProcessList();
    G4String processNameDefinedThisStep = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
   
    const std::vector<const G4Track*>* vectorSecondaryTrack = step->GetSecondaryInCurrentStep();
    fEventAction -> ManageSecondaryKineticMap(vectorSecondaryTrack);
    
    G4int currentTrackID = step->GetTrack()->GetTrackID();
    G4double currentKineticEnergy;
    G4int preTrackID = fEventAction -> GetPreStepTrackID();
    if (preTrackID != currentTrackID)
    {
        currentKineticEnergy = fEventAction -> GetSecondaryKineticEnergy(step->GetTrack());
    }
    else
    {
        currentKineticEnergy = preStepKineticEnergy;
    }
    
    G4double nextKineticEnergy = step->GetTrack()->GetKineticEnergy();
    G4double secondaryKineticEnergy = 0;
    for (size_t i=0; i<vectorSecondaryTrack -> size(); i++)
    {
        secondaryKineticEnergy += (vectorSecondaryTrack -> at(i))->GetKineticEnergy();
    }
    G4double energyLossInelastic = currentKineticEnergy - nextKineticEnergy - secondaryKineticEnergy - step->GetTotalEnergyDeposit();
    
    if (energyLossInelastic > 1e-10)
    {
        fEventAction -> GetRunAction() -> ManageProcessNameVector(processNameDefinedThisStep);
    }

    G4double energyDifference = currentKineticEnergy - secondaryKineticEnergy - step->GetTotalEnergyDeposit() - energyLossInelastic - nextKineticEnergy;
    if (energyDifference > 1e-5 || energyDifference < -1e-5)
    {
        coutmode = true;
    }
    
    if (processNameDefinedThisStep == "protonInelastic")
    {
        G4cout << "====================" << G4endl;
        size_t trackLength = vectorSecondaryTrack->size();
        G4double alphabinding = 2 * (938.272029) + 2 * 939.565560 - 3727.379;
        G4double C12binding = 92.161753;
        G4double sumbinding = 0;
        for (size_t i=0; i < trackLength; i++)
        {
            auto particle = vectorSecondaryTrack->at(i)->GetParticleDefinition();
            
            G4double mass = particle->GetPDGMass();
            G4int Z = particle->GetAtomicNumber();
            G4int N = particle->GetAtomicMass() - Z;
            G4double m_p = 938.272029;
            G4double m_e = 0.510998950;
            G4double m_n = 939.565560;
            G4double binding = Z * (m_p) + N * m_n - mass;

            sumbinding += binding;

            G4cout << "protonInelastic  Secondary Particle : " << particle->GetParticleName() << G4endl;
            G4cout << "                                    : Mass : " << particle->GetPDGMass() << G4endl;
            G4cout << "                                    : Atomic Mass : " << particle->GetAtomicMass() << G4endl;
            G4cout << "                                    : Atomic Number : " << particle->GetAtomicNumber() << G4endl;
            G4cout << "                                    : Charge : " << particle->GetPDGCharge() << G4endl;
            G4cout << "                                    : Binding Energy : " << binding << G4endl;
        }
        G4cout << " <<<<<<<<<< Conclusion >>>>>>>>>>>>" << G4endl;
        G4cout << " C12binding - sum_binding : " << C12binding - sumbinding << G4endl;
        G4cout << " energyLossInelastic : " << energyLossInelastic << G4endl;
    }

    if (coutmode)
    {
        G4cout << "Track ID " << currentTrackID
                << " : " << particleName << " ================================================" << G4endl;
        G4cout << "Track pointer " << step->GetTrack() << G4endl;
        G4cout << "[Process]" << G4endl;
        G4cout << "  Process defined this step : " << processNameDefinedThisStep << G4endl;
        
        if ((processNameDefinedThisStep == "protonInelastic") ||
            (processNameDefinedThisStep == "alphaInelastic") ||
            (processNameDefinedThisStep == "hadElastic") ||
            (processNameDefinedThisStep == "ionInelastic"))
        {
            G4cout << "  PreStep Kinetic Energy              : " << currentKineticEnergy << G4endl;
            G4cout << "  Energy transfered to Secondary      : " << secondaryKineticEnergy << G4endl;
            G4cout << "  Energy Deposit in this Step         : " << step->GetTotalEnergyDeposit() << G4endl;
            G4cout << "  Energy Loss in 'hadElastic' process : " << energyLossInelastic << G4endl;
        }
        
        // for (size_t i=0; i<processList->size(); i++)
        // {
        //     auto process = (*processList)[i];
        //     G4cout << "    " << process->GetProcessName() << G4endl;
        //     G4cout << "            Interaction Length                : " << process->GetCurrentInteractionLength() << G4endl;
        //     G4cout << "            Number of Interation Length Left  : " << process->GetNumberOfInteractionLengthLeft() << G4endl;
        // }
        // G4cout << "Track - Position            : " << step->GetTrack()->GetPosition() << G4endl;
        G4cout << "Track - Kinetic Energy      : " << nextKineticEnergy << G4endl;
        G4cout << "Step Length                 : " << step->GetStepLength() << G4endl;
        G4cout << "Total Energy Deposit        : " << step->GetTotalEnergyDeposit() << G4endl;
        G4cout << "Energy Difference           : " << energyDifference << G4endl;
        // G4cout << "Delta Position              : " << step->GetDeltaPosition() << G4endl;
        G4cout << "=============================================================================" << G4endl;
        G4cout << G4endl;
    }
    
    G4LogicalVolume* currentLogicalVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    if (currentLogicalVolume == fScoringVolume) // In the Box 
    {
        if (fEventAction->IsInTrackIdVector(currentTrackID) == false) // If current Track never have considered
        {
            fEventAction -> AppendRunIdVector(fEventAction->GetRunAction()->GetRunID());
            fEventAction -> AppendEventIdVector(fEventAction->GetEventID());
            fEventAction -> AppendTrackIdVector(currentTrackID);
            fEventAction -> AppendParticleNameVector(particleName);
            fEventAction -> AppendEnergyDepositVector(step->GetTotalEnergyDeposit());
            // fEventAction -> AppendTravelDistanceVector(step->GetStepLength());         // True Range
            fEventAction -> AppendTravelDistanceVector(step->GetDeltaPosition().z());   // Projected Range
            fEventAction -> AppendEnergyLossInelasticVector(energyLossInelastic);
            fEventAction -> AppendEnergyLossLeakVector(0);
        }
        else // If current Track have considered
        {
            fEventAction -> AddEnergyDepositVector(step->GetTotalEnergyDeposit());
            // fEventAction -> AddTravelDistanceVector(step->GetStepLength());            // True Range
            fEventAction -> AddTravelDistanceVector(step->GetDeltaPosition().z());      // Projected Range
            fEventAction -> AddEnergyLossInelasticVector(energyLossInelastic);
        }
        fEventAction -> AddEdep(step->GetTotalEnergyDeposit());
        fEventAction -> AddElInel(energyLossInelastic);
    }
    else // Outside of the Box
    {
        fEventAction -> AddEleak(step->GetTotalEnergyDeposit());
        if ((step->IsLastStepInVolume()) && (currentTrackID != 1))
        {
            fEventAction -> AddEleak(nextKineticEnergy);
        }

        if (fEventAction->IsInTrackIdVector(currentTrackID) == false) // If current Track never have considered
        {
            fEventAction -> AppendRunIdVector(fEventAction->GetRunAction()->GetRunID());
            fEventAction -> AppendEventIdVector(fEventAction->GetEventID());
            fEventAction -> AppendTrackIdVector(currentTrackID);
            fEventAction -> AppendParticleNameVector(particleName);
            fEventAction -> AppendEnergyDepositVector(0);
            fEventAction -> AppendTravelDistanceVector(0);
            fEventAction -> AppendEnergyLossInelasticVector(0);
            
            fEventAction->AppendEnergyLossLeakVector(step->GetTotalEnergyDeposit());
            if ((step->IsLastStepInVolume()) && (currentTrackID != 1))
            {
                fEventAction -> AppendEnergyLossLeakVector(nextKineticEnergy);
            }
        }
        else // If current Track have considered
        {
            fEventAction->AddEnergyLossLeakVector(step->GetTotalEnergyDeposit());
            if ((step->IsLastStepInVolume()) && (currentTrackID != 1))
            {
                fEventAction -> AddEnergyLossLeakVector(nextKineticEnergy);
            }
        }
    }

    if (energyDifference > 1e-5 || energyDifference < -1e-5)
    {
        coutmode = false;
    }

    // transfer Kinetic Energy Information to the next step
    preStepKineticEnergy = nextKineticEnergy;
    fEventAction -> SetPreStepTrackID(currentTrackID);
}
