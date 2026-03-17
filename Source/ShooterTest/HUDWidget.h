// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERTEST_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,meta= (BindWidget))
	UProgressBar* HealthBar;
	
	UPROPERTY(EditAnywhere,meta= (BindWidget))
	UTextRenderComponent* textInfo;
	
	void SetPorcent(float value);
};
