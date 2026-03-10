// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterTestGameMode.h"

AShooterTestGameMode::AShooterTestGameMode()
{
	// stub
}

void AShooterTestGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AShooterTestCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEnemyAI::StaticClass(),shooterAIActors);
	
	for (auto i = 0; i < shooterAIActors.Num();i++)
	{
		AActor* temp =shooterAIActors[i];
		Cast<AEnemyAI>(temp)->StartbehaiviourTree(player);
	}
		
}
