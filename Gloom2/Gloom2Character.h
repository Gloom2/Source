// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Gloom2Character.generated.h"

class UInputComponent;

// Firing Enumeration for the character
UENUM()
namespace ETaskEnum
{
	enum Type
	{
		None,
		Fire,
		Reload,
	};
}

UCLASS(config=Game)
class AGloom2Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Task replication
	UPROPERTY(ReplicatedUsing = OnRep_Task)
		TEnumAsByte<ETaskEnum::Type> Task;

	// Task timer
	FTimerHandle FTimerHandle_Task;

	// Health that is replicated to the clients
	UPROPERTY(ReplicatedUsing = OnRep_Health)
		float Health;

public:
	AGloom2Character();

	// Pull the view rotation from Character, using it for viewing other players aim
	FRotator GetViewRotation() const override;
	void Tick(float DeltaTime) override;

	// Take damage from enemy players
	float TakeDamage(float DamageAmount, const FDamageEvent & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	// Task function (UFUNCTION so the engine will recognize it)
	UFUNCTION()
		void OnRep_Task();

	// Health function for the engine
	UFUNCTION()
		void OnRep_Health();
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AGloom2Projectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/*New Code for Weapon Ammo*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		int32 loadedAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		int32 ammoPool;
	/*Ammo End*/


protected:

	// Perform the task function
	void PerformTask(ETaskEnum::Type NewTask);

	// Server performs the task
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPerformTask(ETaskEnum::Type NewTask);

	// Start firing function
	void StartFiring();

	// Stop firing function
	void StopFiring();
	
	/** Fires a projectile. */
	void OnFire();

	/** Reload Weapon */
	void OnReload();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/*struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;*/
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	//bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

