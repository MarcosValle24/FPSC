// Fill out your copyright notice in the Description page of Project Settings.


//The BTTask is use in the Behavior Tree as an action that can perform the AI
#include "BTTask_ClearBBValue.h"

UBTTask_ClearBBValue::UBTTask_ClearBBValue()
{
	NodeName = TEXT("ClearValue");
}

//This function clear the value asing in the blackboard BP
EBTNodeResult::Type UBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& rootComp, uint8* nodeMemory)
{
	Super::ExecuteTask(rootComp, nodeMemory);

	UBlackboardComponent* blackboard =  rootComp.GetBlackboardComponent();
	
	blackboard->ClearValue(GetSelectedBlackboardKey());
	
	return EBTNodeResult::Succeeded;
}
