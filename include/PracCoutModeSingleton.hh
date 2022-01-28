#pragma once

#ifndef PRACCOUTMODESINGLETON_H
#define PRACCOUTMODESINGLETON_H


#include "globals.hh"

class PracCoutModeSingleton
{
    private:
        static PracCoutModeSingleton* instance;
        PracCoutModeSingleton();
        G4bool pracCoutMode;
    public:
        static PracCoutModeSingleton* GetInstance(){return instance;}
        G4bool GetPracCoutMode(){return pracCoutMode;}
        void SetPracCoutMode(G4bool coutmode){pracCoutMode = coutmode;}
};

#endif
