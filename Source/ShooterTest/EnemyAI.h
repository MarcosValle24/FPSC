// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterTestCharacter.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERTEST_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
private:
	AShooterTestCharacter* playerCharacter;
	
	AShooterTestCharacter* myCharacter;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* enemyTree;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
public:
	void StartbehaiviourTree(AShooterTestCharacter* character);
	
	void DeadEnemy();
	
	AShooterTestCharacter* GetPlayerCharacter() const {return playerCharacter;};
	
	AShooterTestCharacter* GetMyCharacter() const {return myCharacter;};
	
};
