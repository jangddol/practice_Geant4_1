#pragma once
#ifndef PracPhysicsList_H
#define PracPhysicsList_H 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class PracPhysicsList: public G4VModularPhysicsList
{
public:
  PracPhysicsList(G4int ver = 1);
  virtual ~PracPhysicsList()=default;

  PracPhysicsList(const PracPhysicsList &) = delete;
  PracPhysicsList & operator=(const PracPhysicsList &)=delete;
  
};

#endif



