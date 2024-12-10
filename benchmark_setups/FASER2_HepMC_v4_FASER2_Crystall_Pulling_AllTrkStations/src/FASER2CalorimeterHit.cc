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
/// \file eventgenerator/HepMC/HepMCEx01/src/FASER2CalorimeterHit.cc
/// \brief Implementation of the FASER2CalorimeterHit class
//
//

#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"
#include "FASER2CalorimeterHit.hh"

G4Allocator<FASER2CalorimeterHit> FASER2CalorimeterHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2CalorimeterHit::FASER2CalorimeterHit()
 : G4VHit(), fpLogV(NULL)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2CalorimeterHit::FASER2CalorimeterHit(G4LogicalVolume* logVol,
                                         G4int z, G4int phi)
  : fZCellID(z), fPhiCellID(phi), fpLogV(logVol)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2CalorimeterHit::FASER2CalorimeterHit(const FASER2CalorimeterHit &right)
  : G4VHit()
{
  fZCellID = right.fZCellID;
  fPhiCellID = right.fPhiCellID;
  fedep = right.fedep;
  fpos = right.fpos;
  frot = right.frot;
  fpLogV = right.fpLogV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2CalorimeterHit::~FASER2CalorimeterHit()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const FASER2CalorimeterHit& FASER2CalorimeterHit::operator=
                           (const FASER2CalorimeterHit &right)
{
  fZCellID = right.fZCellID;
  fPhiCellID = right.fPhiCellID;
  fedep = right.fedep;
  fpos = right.fpos;
  frot = right.frot;
  fpLogV = right.fpLogV;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool FASER2CalorimeterHit::operator==(const FASER2CalorimeterHit &right) const
{
  return ( (fZCellID == right.fZCellID) &&
           (fPhiCellID == right.fPhiCellID) );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void FASER2CalorimeterHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

  if(pVVisManager) {
    G4Transform3D trans(frot, fpos);
    G4VisAttributes attribs;
    const G4VisAttributes* pVA = fpLogV-> GetVisAttributes();
    if ( pVA ) attribs = *pVA;
    G4Colour colour(1., 0., 0.);
    attribs.SetColour(colour);
    attribs.SetForceWireframe(false);
    attribs.SetForceSolid(true);
    pVVisManager-> Draw(*fpLogV, attribs, trans);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void FASER2CalorimeterHit::Print()
{
}
