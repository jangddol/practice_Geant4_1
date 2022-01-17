#include "PracDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4NistManager.hh"

#include "G4Box.hh"


PracDetectorConstruction::PracDetectorConstruction() : G4VUserDetectorConstruc(), fScoringVolume(0){}


PracDetectorConstruction::~PracDetectorConstruction(){}


G4VPhysicalVolume* PracDetectorConstruction::Construct()
{
	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// World
	G4double world_sizeXYZ = 1;
	G4Material* world_material = nist->FindOrBuildMaterial(); // incomplete //////////////////////////////////////////////////////////////////////

	G4Box* solidWolrd = new G4Box("World",							      // name of the world
				      0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ); // size of the world

	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, // solid
							  world_mat,  // material
							  "World");   // name
	
	G4VPhysicalVolume* physWorld = new G4PVPlacement(0,               // no rotation
							 G4ThreeVector(), // at (0, 0, 0)
							 logicWorld,      // logical volume
							 "World",         // name
							 0,               // mother volume
							 false,           // no boolean operation
							 0,               // copy number
							 true);           // overlaps checking

	// Shape
	G4double shape_sizeXYZ = 0.1;
	G4Material* shape_material = nist->FindOrBuildMaterial(); // incomplet ///////////////////////////////////////////////////////////////////////
	G4ThreeVector shape_position = G4ThreeVector(0, 0, 0);

	G4Box* solidShape = new G4Box("Shape",                                                        // name of the Shape
				      0.5 * shape_sizeXYZ, 0.5 * shape_sizeXYZ, 0.5 * shape_sizeXYZ); // size of the Shape

	G4LogicalVolume* logicShape = new G4LogicalVolume(solidShape,     // solid
							  shape_material, // material
							  "Shape");       // name

	G4VPhysicalVolume* physWorld = new G4PVPlacement(0,              // no rotation
							 shape_position, // at (0, 0, 0)
							 logicShape,     // logical volume
							 "Shape",        // name
							 logicWorld,     // mother volume
							 false,          // no boolean operation
							 0,              // copy number
							 checkOverlaps); // overlaps checking
	
	// Set Shape as scoring volume
	fScoringVolume = logicShape2;

	// Always return the physical World
	return physWorld;
}
