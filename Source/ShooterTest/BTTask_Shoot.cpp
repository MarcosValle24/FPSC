// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& rootComp, uint8* nodeMemory)
{
	Super::ExecuteTask(rootComp, nodeMemory);
	
	AEnemyAI* controller = Cast<AEnemyAI>(rootComp.GetAIOwner());
	AShooterTestCharacter* MyCharacter = controller->GetMyCharacter();
	if (controller->GetPlayerCharacter()->isAlavie)
	{
		MyCharacter->DoShoot();
		return EBTNodeResult::Succeeded;
	}	
	return EBTNodeResult::Failed;
}
