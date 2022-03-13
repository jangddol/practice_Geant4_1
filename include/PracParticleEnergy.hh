#pragma once

#ifndef PRACPARTICLEENERGY_H
#define PRACPARTICLEENERGY_H

#include "globals.hh"
#include "G4SystemOfUnits.hh"

class PracParticleEnergy
{
    public:
        G4double GetParticleEnergy(){return fParticleEnergy;}
        void SetParticleEnergy(const G4double energy){fParticleEnergy = energy;}

    private:
        G4double fParticleEnergy = 100 * MeV;
};

#endif
