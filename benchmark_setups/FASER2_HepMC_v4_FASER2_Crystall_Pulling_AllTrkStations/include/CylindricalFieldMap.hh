#ifndef CYLINDRICALFIELDMAP_HH
#define CYLINDRICALFIELDMAP_HH

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

#include <vector>
#include <map>
#include <tuple>
#include <string>

class CylindricalFieldMap : public G4MagneticField {
public:
    CylindricalFieldMap(const G4String& filename, const G4String& treename = "bField");

    virtual void GetFieldValue(const G4double Point[4], G4double *Bfield) const override;

private:
    // Coordonnées discrètes de la grille
    std::vector<double> fXvals;
    std::vector<double> fYvals;
    std::vector<double> fZvals;

    // Champ B à chaque triplet (x, y, z)
    std::map<std::tuple<double, double, double>, G4ThreeVector> fFieldMap;

    // Bornes spatiales
    double fXmin, fXmax;
    double fYmin, fYmax;
    double fZmin, fZmax;

    // Statut de chargement
    bool fMapLoaded;
};

#endif