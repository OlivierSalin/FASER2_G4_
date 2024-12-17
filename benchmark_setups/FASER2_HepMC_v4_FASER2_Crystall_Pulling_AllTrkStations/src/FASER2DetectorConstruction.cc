//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file eventgenerator/HepMC/HepMCEx01/src/FASER2DetectorConstruction.cc
/// \brief Implementation of the FASER2DetectorConstruction class
//
//

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "FASER2CalorimeterParametrisation.hh"
#include "FASER2CalorimeterROGeometry.hh"
#include "FASER2CalorimeterSD.hh"
#include "FASER2DetectorConstruction.hh"
#include "FASER2Field.hh"
#include "FASER2Field_CP.hh"
#include "FASER2MuonSD.hh"
#include "FASER2TrackerParametrisation.hh"
#include "FASER2TrackerSD.hh"
#include "FASER2Detector.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2DetectorConstruction::FASER2DetectorConstruction()
 : G4VUserDetectorConstruction()
{
#include "FASER2DetectorParameterDef.icc"
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2DetectorConstruction::~FASER2DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void FASER2DetectorConstruction::DefineMaterials()
{
  //-------------------------------------------------------------------------
  // Materials
  //-------------------------------------------------------------------------
  G4NistManager* nistManager = G4NistManager::Instance();
  fAir = nistManager->FindOrBuildMaterial("G4_AIR");
  fLead = nistManager->FindOrBuildMaterial("G4_Pb");
  fSilicon = nistManager->FindOrBuildMaterial("G4_Si");

  G4double a, z, density;
  G4int nel;

  // Argon gas
  a= 39.95*g/mole;
  density= 1.782e-03*g/cm3;
  fAr= new G4Material("ArgonGas", z=18., a, density);

  // Scintillator
  G4Element* elH = nistManager->FindOrBuildElement("H");
  G4Element* elC = nistManager->FindOrBuildElement("C");
  fScinti = new G4Material("Scintillator", density= 1.032*g/cm3, nel=2);
  fScinti-> AddElement(elC, 9);
  fScinti-> AddElement(elH, 10);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* FASER2DetectorConstruction::Construct()
{
  //-------------------------------------------------------------------------
  // Magnetic field
  //-------------------------------------------------------------------------

  /*
  static G4bool fieldIsInitialized = false;
  if ( !fieldIsInitialized ) {
    FASER2Field* myField = new FASER2Field;
    G4FieldManager* fieldMgr
      = G4TransportationManager::GetTransportationManager()->
        GetFieldManager();
    fieldMgr-> SetDetectorField(myField);
    fieldMgr-> CreateChordFinder(myField);
    fieldIsInitialized = true;
  }
  */
  
  //-------------------------------------------------------------------------
  // Materials
  //-------------------------------------------------------------------------
  DefineMaterials();

  //-------------------------------------------------------------------------
  // Detector geometry
  //-------------------------------------------------------------------------

  //------------------------------ experimental hall
  G4Box* experimentalHall_box =
         new G4Box("expHall_b", fexpHall_x, fexpHall_y, fexpHall_z);
  G4LogicalVolume* experimentalHall_log =
    new G4LogicalVolume(experimentalHall_box, fAir,"expHall_L", 0,0,0);
  G4VPhysicalVolume * experimentalHall_phys =
         new G4PVPlacement(0, G4ThreeVector(), experimentalHall_log,
                           "expHall_P", 0, false,0);
  G4VisAttributes* experimentalHallVisAtt =
         new G4VisAttributes(G4Colour(1.,1.,1.));
  experimentalHallVisAtt-> SetForceWireframe(true);
  experimentalHall_log-> SetVisAttributes(experimentalHallVisAtt);
  //experimentalHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());




  // CrystalPulling design
  for (int i = 0; i < fNCPMagnets; ++i) {
    // G4double offset = fCPMagnetZpos + (i - 0.5 * (fNCPMagnets - 1)) * (fCPMagnetSpacing + fCPMagnetLengthZ);
    //// fCPMagnetZpos define as the position of the beggining of the first magnet modules
    G4double offset = fCPMagnetZpos + i*fCPMagnetSpacing + i*fCPMagnetLengthZ + fCPMagnetLengthZ/2. ; 
    G4ThreeVector magPos(0., 0., offset);

    G4VSolid* magWindowSolid = new G4Tubs("MagnetWindow", 0., fCPMagnetInnerR, fCPMagnetLengthZ / 2., 0., CLHEP::twopi);
    G4VSolid* magYokeSolid = new G4Tubs("MagnetYoke", fCPMagnetInnerR, fCPMagnetOuterR, fCPMagnetLengthZ / 2., 0., CLHEP::twopi);

    G4LogicalVolume* magWindowLog = new G4LogicalVolume(magWindowSolid, fAir, "MagnetWindowLogical");
    G4LogicalVolume* magYokeLog = new G4LogicalVolume(magYokeSolid, fAir, "MagnetYokeLogical");

    new G4PVPlacement(0, magPos, magWindowLog, "MagnetWindowPhys", experimentalHall_log, false, 0);
    new G4PVPlacement(0, magPos, magYokeLog, "MagnetYokePhys", experimentalHall_log, false, 0);

    G4VisAttributes* magWindowVis = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.05));
    magWindowVis->SetForceWireframe(true);
    magWindowLog->SetVisAttributes(magWindowVis);

    G4VisAttributes* magYokeVis = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0, 0.1));
    magYokeVis->SetForceSolid(true);
    magYokeLog->SetVisAttributes(magYokeVis);

    // Set magnetic field for each magnet
    FASER2Field_CP* myField = new FASER2Field_CP;
    myField->fzmin = offset - fCPMagnetLengthZ / 2.;
    myField->fzmax = offset + fCPMagnetLengthZ / 2.;
    G4FieldManager* localFieldMgr = new G4FieldManager(myField);
    localFieldMgr->SetDetectorField(myField);
    localFieldMgr->CreateChordFinder(myField);
    magWindowLog->SetFieldManager(localFieldMgr, true);
  }

  //------------------------------ Sensitive detectors
  G4Box* SD1_box = new G4Box("SD1_box", 10*m, 10*m, 0.1*mm);
  SD1_log = new G4LogicalVolume(SD1_box, fAir,"SD1_log");
  G4VPhysicalVolume * SD1_phys = new G4PVPlacement(0, G4ThreeVector(0,0,SD1_locz), SD1_log, "SD1_phys", experimentalHall_log, false, 0);
  //SD1_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4Box* SD2_box = new G4Box("SD2_box", 10*m, 10*m, 0.1*mm);
  SD2_log = new G4LogicalVolume(SD2_box, fAir,"SD2_log");
  G4VPhysicalVolume * SD2_phys = new G4PVPlacement(0, G4ThreeVector(0,0,SD2_locz), SD2_log, "SD2_phys", experimentalHall_log, false, 0);

  G4Box* SD3_box = new G4Box("SD3_box", 10*m, 10*m, 0.1*mm);
  SD3_log = new G4LogicalVolume(SD3_box, fAir,"SD3_log");
  G4VPhysicalVolume * SD3_phys = new G4PVPlacement(0, G4ThreeVector(0,0,SD3_locz), SD3_log, "SD3_phys", experimentalHall_log, false, 0);

  G4Box* SD4_box = new G4Box("SD4_box", 10*m, 10*m, 0.1*mm);
  SD4_log = new G4LogicalVolume(SD4_box, fAir,"SD4_log");
  G4VPhysicalVolume * SD4_phys = new G4PVPlacement(0, G4ThreeVector(0,0,SD4_locz), SD4_log, "SD4_phys", experimentalHall_log, false, 0);

  G4Box* SD5_box = new G4Box("SD5_box", 10*m, 10*m, 0.1*mm);
  SD5_log = new G4LogicalVolume(SD5_box, fAir,"SD5_log");
  G4VPhysicalVolume * SD5_phys = new G4PVPlacement(0, G4ThreeVector(0,0,SD5_locz), SD5_log, "SD5_phys", experimentalHall_log, false, 0);
  
    
  //------------------------------------------------------------------
  // Digitizer modules
  //------------------------------------------------------------------

  return experimentalHall_phys;
}


void FASER2DetectorConstruction::ConstructSDandField(){
  G4SDManager *sdman = G4SDManager::GetSDMpointer();
  
  FASER2Detector* sensDet1 = new FASER2Detector("sensDet1");
  SD1_log->SetSensitiveDetector(sensDet1);
  sdman->AddNewDetector(sensDet1);

  FASER2Detector* sensDet2 = new FASER2Detector("sensDet2");
  SD2_log->SetSensitiveDetector(sensDet2);
  sdman->AddNewDetector(sensDet2);

  FASER2Detector* sensDet3 = new FASER2Detector("sensDet3");
  SD3_log->SetSensitiveDetector(sensDet3);
  sdman->AddNewDetector(sensDet3);

  FASER2Detector* sensDet4 = new FASER2Detector("sensDet4");
  SD4_log->SetSensitiveDetector(sensDet4);
  sdman->AddNewDetector(sensDet4);

  FASER2Detector* sensDet5 = new FASER2Detector("sensDet5");
  SD5_log->SetSensitiveDetector(sensDet5);
  sdman->AddNewDetector(sensDet5);


}
