#include "CDoAction_Throw.h"
#include "Global.h"
#include "CAim.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Throw::DoAction()
{
	Super::DoAction();
	
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void ACDoAction_Throw::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdelMode();
	Status->SetMove();
}

void ACDoAction_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACDoAction_Throw::OnAim()
{
	Aim->On();
}

void ACDoAction_Throw::OffAim()
{
	Aim->Off();
}