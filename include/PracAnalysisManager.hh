#pragma once

#ifndef PRACANALYSISMANAGER_H
#define PRACANALYSUSMANAGER_H

#include "G4CsvAnalysisManager.hh"
#include "G4RootAnalysisManager.hh"

class PracAnalysisManager
{
    public:
        G4VAnalysisManager* GetInstance()
        {
            return G4CsvAnalysisManager::Instance();
            // return G4RootAnalysisManager::Instance();
        }
};

#endif
