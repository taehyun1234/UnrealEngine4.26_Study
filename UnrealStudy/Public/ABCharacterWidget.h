// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindCharacterStat(class UABCharacterStatComponent* newCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UABCharacterStatComponent> _currentCharacterStat;

	UPROPERTY()
	class UProgressBar* _hpProgressBar;
};