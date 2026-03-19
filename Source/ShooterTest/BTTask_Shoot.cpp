// Fill out your copyright notice in the Description page of Project Settings.


//The BTTask is use in the Behavior Tree as an action that can perform the AI

#include "BTTask_Shoot.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& rootComp, uint8* nodeMemory)
{
	Super::ExecuteTask(rootComp, nodeMemory);
	
	//Save the controller and the player to perfom the action
	AEnemyAI* controller = Cast<AEnemyAI>(rootComp.GetAIOwner());
	AShooterTestCharacter* MyCharacter = controller->GetMyCharacter();
	
	if (controller->GetPlayerCharacter()->isAlavie)
	{
		//if the player is allive, the enemy shoot and the task is succeeded
		MyCharacter->DoShoot();
		return EBTNodeResult::Succeeded;
	}	
	return EBTNodeResult::Failed;
}
