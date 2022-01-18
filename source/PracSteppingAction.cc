#include "PracSteppingAction.hh"
//#include "PracEventAction.hh"
//#include "PracDetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4Event.hh"
//#include "G4RunManager.hh"
//#include "G4LogicalVolume.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction)
{
    G4cout << "Step is Constructed." << G4endl;
    // �ؿ��� ������� fScoring ������ �ʿ��ϸ� �Ƹ� ���⿡ fScoringVolume�� �ʱ�ȭ�� ���� ���ٵ�
    // �ϴ� ������ �غ��ô�.
}


PracSteppingAction::~PracSteppingAction()
{
    G4cout << "Step is Destructed." << G4endl;
}


void PracSteppingAction::UserSteppingAction(const G4Step*)
{
    G4cout << "Step is stepping." << G4endl;
    // �Ƹ� fScoringVolume�� Volume�̶� ���ؼ� ������ ������ step�� �����Ű�� �ڵ尡 ���� ���� �� ������
    // �ϴ� ������ �غ��ô�.
}
