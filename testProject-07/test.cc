#include <iostream>

#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "physics.hh"
#include "construction.hh"
#include "action.hh"


int main(int argc, char** argv) {
	/*#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager();
	#else
		G4RunManager *runManager = new G4RunManager();
	#endif*/
	
	G4RunManager *runManager = new G4RunManager();

	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(argv[1]){
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	
	UImanager->ApplyCommand("/control/execute vis.mac");
	ui->SessionStart();
	
	return 0;
}
