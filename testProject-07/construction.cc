#include "construction.hh"

//Website for refractive index : refractiveindex.info

MyDetectorConstruction::MyDetectorConstruction() {

}

MyDetectorConstruction::~MyDetectorConstruction() {

}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	G4double worldEnergy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
	G4double rindexWorld[2] = {1.0, 1.0};
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", worldEnergy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Material *CsI = new G4Material("CsI", 4.51*g/cm3, 2);
	CsI->AddElement(nist->FindOrBuildElement("Cs"), 1);
	CsI->AddElement(nist->FindOrBuildElement("I"), 1);
	
	G4double rEnergy[5] = {0.0619920965*eV, 0.247968386*eV, 1.23984193*eV, 2.47968386*eV, 4.95936772*eV };
	G4double rindexCsI[5] = {1.7280, 1.7428, 1.7576, 1.8067, 2.2094};
	G4double absLengthE[4] = {1.7712027571428572*eV, 2.0664032166666666*eV, 2.47968386*eV, 3.4440053611111114*eV};
	G4double absLength[4] = {39*cm, 34.*cm, 28.*cm, 17.5*cm};
	G4double scintEnergy[9] = {1.79687236*eV, 1.96800306*eV, 2.083767949*eV, 2.175161280*eV, 2.3843114038*eV, 2.5563751134*eV,2.637961553*eV , 2.883353325*eV, 3.542405514*eV};
	G4double scintIntensity[9] = {0.2, 0.4, 0.6, 0.8, 1.0, 0.8, 0.4, 0.2, 0.};
	
	G4MaterialPropertiesTable *mptCsI = new G4MaterialPropertiesTable();
	mptCsI->AddProperty("SCINTILLATIONCOMPONENT1", scintEnergy, scintIntensity, 9);
	mptCsI->AddProperty("RINDEX", rEnergy, rindexCsI, 5);
	mptCsI->AddProperty("ABSLENGTH", absLengthE, absLength, 4);
	mptCsI->AddConstProperty("SCINTILLATIONYIELD", 54./keV);
	mptCsI->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptCsI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1000.*ns);
	mptCsI->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	CsI->SetMaterialPropertiesTable(mptCsI);
	
	G4Tubs *solidCsI = new G4Tubs("solidCsI", 0.*cm, 5.*cm, 10.*cm, 0.*deg, 360.*deg);
	logicCsI = new G4LogicalVolume(solidCsI, CsI, "logicCsI");
	fScoringVolume = logicCsI;
	G4VPhysicalVolume *physCsI = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.3*m), logicCsI, "physCsI", logicWorld, false, 1, true);
	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicCsI->SetSensitiveDetector(sensDet);
}
