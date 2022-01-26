#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4RunManagerFactory.hh"

#include "PracDetectorConstruction.hh"
#include "PracActionInitialization.hh"

#include "FTFP_BERT.hh"

int main(int argc, char** argv)
{
	G4UIExecutive* ui = new G4UIExecutive(argc, argv);
	
	//runManager
	auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    // runManager->SetNumberOfThreads(1);

	//Physics List
	G4VModularPhysicsList* physicsList = new FTFP_BERT;
	physicsList->SetVerboseLevel(1);
	runManager->SetUserInitialization(physicsList);

	// Action Initialize
	runManager->SetUserInitialization(new PracActionInitialization());

	// Detector Construction
	runManager->SetUserInitialization(new PracDetectorConstruction());
	
	// Initialize visualization
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
	
	// User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	if (!ui)
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	else
	{
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}

	delete visManager;
	delete runManager;
}
