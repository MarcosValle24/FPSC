// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

//Update the value of the healthBar in the blueprint, if a HUD blueprint inherit of a c++ classs
//you can name the values the same to simplify the connection
void UHUDWidget::SetPorcent(float value)
{
	if (value > 0.0f && value < 1.0f)
	{
		HealthBar->SetPercent(value);
	}
}