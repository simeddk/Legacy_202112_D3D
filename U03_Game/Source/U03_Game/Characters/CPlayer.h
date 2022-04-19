#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Characters/ICharacter.h"
#include "GenericTeamAgentInterface.h"
#include "Components/TimelineComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class U03_GAME_API ACPlayer : public ACharacter, public IICharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "TeamID")
		uint8 TeamID = 0;

	UPROPERTY(VisibleDefaultsOnly, Category = "PostProcss")
		class UMaterialParameterCollection* ParameterCollection;

	UPROPERTY(EditAnywhere, Category = "PostProcess")
		float SpeedLineLength = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UCUserWidget_Select> SelectWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
		class UCDataAsset* Test_DataAsset;

public:
	class UCUserWidget_Select* GetSelectWidget() { return SelectWidget; }

public:
	ACPlayer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private: //SceneComponent
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UPostProcessComponent* PostProcess;

private: //ActorComponent
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCFeetComponent* Feet;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

private: //AxisEvent
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
	void OnZoom(float Axis);


private: //ActionEvent
	void OnWalk();
	void OffWalk();

	void OnEvade();
	
	UFUNCTION()	void End_Evade();

	UFUNCTION() void OnFist();
	UFUNCTION() void OnOneHand();
	UFUNCTION() void OnTwoHand();
	UFUNCTION() void OnMagicBall();
	UFUNCTION() void OnWarp();
	UFUNCTION() void OnTornado();

	void OnDoAction();

	void OnAim();
	void OffAim();

	void OnSelectAction();
	void OffSelectAction();

	void OnInteract();
	void OnScan();

private:
	void Begin_Backstep();
	void Begin_Roll();

public:
	void End_Backstep();
	void End_Roll();

private:
	void UpdateSpeedLine();

private:
	void Hitted();

	UFUNCTION()
		void Hitted_End();

	void Dead();
	void End_Dead() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void ChangeColor(FLinearColor InColor);

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void OnProgress(float Output);

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AController* DamageInstigator;
	class ACInteractDoor* InteractDoor;

protected:
	UPROPERTY(BlueprintReadOnly)
		class UCUserWidget_Select* SelectWidget;

private:
	FTimeline Timeline;
	class UCurveFloat* Curve;
	

};
