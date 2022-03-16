#include "PracSteppingAction.hh"
#include "PracEventAction.hh"
#include "PracDetectorConstruction.hh"
#include "PracCoutModeSingleton.hh"
#include "PracParticleEnergy.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4IonTable.hh"

#include "G4SystemOfUnits.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction) : G4UserSteppingAction(), 
                                                                       fEventAction(eventAction) 
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

G4double PracSteppingAction::GetBindingEnergyDifference(const G4Step* step,
                                                        const std::vector<const G4Track*>* vectorSecondaryTrack)
{
    G4String processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    
    G4double m_p = 938.272029;
    G4double m_n = 939.565560;
    
    size_t trackLength = vectorSecondaryTrack->size();
    G4double sumbinding = 0;
    G4int sumZ = 0;
    G4int sumN = 0;
    
    for (size_t i=0; i < trackLength; i++)
    {
        auto particle = vectorSecondaryTrack->at(i)->GetParticleDefinition();
        
        G4double mass = particle->GetPDGMass();
        G4int Z = particle->GetAtomicNumber();
        sumZ += Z;
        G4int N = particle->GetAtomicMass() - Z;
        sumN += N;
        G4double binding = Z * (m_p) + N * m_n - mass;
        sumbinding += binding;
    }
        
    auto incident = step->GetTrack()->GetParticleDefinition();
    G4double incident_mass = incident->GetPDGMass();
    G4int incident_Z = incident->GetAtomicNumber();
    G4int incident_N = incident->GetAtomicMass() - incident_Z;
    G4double incident_binding = incident_Z * m_p + incident_N * m_n - incident_mass;

    G4int matter_Z = sumZ - incident_Z;
    G4int matter_N = sumN - incident_N;
    G4double matter_binding = 0;
    G4double bindingEnergyDifference;
    if (trackLength == 0)
    {
        matter_binding = -incident_binding;
        bindingEnergyDifference = incident_binding + matter_binding - sumbinding;
    } 
    else
    {
        if ((processName == "compt")       ||
            (processName == "phot")        ||
            (processName == "eIoni")       ||
            (processName == "conv")        ||
            (processName == "eBrem")       ||
            (processName == "CoulombScat") ||
            (processName == "hadElastic")  ||
            (processName == "conv")        ||
            (processName == "hIoni")       ||
            (processName == "annihil"))
        {
            bindingEnergyDifference = 0;
        }
        else if (matter_Z + matter_N == 0)
        {
            matter_binding = 0;
            G4cout << "===================================================================================================" << G4endl;
            G4cout << " process Name : " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
            G4cout << " incident particle Name : " << incident->GetParticleName() << G4endl;
            for (size_t i=0; i<trackLength; i++)
            {
                auto particle = vectorSecondaryTrack->at(i)->GetParticleDefinition();

                G4cout << " secondary particle Name : " << particle->GetParticleName() << G4endl;
            }
            G4cout << "===================================================================================================" << G4endl;
            bindingEnergyDifference = incident_binding + matter_binding - sumbinding;
        }
        else
        {
            G4double matter_mass = G4IonTable::GetIonTable()->GetNucleusMass(matter_Z, matter_Z + matter_N);
            matter_binding = matter_Z * m_p + matter_N * m_n - matter_mass;
            bindingEnergyDifference = incident_binding + matter_binding - sumbinding;
        }
    }
    
    return bindingEnergyDifference; 
}


G4double PracSteppingAction::GetEnergyLossAnnihilConv(const G4Step* step)
{
    G4String processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4double m_e = 0.510999;
    G4double energyLoss = 0;
    if (processName == "conv")
    {
        energyLoss = 2 * m_e;
    }
    else if (processName == "annihil")
    {
        energyLoss = -2 * m_e;
    }
    return energyLoss;
}


G4double PracSteppingAction::GetEnergyLossByMass(const G4Step* step, const std::vector<const G4Track*>* vectorSecondaryTrack, G4double energyLossInelastic)
{
    G4double bindingEnergyDifference = GetBindingEnergyDifference(step, vectorSecondaryTrack);
    G4double energyLossAnnihilConv = GetEnergyLossAnnihilConv(step);
    G4double energyLossByMass = bindingEnergyDifference + energyLossAnnihilConv;

    G4double threshold = 0.5;
    if (energyLossByMass - energyLossInelastic < -threshold || energyLossByMass - energyLossInelastic > threshold)
    {
        G4String processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
        G4String incidentName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
        size_t trackLength = vectorSecondaryTrack->size();

        G4cout << "===========================================================" << G4endl;
        G4cout << "processName : " << processName << G4endl;
        G4cout << "incident : " << incidentName << G4endl;
        for (size_t i=0; i<trackLength; i++)
        {
            G4cout << "secondary : " << vectorSecondaryTrack->at(i)->GetParticleDefinition()->GetParticleName() << G4endl;
        }
        G4cout << "energyLossInelastic : " << energyLossInelastic << G4endl;
        G4cout << "bindingEnergyDifference : " << bindingEnergyDifference << G4endl;
        G4cout << "KineticEnergy : " << step->GetTrack()->GetKineticEnergy() << G4endl;
    }

    return energyLossByMass;
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
        currentKineticEnergy = fEventAction -> GetPreStepKineticEnergy();
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
    
    G4double energyLossByMass = PracSteppingAction::GetEnergyLossByMass(step, vectorSecondaryTrack, energyLossInelastic);
    
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
            (processNameDefinedThisStep == "ionInelastic") ||
            (processNameDefinedThisStep == "conv") ||
            (processNameDefinedThisStep == "annihil"))
        {
            G4cout << "  PreStep Kinetic Energy              : " << currentKineticEnergy << G4endl;
            G4cout << "  Energy transfered to Secondary      : " << secondaryKineticEnergy << G4endl;
        }
        
        G4cout << "Track - Kinetic Energy            : " << nextKineticEnergy << G4endl;
        G4cout << "Step Length                       : " << step->GetStepLength() << G4endl;
        G4cout << "Total Energy Deposit              : " << step->GetTotalEnergyDeposit() << G4endl;
        G4cout << "Energy Loss in Inelasticc process : " << energyLossInelastic << G4endl;
        G4cout << "Energy Loss By E=mc^2             : " << energyLossByMass << G4endl;
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
            fEventAction -> AppendEnergyLossByMassVector(energyLossByMass);
        }
        else // If current Track have considered
        {
            fEventAction -> AddEnergyDepositVector(step->GetTotalEnergyDeposit());
            // fEventAction -> AddTravelDistanceVector(step->GetStepLength());            // True Range
            fEventAction -> AddTravelDistanceVector(step->GetDeltaPosition().z());      // Projected Range
            fEventAction -> AddEnergyLossInelasticVector(energyLossInelastic);
            fEventAction -> AddEnergyLossByMassVector(energyLossByMass);
        }
        fEventAction -> AddEdep(step->GetTotalEnergyDeposit());
        fEventAction -> AddElInel(energyLossInelastic);
        fEventAction -> AddElBM(energyLossByMass);
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
            fEventAction -> AppendEnergyLossByMassVector(0);
            
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

    // transfer Kinetic Energy Information to the next step
    fEventAction -> SetPreStepKineticEnergy(nextKineticEnergy);
    fEventAction -> SetPreStepTrackID(currentTrackID);
}
