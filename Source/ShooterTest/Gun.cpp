// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rootComp = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(rootComp);

	skeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	skeletalMeshComp->SetupAttachment(rootComp);
	
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
	flashParticle->Activate(true);
	if (ownerController)
	{
		FVector viewPoint;
		FRotator vewRot;
		ownerController->GetPlayerViewPoint(viewPoint, vewRot);
		
		//DrawDebugCamera(GetWorld(),viewPoint,vewRot,90,2,FColor::Red,true);
		FVector endPoint = viewPoint + vewRot.Vector()*maxRange;
		
		FHitResult hit;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(GetOwner());
		
		bool isHit = GetWorld()->LineTraceSingleByChannel(hit,viewPoint,endPoint,ECC_GameTraceChannel1,params);
		if (isHit)
		{
			//DrawDebugSphere(GetWorld(),hit.ImpactPoint,5,20,FColor::Red,true);		
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),impactParticle,hit.ImpactPoint,hit.ImpactPoint.Rotation());
			AActor* hitActor = hit.GetActor();
			if (hitActor)
			{
				UGameplayStatics::ApplyDamage(hitActor,bulletDamage,ownerController,this,UDamageType::StaticClass());
			}
		}
	}
}

void AGun::SetOwnerController(AController& c)
{
	ownerController = &c;
}



