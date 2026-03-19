// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterTestGameMode.h"

AShooterTestGameMode::AShooterTestGameMode()
{

}

void AShooterTestGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Get the player of the level and save it in the "Player" variable
	player = Cast<AShooterTestCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	
	//Get All the enemies of the level and saves it in a Array of enemies
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEnemyAI::StaticClass(),shooterAIActors);
	
	//Loop through the enemy list and activate the behaiviour Tree
	for (AActor* temp : shooterAIActors)
	{
		Cast<AEnemyAI>(temp)->StartbehaiviourTree(player);
	}
		
}
