// Fill out your copyright notice in the Description page of Project Settings.
// Tasks are actionable behaviors (do this) that end, 
// while Services are continuous updates (check this periodically) that run in the background


#include "BTService_PlayerLocation.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	//Create a name to find in the Behavior tree
	NodeName = TEXT("Update PlayerLocation");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AEnemyAI* controller = Cast<AEnemyAI>( OwnerComp.GetAIOwner());
	AShooterTestCharacter* player = controller->GetPlayerCharacter();
	
	UBlackboardComponent* blackboard =  controller->GetBlackboardComponent();
	
	if (controller->LineOfSightTo(player))
	{
		controller->SetFocus(player);
		blackboard->SetValueAsVector(GetSelectedBlackboardKey(), player->GetActorLocation());
	}
	else
	{
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		blackboard->ClearValue(GetSelectedBlackboardKey());
	}
}

