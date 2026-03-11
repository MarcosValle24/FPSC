// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	currentPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	SetFocus(currentPlayer);
	*/
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
/*	if (LineOfSightTo(currentPlayer))
		MoveToActor(currentPlayer,200.0f);
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}*/
}

void AEnemyAI::StartbehaiviourTree(AShooterTestCharacter* character)
{
	if (enemyTree)
	{
		myCharacter = Cast<AShooterTestCharacter>(GetPawn());

		playerCharacter = character;
		RunBehaviorTree(enemyTree);
		if (myCharacter || playerCharacter)
		{
			UBlackboardComponent* blackb = GetBlackboardComponent();
			if (blackb)
			{
				GetBlackboardComponent()->SetValueAsVector("StartLocation",myCharacter->GetActorLocation());
				GetBlackboardComponent()->SetValueAsVector("PlayerLocation",character->GetActorLocation());
			}
		}
	}
}
