// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/LineBatchComponent.h"

#include "TArray2D.h"
#include "GraphNode.h"
#include "GraphLine.h"

#include "Graph.generated.h"

UCLASS()
class LABGAME_API AGraph : public APawn
{
	GENERATED_BODY()

private:

	// Components

	UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComponent;

	// Graph parameters

	UPROPERTY(EditAnywhere)
	int32 RowSize;

	UPROPERTY(EditAnywhere)
    int32 ColumnSize;

	UPROPERTY(EditAnywhere)
    int32 GridStep;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGraphNode> GraphNodeExample;

	UPROPERTY(EditAnywhere)
    TSubclassOf<AGraphLine> GraphLineExample;

	TArray2D<AGraphNode*> NodeArray;
    TArray2D<int32> AdjMatrix;

	// Controller

	FVector2D LastMousePosition;

    FVector2D CameraVelocity;

	UPROPERTY(EditAnywhere)
	float CameraSpeed = 75.0f;

public:
	// Sets default values for this pawn's properties
	AGraph();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void SetupCameraDistance();
	void SpawnNodes();
    void SpawnLines();

	// Mouse Events
	void OnMouseDown();
	void OnMouseMove(float Value);
};
