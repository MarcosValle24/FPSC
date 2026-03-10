// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterTestCharacter.h"
#include "EnemyAI.h"
#include "ShooterTestGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AShooterTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AShooterTestGameMode();
	
protected:
	virtual  void BeginPlay() override;
	
private:
	AShooterTestCharacter* player;
	TArray<AActor*> shooterAIActors;
};



