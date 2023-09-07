// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphNode.generated.h"

UCLASS()
class LABGAME_API AGraphNode : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;

public:	
	// Sets default values for this actor's properties
	AGraphNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
