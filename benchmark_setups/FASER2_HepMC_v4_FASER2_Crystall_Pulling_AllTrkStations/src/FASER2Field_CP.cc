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
/// \file eventgenerator/HepMC/HepMCEx01/src/FASER2Field.cc
/// \brief Implementation of the FASER2Field class
//
//

#include "G4SystemOfUnits.hh"
#include "FASER2Field_CP.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2Field_CP::FASER2Field_CP()
 : G4MagneticField()
{
  //fBz = 3.0*tesla;
  fBz = 0;
  /*
  fBy = 0;
  fBx = 1*tesla;
  */
  fBy = 0.5*tesla;
  fBx = 0;
  frmax_sq = sqr(0.8*m);
  fxmax = 100.*m;
  fxmin = -100.*m;
  fymax = 100.*m;
  fymin = -100.*m;
  fzmax = 100.*m;
  fzmin = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
FASER2Field_CP::~FASER2Field_CP()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void FASER2Field_CP::GetFieldValue(const double Point[3],double *Bfield) const
{
  /*
  Bfield[0] = 0.;
  Bfield[1] = 0.;
  if ( std::abs(Point[2]) < fzmax &&
      (sqr(Point[0])+sqr(Point[1])) < frmax_sq ) {
    Bfield[2] = fBz;
  } else {
    Bfield[2] = 0.;
  }
  */

    if ( Point[2] >= fzmin && Point[2] < fzmax &&
      (sqr(Point[0])+sqr(Point[1])) < frmax_sq ) {
      Bfield[1] = fBy;
    } else {
      Bfield[1] = 0.;
    }
    Bfield[0] = 0.;
    Bfield[2] = 0.;
}
