#include "PracDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"


PracDetectorConstruction::PracDetectorConstruction() : G4VUserDetectorConstruction() {}


PracDetectorConstruction::~PracDetectorConstruction(){}


G4VPhysicalVolume* PracDetectorConstruction::Construct()
{
	G4bool checkOverlaps = true;
    // Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// World
	G4double world_sizeXYZ = 1*m;
	G4Material* world_material = nist->FindOrBuildMaterial("G4_Galactic");

	G4Box* solidWorld = new G4Box("World",														  // name of the world
								  0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ); // size of the world

	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,      // solid
													  world_material,  // material
													  "World");        // name
	
	G4VPhysicalVolume* physWorld = new G4PVPlacement(0,               // no rotation
													 G4ThreeVector(), // at (0, 0, 0)
													 logicWorld,      // logical volume
													 "World",         // name
													 0,               // mother volume
													 false,           // no boolean operation
													 0,               // copy number
													 checkOverlaps);  // overlaps checking

	// Shape
	G4double shape_sizeXYZ = 0.1*m;
	G4Material* shape_material = nist->FindOrBuildMaterial("G4_POLYETHYLENE"); 
	G4ThreeVector shape_position = G4ThreeVector(0, 0, 0);

	G4Box* solidShape = new G4Box("Shape",                                                        // name of the Shape
								  0.5 * shape_sizeXYZ, 0.5 * shape_sizeXYZ, 0.5 * shape_sizeXYZ); // size of the Shape

	G4LogicalVolume* logicShape = new G4LogicalVolume(solidShape,     // solid
													  shape_material, // material
													  "Shape");       // name

	G4VPhysicalVolume* physShape = new G4PVPlacement(0,              // no rotation
													 shape_position, // at (0, 0, 0)
													 logicShape,     // logical volume
													 "Shape",        // name
													 logicWorld,     // mother volume
													 false,          // no boolean operation
													 0,              // copy number
													 checkOverlaps); // overlaps checking
    
    fScoringVolume = logicShape;
	// Always return the physical World
	return physWorld;
}
