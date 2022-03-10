#include "CDoAction_Tornado.h"
#include "Global.h"
#include "CAttachment.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Characters/CEnemy.h"

void ACDoAction_Tornado::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Tornado"))
		{
			Box =  CHelpers::GetComponent<UBoxComponent>(actor);
			break;
		}
	}
}

void ACDoAction_Tornado::DoAction()
{
	Super::DoAction();

	CheckFalse(State->IsIdleMode());
	CheckTrue(bActive);

	State->SetActionMode();
	bActive = true;

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Tornado::Begin_DoAction()
{
	Super::Begin_DoAction();

	Attached = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, "");
	Attached->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OnCollision();

	UKismetSystemLibrary::K2_SetTimer(this, "Hitted", HittedTime, true);
}

void ACDoAction_Tornado::End_DoAction()
{
	Super::End_DoAction();

	Status->SetMove();
	State->SetIdelMode();

	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, DestroyTime, false);
}

void ACDoAction_Tornado::Abort()
{
	Super::Abort();

	//Todo. 쳐맞으면 모든게 취소
}

void ACDoAction_Tornado::Tick(float DeltaTime)
{
	//Todo. 플레이어 주변으로 빙글빙글 돌리기
}

void ACDoAction_Tornado::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherChracter)
{
	HittedCharacters.AddUnique(InOtherChracter);
}

void ACDoAction_Tornado::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherChracter)
{
	HittedCharacters.Remove(InOtherChracter);
}

void ACDoAction_Tornado::Hitted()
{
	FDamageEvent e;

	for (ACharacter* character : HittedCharacters)
	{
		bool bDead = false;
		ACEnemy* enemy = Cast<ACEnemy>(character);
		if (!!enemy)
		{
			UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(enemy);
			bDead = state->IsDeadMode();
		}

		if (!!character && bDead == false)
		{
			character->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
			break;
		}
	}
}

void ACDoAction_Tornado::Finish()
{
	if (!!Attached)
		Attached->DestroyComponent();

	 bActive = false;


	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OffCollision();


	UKismetSystemLibrary::K2_ClearTimer(this, "Hitted");
}
