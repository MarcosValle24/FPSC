// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::SetPorcent(float value)
{
	if (value > 0.0f && value < 1.0f)
	{
		HealthBar->SetPercent(value);
	}
}