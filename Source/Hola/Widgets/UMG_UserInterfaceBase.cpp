// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_UserInterfaceBase.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UUMG_UserInterfaceBase::NativeConstruct()
{
	Super::NativeConstruct();

	CrossHair->SetVisibility(ESlateVisibility::Collapsed);
}