#pragma once

#ifndef PracActionInitialization_h
#define PracActionInitialization_h

#include "G4VUserActionInitialization.hh"

class PracActionInitialization : public G4VUserActionInitialization
{
	public:
		PracActionInitialization();
		virtual ~PracActionInitialization();

		virtual void BuildForMaster() const;
		virtual void Build() const;
};

#endif
