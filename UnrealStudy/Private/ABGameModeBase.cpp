// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameModeBase.h"
#include "ABCharacter.h"
#include "ABPlayerController.h"

AABGameModeBase::AABGameModeBase()
{
	DefaultPawnClass = AABCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}

void AABGameModeBase::PostLogin(APlayerController* newPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(newPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}
