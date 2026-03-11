// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_ClearBBValue.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERTEST_API UBTTask_ClearBBValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ClearBBValue();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& rootComp, uint8* nodeMemory) override;
};
