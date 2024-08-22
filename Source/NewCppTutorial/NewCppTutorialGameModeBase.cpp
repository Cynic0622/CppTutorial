// Fill out your copyright notice in the Description page of Project Settings.


#include "NewCppTutorialGameModeBase.h"

void ANewCppTutorialGameModeBase::InitGameState()
{
	Super::InitGameState();

	if (DefaultPawnClass == ADefaultPawn::StaticClass() || !DefaultPawnClass)
	{
		DefaultPawnClass = CustomXPCharacterClass;
	}
}
