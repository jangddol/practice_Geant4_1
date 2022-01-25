#pragma once

#ifndef PracDetectorConstruction_h
#define PracDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class PracDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		PracDetectorConstruction();
		virtual ~PracDetectorConstruction();
        
        G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;}

		virtual G4VPhysicalVolume* Construct();

    protected:
        G4LogicalVolume* fScoringVolume;
};

#endif
