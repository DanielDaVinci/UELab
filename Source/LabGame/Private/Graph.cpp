// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"

// Sets default values
AGraph::AGraph()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
    SetRootComponent(SceneComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
    SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AGraph::BeginPlay()
{
	Super::BeginPlay();

	SetupCameraDistance();
	SpawnNodes();
    SpawnLines();
}

// Called every frame
void AGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CameraVelocity != FVector2D::ZeroVector)
	{
        FRotator addRotation = FRotator( -1 * CameraVelocity.Y, CameraVelocity.X, 0.0f) * DeltaTime * CameraSpeed;
        FRotator currentArmRotation = SpringArmComponent->GetComponentRotation();

        float newPitch = FMath::Clamp(addRotation.Pitch + currentArmRotation.Pitch, -89.0f, 89.0f);
        float newYaw = addRotation.Yaw + currentArmRotation.Yaw;
        SpringArmComponent->SetWorldRotation(FRotator(newPitch, newYaw, 0.0f));

		CameraVelocity = FVector2D::ZeroVector;
	}
}

// Called to bind functionality to input
void AGraph::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftMouseAction", IE_Pressed, this, &AGraph::OnMouseDown);
	PlayerInputComponent->BindAxis("LeftMouseMove", this, &AGraph::OnMouseMove);
}

void AGraph::SetupCameraDistance()
{
    float distance = ((float)FMath::Max(RowSize, ColumnSize) / 2.0f + 1.0f) * GridStep;
    SpringArmComponent->TargetArmLength = distance;
}

void AGraph::SpawnNodes()
{
    if (!GraphNodeExample)
        return;

	NodeArray.Init(nullptr, RowSize, ColumnSize);

	UWorld* world = GetWorld();

	float startShiftX = -1 * (float)RowSize / 2.0f * GridStep;
    float startShiftY = -1 * (float)ColumnSize / 2.0f * GridStep;
	
	for (int32 i = 0; i < RowSize; i++)
	{
		for (int32 j = 0; j < ColumnSize; j++)
		{
            FTransform transform(
				FRotator::ZeroRotator, 
				FVector(startShiftX + i * GridStep + FMath::FRandRange(-0.5f, 0.5f) * GridStep, 
					startShiftY + j * GridStep + FMath::FRandRange(-0.5f, 0.5f) * GridStep, 0.0f));

			AGraphNode* node = world->SpawnActor<AGraphNode>(GraphNodeExample, transform);
            node->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			NodeArray.Set(i, j, node);
		}
	}
}

void AGraph::SpawnLines()
{
    if (!GraphNodeExample)
        return;

	AdjMatrix.Init(0, RowSize, ColumnSize);

    UWorld* world = GetWorld();

	for (int32 i = 0; i < RowSize; i++)
	{
		for (int32 j = 0; j < ColumnSize; j++)
		{
			if (j + 1 < ColumnSize)
			{
                AGraphLine* line = world->SpawnActor<AGraphLine>(GraphLineExample);
                line->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
                line->PawnCamera = CameraComponent;

                line->Setup(NodeArray.Get(i, j)->GetActorLocation(), NodeArray.Get(i, j + 1)->GetActorLocation(), 10.0f);
			}

			if (i + 1 < RowSize)
			{
                AGraphLine* line = world->SpawnActor<AGraphLine>(GraphLineExample);
                line->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
                line->PawnCamera = CameraComponent;

                line->Setup(NodeArray.Get(i, j)->GetActorLocation(), NodeArray.Get(i + 1, j)->GetActorLocation(), 10.0f);
			}
		}
	}
}

void AGraph::OnMouseDown()
{
    GetWorld()->GetGameViewport()->GetMousePosition(LastMousePosition);
}

void AGraph::OnMouseMove(float Value)
{
    if (!Value)
        return;

    FVector2D currentMousePosition;
    GetWorld()->GetGameViewport()->GetMousePosition(currentMousePosition);

	FVector2D mouseShift = currentMousePosition - LastMousePosition;
    CameraVelocity = mouseShift.GetSafeNormal();

	LastMousePosition = currentMousePosition;
}

