// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Still in testing
	if (myCharacter && !myCharacter->isAlavie)
	{
		FTimerHandle deadTimerHandle;
		GetWorldTimerManager().SetTimer(deadTimerHandle,this,&AEnemyAI::DeadEnemy,3);
	}
}

void AEnemyAI::StartbehaiviourTree(AShooterTestCharacter* character)
{
	if (enemyTree)
	{
		//Save the character and the plater for use of the Behavior Tree
		myCharacter = Cast<AShooterTestCharacter>(GetPawn());
		playerCharacter = character;
		
		RunBehaviorTree(enemyTree);
		if (myCharacter || playerCharacter)
		{
			//Create a BlackBoard variable to save the values of the current IAController
			UBlackboardComponent* blackb = GetBlackboardComponent();
			if (blackb)
			{
				GetBlackboardComponent()->SetValueAsVector("StartLocation",myCharacter->GetActorLocation());
				GetBlackboardComponent()->SetValueAsVector("PlayerLocation",character->GetActorLocation());
			}
		}
	}
}

void AEnemyAI::DeadEnemy()
{
	Destroy(GetOwner());
}
