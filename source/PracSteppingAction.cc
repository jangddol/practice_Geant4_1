#include "PracSteppingAction.hh"
//#include "PracEventAction.hh"
//#include "PracDetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4Event.hh"
//#include "G4RunManager.hh"
//#include "G4LogicalVolume.hh"


PracSteppingAction::PracSteppingAction(PracEventAction* eventAction)
{
	// �ؿ��� ������� fScoring ������ �ʿ��ϸ� �Ƹ� ���⿡ fScoringVolume�� �ʱ�ȭ�� ���� ���ٵ�
	// �ϴ� ������ �غ��ô�.
}


PracSteppingAction::~PracSteppingAction() {}


void PracSteppingAction::UserSteppingAction(const G4Step*)
{
	// �Ƹ� fScoringVolume�� Volume�̶� ���ؼ� ������ ������ step�� �����Ű�� �ڵ尡 ���� ���� �� ������
	// �ϴ� ������ �غ��ô�.
}
