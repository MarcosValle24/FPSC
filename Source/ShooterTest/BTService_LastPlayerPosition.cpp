// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LastPlayerPosition.h"

UBTService_LastPlayerPosition::UBTService_LastPlayerPosition()
{
	NodeName = TEXT("Update LastKnowPlayerLocation");
}

void UBTService_LastPlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AEnemyAI* controller = Cast<AEnemyAI>( OwnerComp.GetAIOwner());
	AShooterTestCharacter* player = controller->GetPlayerCharacter();
	
	UBlackboardComponent* blackboard =  controller->GetBlackboardComponent();
	if (player)
	{
		blackboard->SetValueAsVector(GetSelectedBlackboardKey(), player->GetActorLocation());
	}
}
