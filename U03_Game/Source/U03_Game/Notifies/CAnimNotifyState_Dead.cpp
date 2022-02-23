#include "CAnimNotifyState_Dead.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/CActionComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


FString UCAnimNotifyState_Dead::GetNotifyName_Implementation() const
{
	return "Dead";
}

void UCAnimNotifyState_Dead::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//모든 무기의 컬리전 끄기
	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);
	
	action->OffAllCollisions();

	//캐릭터의 캡슐 끄기
	Cast<ACharacter>(MeshComp->GetOwner())->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCAnimNotifyState_Dead::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//캐릭터의 색깔 변경
	IICharacter* charcter = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(charcter);

	charcter->ChangeColor(FLinearColor::Gray);
}