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


void UABCharacterWidget::NativeConstruct()	// Widget�� ȣ�� ���� �����ؼ� NativeConstruct�� ���� ȣ��Ǵ���? �̷��� �˾ƾ��ҵ�.
{
	Super::NativeConstruct();
	_hpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));	// ���� �������Ʈ�� Progressbar�� �̸��� ������
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