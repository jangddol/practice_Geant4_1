#include "PracSteppingAction.hh"
//#include "PracEventAction.hh"
//#include "PracDetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4Event.hh"
//#include "G4RunManager.hh"
//#include "G4LogicalVolume.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction)
{
    // 밑에서 언급중인 fScoring 관련이 필요하면 아마 여기에 fScoringVolume의 초기화가 들어가야 할텐데
    // 일단 빼보고 해봅시다.
}


PracSteppingAction::~PracSteppingAction()
{
    // pass
}


void PracSteppingAction::UserSteppingAction(const G4Step*)
{
    G4cout << "Step is stepping." << G4endl;
    // 아마 fScoringVolume을 Volume이랑 비교해서 밖으로 나가면 step을 종료시키는 코드가 여기 들어가는 것 같은데
    // 일단 빼보고 해봅시다.
}
