#include <cstdio>
#include <string>
#include <vector>
#include <cassert>

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "G4RunManagerFactory.hh"

#include "PracDetectorConstruction.hh"
#include "PracActionInitialization.hh"
#include "PracCoutModeSingleton.hh"

#include "FTFP_BERT.hh"

PracCoutModeSingleton* PracCoutModeSingleton::instance = nullptr;

int main(int argc, char** argv)
{
    G4UIsession* ter_ui = new G4UIterminal;
    G4UIExecutive* exe_ui = new G4UIExecutive(argc, argv);
    
    G4bool bUI_ter = true;
    G4bool bCout_info = false;

    PracCoutModeSingleton* coutmodeinstance = PracCoutModeSingleton::GetInstance();

    if (argc == 1)
    {
        bUI_ter = true;
    }
    else
    {
        std::vector<std::string> allArgs(argv, argv+argc);
        if (allArgs[1] == "-e")
        {
            bUI_ter = false;
        }
        else if (allArgs[1] == "-v")
        {
            bCout_info = true;
        }
        else if ((allArgs[1] == "-ve") || (allArgs[1] == "-ev"))
        {
            bUI_ter = false;
            bCout_info = true;
        }
        else
        {
            assert(true && "Wrong Command");
        }
    }

	//runManager
	auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    runManager->SetNumberOfThreads(4);

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
	
    if (bCout_info)
    {
        coutmodeinstance->SetPracCoutMode(true);
    }
    else
    {
        coutmodeinstance->SetPracCoutMode(false);
    }
	if (bUI_ter)
    {
        UImanager->ApplyCommand("/control/execute init_ter.mac");
        ter_ui->SessionStart();
    }
    else
    {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        exe_ui->SessionStart();
    }
    
	delete ter_ui;
    delete exe_ui;

	delete visManager;
	delete runManager;
}
