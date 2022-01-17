#pragma once

#ifndef PracDetectorConstruction_h
#define PracDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class PracDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		PracDetectorConstruction();
		virtual ~PracDetectorConstruction();

		virtual G4VPhysicalVolume* Construct();
};

#endif
