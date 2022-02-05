#pragma once

#ifndef PRACCOUTMODESINGLETON_H
#define PRACCOUTMODESINGLETON_H


#include "globals.hh"

class PracCoutModeSingleton
{
    private:
<<<<<<< HEAD
        PracCoutModeSingleton();
=======
        PracCoutModeSingleton(){};
>>>>>>> ac5344fc3196136717d02df5a79fc375af59c22d
        PracCoutModeSingleton(const PracCoutModeSingleton& other);
        ~PracCoutModeSingleton(){};

        static PracCoutModeSingleton* instance;
        G4bool pracCoutMode;
    public:
        static PracCoutModeSingleton* GetInstance()
        {
            if (instance == NULL)
            {
                instance = new PracCoutModeSingleton;
            }
            return instance;
        }
        
        G4bool GetPracCoutMode(){return pracCoutMode;}
        void SetPracCoutMode(G4bool coutmode){pracCoutMode = coutmode;}
};

#endif
