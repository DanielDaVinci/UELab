// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"

#include "GraphLine.generated.h"

UCLASS()
class LABGAME_API AGraphLine : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;

    UCameraComponent* PawnCamera;

public:	
	// Sets default values for this actor's properties
	AGraphLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Setup(const FVector& StartPos, const FVector& EndPos, const float Thickness);
};
