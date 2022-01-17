#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4RunManagerFactory.hh"

#include "PracDetectorConstruction.hh"
#include "PracActionInitialization.hh"



int main(int argc, char** argv)
{
	H4UIExecutive* ui = new G4UIExecutive(argc, argv);
	
	//runManager
	auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

	//Physics List - incomplete
	G4ModularPhysicsList* physicsList = new ;
	physicsList->SetVervoseLevel(1);
	runManager->SetUserInitialization(physicalList);

	// Action Initialize
	runManager->SetUserInitialization(new PracActionInitialization());

	// Detector Construction
	runManager->SetUserInitialization(new PracDetectorConstruction());
	
	// Initialize visualization
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
	
	// User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	delete visManager;
	delete runManager;
}
