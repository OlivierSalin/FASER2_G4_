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
/// \file eventgenerator/HepMC/HepMCEx01/src/CylindricalFieldMap.cc
/// \brief Implementation of the   CylindricalFieldMap class
#include "CylindricalFieldMap.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"

#include <TFile.h>
#include <TTree.h>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <algorithm>

CylindricalFieldMap::CylindricalFieldMap(const G4String& filename, const G4String& treename)
    : fXmin(std::numeric_limits<double>::max()),
      fXmax(std::numeric_limits<double>::lowest()),
      fYmin(std::numeric_limits<double>::max()),
      fYmax(std::numeric_limits<double>::lowest()),
      fZmin(std::numeric_limits<double>::max()),
      fZmax(std::numeric_limits<double>::lowest()),
      fMapLoaded(false)
{
    TFile* file = TFile::Open(filename.c_str(), "READ");
    if (!file || file->IsZombie()) {
        G4cerr << "Failed to open ROOT file: " << filename << G4endl;
        return;
    }

    TTree* tree = dynamic_cast<TTree*>(file->Get(treename.c_str()));
    if (!tree) {
        G4cerr << "TTree '" << treename << "' not found in file." << G4endl;
        return;
    }

    double x, y, z, Bx, By, Bz;
    tree->SetBranchAddress("x", &x);
    tree->SetBranchAddress("y", &y);
    tree->SetBranchAddress("z", &z);
    tree->SetBranchAddress("Bx", &Bx);
    tree->SetBranchAddress("By", &By);
    tree->SetBranchAddress("Bz", &Bz);

    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        // Stockage des valeurs uniques de x, y, z
        if (std::find(fXvals.begin(), fXvals.end(), x) == fXvals.end()) fXvals.push_back(x);
        if (std::find(fYvals.begin(), fYvals.end(), y) == fYvals.end()) fYvals.push_back(y);
        if (std::find(fZvals.begin(), fZvals.end(), z) == fZvals.end()) fZvals.push_back(z);

        fFieldMap[std::make_tuple(x, y, z)] = G4ThreeVector(Bx, By, Bz);

        fXmin = std::min(fXmin, x);
        fXmax = std::max(fXmax, x);
        fYmin = std::min(fYmin, y);
        fYmax = std::max(fYmax, y);
        fZmin = std::min(fZmin, z);
        fZmax = std::max(fZmax, z);
    }

    std::sort(fXvals.begin(), fXvals.end());
    std::sort(fYvals.begin(), fYvals.end());
    std::sort(fZvals.begin(), fZvals.end());

    fMapLoaded = true;
    file->Close();
}

void CylindricalFieldMap::GetFieldValue(const G4double Point[4], G4double* Bfield) const {
    if (!fMapLoaded) {
        Bfield[0] = Bfield[1] = Bfield[2] = 0.0;
        return;
    }

    double x = Point[0];
    double y = Point[1];
    double z = Point[2];

    double minDist2 = std::numeric_limits<double>::max();
    G4ThreeVector closestB(0.0, 0.0, 0.0);

    for (const auto& entry : fFieldMap) {
        const auto& [xi, yi, zi] = entry.first;
        const G4ThreeVector& Bi = entry.second;

        double dx = x - xi;
        double dy = y - yi;
        double dz = z - zi;
        double dist2 = dx * dx + dy * dy + dz * dz;

        if (dist2 < minDist2) {
            minDist2 = dist2;
            closestB = Bi;
        }
    }

    Bfield[0] = closestB.x();
    Bfield[1] = closestB.y();
    Bfield[2] = closestB.z();
}
