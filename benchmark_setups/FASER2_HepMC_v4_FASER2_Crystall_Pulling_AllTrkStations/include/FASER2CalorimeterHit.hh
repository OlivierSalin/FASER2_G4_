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
/// \file eventgenerator/HepMC/HepMCEx01/include/FASER2CalorimeterHit.hh
/// \brief Definition of the FASER2CalorimeterHit class
//
//

#ifndef FASER2CalorimeterHit_h
#define FASER2CalorimeterHit_h 1

#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4VHit.hh"

class FASER2CalorimeterHit : public G4VHit {
public:
  FASER2CalorimeterHit();
  FASER2CalorimeterHit(G4LogicalVolume* logVol, G4int z, G4int phi);
  FASER2CalorimeterHit(const FASER2CalorimeterHit& right);

  virtual ~FASER2CalorimeterHit();

  const FASER2CalorimeterHit& operator=(const FASER2CalorimeterHit& right);
  G4bool operator==(const FASER2CalorimeterHit& right) const;

  inline void* operator new(size_t);
  inline void operator delete(void* aHit);

  virtual void Draw();
  virtual void Print();

  void SetCellID(G4int z,G4int phi);
  G4int GetZ();
  G4int GetPhi();
  void SetEdep(G4double de);
  void AddEdep(G4double de);
  G4double GetEdep();
  void SetPos(G4ThreeVector xyz);
  G4ThreeVector GetPos();
  void SetRot(G4RotationMatrix rmat);
  G4RotationMatrix GetRot();
  const G4LogicalVolume* GetLogV();

private:
  G4int fZCellID;
  G4int fPhiCellID;
  G4double fedep;
  G4ThreeVector fpos;
  G4RotationMatrix frot;
  const G4LogicalVolume* fpLogV;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void FASER2CalorimeterHit::SetCellID(G4int z,G4int phi)
 {
  fZCellID = z;
  fPhiCellID = phi;
}

inline G4int FASER2CalorimeterHit::GetZ()
{
  return fZCellID;
}

inline G4int FASER2CalorimeterHit::GetPhi()
{
  return fPhiCellID;
}

inline void FASER2CalorimeterHit::SetEdep(G4double de)
{
  fedep = de;
}

inline void FASER2CalorimeterHit::AddEdep(G4double de)
{
  fedep += de;
}

inline G4double FASER2CalorimeterHit::GetEdep()
{
  return fedep;
}

inline void FASER2CalorimeterHit::SetPos(G4ThreeVector xyz)
{
  fpos = xyz;
}

inline G4ThreeVector FASER2CalorimeterHit::GetPos()
{
  return fpos;
}

inline void FASER2CalorimeterHit::SetRot(G4RotationMatrix rmat)
{
  frot = rmat;
}

inline G4RotationMatrix FASER2CalorimeterHit::GetRot()
{
  return frot;
}

inline const G4LogicalVolume * FASER2CalorimeterHit::GetLogV()
{
  return fpLogV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<FASER2CalorimeterHit> FASER2CalorimeterHitsCollection;

extern G4Allocator<FASER2CalorimeterHit> FASER2CalorimeterHitAllocator;

inline void* FASER2CalorimeterHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) FASER2CalorimeterHitAllocator.MallocSingle();
  return aHit;
}

inline void FASER2CalorimeterHit::operator delete(void* aHit)
{
  FASER2CalorimeterHitAllocator.FreeSingle((FASER2CalorimeterHit*) aHit);
}

#endif
