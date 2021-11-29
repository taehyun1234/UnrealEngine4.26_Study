// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AABGameModeBase();

	virtual void PostLogin(APlayerController* newPlayer) override;
};
