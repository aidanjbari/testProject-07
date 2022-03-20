#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {

}

MySensitiveDetector::~MySensitiveDetector() {

}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	G4ThreeVector momPhoton = preStepPoint->GetMomentum();
	
	G4double eDep = track->GetVertexKineticEnergy();
	
	G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	man->FillNtupleIColumn(0, 0, evt);
	man->FillNtupleDColumn(0, 1, posPhoton[0]);
	man->FillNtupleDColumn(0, 2, posPhoton[1]);
	man->FillNtupleDColumn(0, 3, posPhoton[2]);
	man->FillNtupleDColumn(0, 4, wlen);
	man->AddNtupleRow(0);
	
	man->FillNtupleIColumn(1, 0, evt);
	man->FillNtupleDColumn(1, 1, posPhoton[0]);
	man->FillNtupleDColumn(1, 2, posPhoton[1]);
	man->FillNtupleDColumn(1, 3, posPhoton[2]);
	man->AddNtupleRow(1);
	
	G4LogicalVolume *volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	
	if(volume != fScoringVolume)
		return true;
	
	if(eDep > 0.001) {
	man->FillNtupleDColumn(2, 0, eDep);
	man->AddNtupleRow(2);
	man->FillH1(0, eDep);
	}
	
	return true;
}
