// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GraphPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LABGAME_API AGraphPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void SetupInputComponent() override;
};
