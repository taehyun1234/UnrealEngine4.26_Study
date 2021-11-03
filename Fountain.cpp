// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	_water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	_splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	RootComponent = _body;				// 액터를 대표할 루트컴포넌트를 설정한다.
	_water->SetupAttachment(_body);		// water는 body의 자식으로 붙이도록
	_light->SetupAttachment(_body);		
	_splash->SetupAttachment(_body);		


	_water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.f));
	_light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.f));
	_splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_BODY(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));

	if(SM_BODY.Succeeded())
	{
		_body->SetStaticMesh(SM_BODY.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_WATER(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	if (SM_WATER.Succeeded())
	{
		_water->SetStaticMesh(SM_BODY.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		SM_SPLASH(TEXT("ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01'"));
	if (SM_SPLASH.Succeeded())
	{
		_splash->SetTemplate(SM_SPLASH.Object);
	}
	//ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01'

}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

