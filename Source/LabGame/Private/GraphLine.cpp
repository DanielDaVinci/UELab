// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphLine.h"

// Sets default values
AGraphLine::AGraphLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
    SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
    StaticMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AGraphLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGraphLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PawnCamera)
	{
        FVector direction = GetTransform().InverseTransformPosition(PawnCamera->GetComponentLocation());        
		direction.Z = (PawnCamera->GetComponentLocation() - GetActorLocation()).Z;

		FRotator newRotation = StaticMeshComponent->GetRelativeRotation();

		if (direction.Y >= 0)
            newRotation.Roll = 90.0f - direction.ToOrientationRotator().Pitch;
		else
            newRotation.Roll = -90.0f + direction.ToOrientationRotator().Pitch;

		StaticMeshComponent->SetRelativeRotation(newRotation);
	}
}

void AGraphLine::Setup(const FVector& StartPos, const FVector& EndPos, const float Thickness)
{
    SetActorLocation(StartPos);

	FVector direction = EndPos - StartPos;
    SetActorRotation(direction.ToOrientationRotator());

	FVector scale(direction.Size(), Thickness, 0.0f);
	SetActorScale3D(scale);
}

