#include "run.hh"

MyRunAction::MyRunAction() {

}

MyRunAction::~MyRunAction() {

}

void MyRunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4int runNumber = run->GetRunID();
	
	std::stringstream strRunID;
	strRunID << runNumber;
	
	man->OpenFile("output"+strRunID.str()+".root");
	
	man->CreateNtuple("Photons", "Photons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fWlen");
	man->FinishNtuple(0);
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1);
	
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(2);
} 

void MyRunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
} 
