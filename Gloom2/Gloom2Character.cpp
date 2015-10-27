// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gloom2.h"
#include "Gloom2Character.h"
#include "Gloom2Projectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "UnrealNetwork.h"
#include "Gloom2PlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AGloom2Character

AGloom2Character::AGloom2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	Health = 100.f;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->AttachTo(Mesh1P, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);


	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	/*Ammo system code*/
	loadedAmmo = 30;
	ammoPool = 30;
	/*End ammo*/
}

void AGloom2Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGloom2Character, Task);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGloom2Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AGloom2Character::StartFiring);
	InputComponent->BindAction("Fire", IE_Released, this, &AGloom2Character::StopFiring);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	InputComponent->BindAxis("MoveForward", this, &AGloom2Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGloom2Character::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AGloom2Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AGloom2Character::LookUpAtRate);

	//Bind reload to key
	InputComponent->BindAction("Reload", IE_Pressed, this, &AGloom2Character::OnReload);
}

void AGloom2Character::StartFiring()
{
	PerformTask(ETaskEnum::Fire);

}

void AGloom2Character::StopFiring()
{
	PerformTask(ETaskEnum::None);

}

void AGloom2Character::PerformTask(ETaskEnum::Type NewTask)
{
	if (GetNetMode() == NM_Client)
	{
		ServerPerformTask(NewTask);
		return;
	}
	Task = NewTask;
	OnRep_Task();
}

void AGloom2Character::ServerPerformTask_Implementation(ETaskEnum::Type NewTask)
{
	PerformTask(NewTask);

}

bool AGloom2Character::ServerPerformTask_Validate(ETaskEnum::Type NewTask)
{
	return true;
}

void AGloom2Character::OnFire()
{ 
	if (Task != ETaskEnum::Fire) return;

	if (loadedAmmo > 0)
	{

		loadedAmmo--;
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			const FRotator SpawnRotation = GetViewRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();


			if (World != NULL)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<AGloom2Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}

		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
	else { return; };

	GetWorldTimerManager().SetTimer(FTimerHandle_Task, this, &AGloom2Character::OnFire, 0.3f);
}

void AGloom2Character::OnReload()
{
	if (ammoPool <= 0 || loadedAmmo >= 30) //if no reserve ammo or gun is full
	{
		return;
	}
	else if (ammoPool < (30 - loadedAmmo)) //if reserve is less than full mag, load only remaining ammo
	{
		loadedAmmo = loadedAmmo + ammoPool;
		ammoPool = 0;
	}
	else //else reload mag to full
	{
		ammoPool = ammoPool - (30 - loadedAmmo);
		loadedAmmo = 30;
	}
}


void AGloom2Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGloom2Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGloom2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGloom2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGloom2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FirstPersonCameraComponent->SetWorldRotation(GetViewRotation());

}

FRotator AGloom2Character::GetViewRotation() const
{
	if (Controller)
	{
		return Controller->GetControlRotation();
	}

	return FRotator(RemoteViewPitch / 255.f * 360.f, GetActorRotation().Yaw, 0.f);

}

void AGloom2Character::OnRep_Task()
{
	switch (Task)
	{
	case (ETaskEnum::None) :
		break;
	case (ETaskEnum::Fire) :
		OnFire();
		break;

	}

}

float AGloom2Character::TakeDamage(float DamageAmount, const FDamageEvent & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;
	if (Health < 0.f)
	{
		AGloom2PlayerController * PC = Cast<AGloom2PlayerController>(Controller);
		if (PC)
		{
			PC->OnKilled();
		}
		Destroy();
	}

	OnRep_Health();
	return DamageAmount;
}

void AGloom2Character::OnRep_Health()
{
	FirstPersonCameraComponent->PostProcessSettings.SceneFringeIntensity = 5.f - Health * 0.05f;

}