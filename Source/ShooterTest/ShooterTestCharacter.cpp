// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ShooterTest.h"
#include "ShooterTestPlayerController.h"


void AShooterTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Create delegate to bind the DamageTaken() function 
	OnTakeAnyDamage.AddDynamic(this,&AShooterTestCharacter::OnDamageTaken);
	
	//Set the health value to maxHealth, the maxhealth can be modiffy in editor
	health = maxHealth;
	
	UpdateHUD();
	
	//Set the bone of the mesh to snap the current weapon
	GetMesh()->HideBoneByName("weapon_r",EPhysBodyOp::PBO_None);
	currentGun = GetWorld()->SpawnActor<AGun>(BGun);
	currentGun->SetOwner(this);
	currentGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	currentGun->SetOwnerController(*GetController());

}

//The constructor is called when the engine compile. If presents error is always here
AShooterTestCharacter::AShooterTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	//Set the base values of the character component
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
}

void AShooterTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterTestCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AShooterTestCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterTestCharacter::Look);
	
		//Shooting
		EnhancedInputComponent->BindAction(shootAction,ETriggerEvent::Started,this, &AShooterTestCharacter::DoShoot);
	}
	else
	{
		UE_LOG(LogShooterTest, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AShooterTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AShooterTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AShooterTestCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AShooterTestCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AShooterTestCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AShooterTestCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AShooterTestCharacter::DoShoot()
{
	//Crate a conection with the current weapon and call the function of action
	currentGun->PullTrigger();
}

//UE function to make damage at AActor
void AShooterTestCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (isAlavie)
	{
		health -= Damage;
		//GEngine->AddOnScreenDebugMessage(1,2,FColor::Red,FString::Printf(TEXT("Damage Taken %f"), health));
		UpdateHUD();
		if (health <= 0)
		{
			isAlavie = false;
			health = 0.0f;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void AShooterTestCharacter::UpdateHUD()
{
	//Get the controller of the player for use of de HUD
	AShooterTestPlayerController* playerController = Cast<AShooterTestPlayerController>(GetController());
	if (playerController)
	{
		playerController->hudWidget->SetPorcent(health/maxHealth);
	}
}
