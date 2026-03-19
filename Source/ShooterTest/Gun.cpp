// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "AudioMixerTrace.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rootComp = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(rootComp);

	//If ypu want to animate a weapon, is better to use skeletal mesh, otherwise use static mesh instead
	skeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	skeletalMeshComp->SetupAttachment(rootComp);
	
	//Creates a niagara particle to call it when the gun shoot
	flashParticle = CreateDefaultSubobject<UNiagaraComponent>("FlashParticle");
	flashParticle->SetupAttachment(skeletalMeshComp);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	flashParticle->Deactivate();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	//Activate the particle object at the start of the weapon
	flashParticle->Activate(true);
	
	//Activate the audio at location, use for 3D audio
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),shootSound,GetActorLocation());
	
	//OwnerController is the parent of the weapon, this could be the player or the enemy
	if (ownerController)
	{
		//Get the viewPoint of the parent and save it in this local variables
		FVector viewPoint;
		FRotator vewRot;
		ownerController->GetPlayerViewPoint(viewPoint, vewRot);
		
		//Get the end point of the lineTrace, you can use DrawDebugCamera() to draw a gizmo line
		//DrawDebugCamera(GetWorld(),viewPoint,vewRot,90,2,FColor::Red,true);
		FVector endPoint = viewPoint + vewRot.Vector()*maxRange;
		
		
		//Creates the result of the lineTrace, and create a query, this is a config of how the LineTaceInteract 
		//With the world
		FHitResult hit;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(GetOwner());
		
		//Returns if the line hit with the character or "ECC_GameTraceChannel1" this is config in the editor
		bool isHit = GetWorld()->LineTraceSingleByChannel(hit,viewPoint,endPoint,ECC_GameTraceChannel1,params);
		if (isHit)
		{
			//Spawn particles and sound at the hit position, 
			//You can use the DrawDebugSphere() function to see the point with a gizmo
			//DrawDebugSphere(GetWorld(),hit.ImpactPoint,5,20,FColor::Red,true);		
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),impactParticle,hit.ImpactPoint,hit.ImpactPoint.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),impactSound,GetActorLocation());
			
			AActor* hitActor = hit.GetActor();
			if (hitActor)
			{
				//Hurts the specified actor with generic damage.
				UGameplayStatics::ApplyDamage(hitActor,bulletDamage,ownerController,this,UDamageType::StaticClass());
			
			}
		}
	}
}

void AGun::SetOwnerController(AController& c)
{
	//Return the current actor controller
	ownerController = &c;
}



