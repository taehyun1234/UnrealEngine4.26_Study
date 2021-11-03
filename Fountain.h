// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EngineMinimal.h"
#include "Fountain.generated.h"

UCLASS()
class UNREALSTUDY_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _water;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* _light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* _splash;

	UPROPERTY(EditAnywhere, Category = ID)
	int32 _id;
};
