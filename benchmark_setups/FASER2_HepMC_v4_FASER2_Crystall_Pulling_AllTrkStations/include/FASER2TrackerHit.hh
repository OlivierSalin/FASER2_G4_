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
/// \file eventgenerator/HepMC/HepMCEx01/include/FASER2TrackerHit.hh
/// \brief Definition of the FASER2TrackerHit class
//
//

#ifndef FASER2TrackerHit_h
#define FASER2TrackerHit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class FASER2TrackerHit : public G4VHit {
public:

  FASER2TrackerHit();
  ~FASER2TrackerHit();
  FASER2TrackerHit(const FASER2TrackerHit &right);
  const FASER2TrackerHit& operator=(const FASER2TrackerHit &right);
  G4bool operator==(const FASER2TrackerHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);

  virtual void Draw();
  virtual void Print();

  inline void SetEdep(G4double de) { fEdep = de; }
  inline G4double GetEdep() { return fEdep; }
  inline void SetPos(G4ThreeVector xyz) { fPos = xyz; }
  inline G4ThreeVector GetPos() { return fPos; }

private:
  G4double fEdep;
  G4ThreeVector fPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<FASER2TrackerHit> FASER2TrackerHitsCollection;

extern G4Allocator<FASER2TrackerHit> FASER2TrackerHitAllocator;

inline void* FASER2TrackerHit::operator new(size_t)
{
  void* aHit;
  aHit = (void *) FASER2TrackerHitAllocator.MallocSingle();
  return aHit;
}

inline void FASER2TrackerHit::operator delete(void *aHit)
{
  FASER2TrackerHitAllocator.FreeSingle((FASER2TrackerHit*) aHit);
}

#endif
