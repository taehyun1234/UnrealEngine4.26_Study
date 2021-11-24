// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class UNREALSTUDY_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* _trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* _box;

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class AABWeapon> _weaponItemClass;		// 신기한 문법.... 이런건 공부해둬야할듯.

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* _effect;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* _hpBarWidget;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
			UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* pSystem);
};
