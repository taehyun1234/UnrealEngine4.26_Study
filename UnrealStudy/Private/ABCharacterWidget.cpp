// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacterWidget.h"
#include "ABCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UABCharacterWidget::BindCharacterStat(class UABCharacterStatComponent* newCharacterStat)
{
	ABCHECK(newCharacterStat != nullptr)

	_currentCharacterStat = newCharacterStat;

	newCharacterStat->onHpChanged.AddUObject(this, &UABCharacterWidget::UpdateHPWidget);
}


void UABCharacterWidget::NativeConstruct()	// Widget의 호출 시점 관련해서 NativeConstruct가 언제 호출되는지? 이런거 알아야할듯.
{
	Super::NativeConstruct();
	_hpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));	// 위젯 블루프린트의 Progressbar의 이름과 같도록
	ABCHECK(_hpProgressBar != nullptr);
	UpdateHPWidget();
}
void UABCharacterWidget::UpdateHPWidget()
{
	if (_currentCharacterStat.IsValid())
	{
		if (_hpProgressBar != nullptr)
		{
			_hpProgressBar->SetPercent(_currentCharacterStat->GetHPRatio());
		}
	}
}