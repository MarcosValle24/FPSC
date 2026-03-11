// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBBValue.h"

UBTTask_ClearBBValue::UBTTask_ClearBBValue()
{
	NodeName = TEXT("ClearValue");
}

EBTNodeResult::Type UBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& rootComp, uint8* nodeMemory)
{
	Super::ExecuteTask(rootComp, nodeMemory);

	UBlackboardComponent* blackboard =  rootComp.GetBlackboardComponent();
	
	blackboard->ClearValue(GetSelectedBlackboardKey());
	
	return EBTNodeResult::Succeeded;
}
