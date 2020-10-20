// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPuzzle.generated.h"

UCLASS()
class UNREALSOMETHING_API ANPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPuzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Size;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Fix;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int Step = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Res = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> Puzzle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetScore(TArray<int> InPuzzle);
	int Up(TArray<int> InPuzzle);
	int Down(TArray<int> InPuzzle);
	int Left(TArray<int> InPuzzle);
	int Right(TArray<int> InPuzzle);

	UFUNCTION(BlueprintCallable)
	int DoPuzzle();
};
