// Fill out your copyright notice in the Description page of Project Settings.


#include "NPuzzle.h"

// Sets default values
ANPuzzle::ANPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	int Array[] = { 14, 15, 8, 7,9, 6, 11, 4,3, 13, 2, 1,0, 5, 12, 10 };

	Puzzle = TArray<int>();
	Puzzle.Append(Array, ARRAY_COUNT(Array));
	Size = 4;
	Fix = 6-1;
	CurrentIndex = Puzzle.Find(0);
}

// Called when the game starts or when spawned
void ANPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ANPuzzle::GetScore(TArray<int> InPuzzle)
{
	int Score = 0;
	
	for (int i = 0; i < Size*Size; i++)
	{
		if (InPuzzle[i] != i + 1)
		{
			Score += 1;
		}
	}
	return Score;
}

int ANPuzzle::Up(TArray<int> InPuzzle)
{
	TArray<int> Temp = InPuzzle;
	int UpIndex = CurrentIndex - Size;
	if (UpIndex > 0 && UpIndex < Size*Size)
	{
		Temp.Swap(CurrentIndex, UpIndex);
		return GetScore(Temp);
	}
	else
	{
		return -1;
	}
}

int ANPuzzle::Down(TArray<int> InPuzzle)
{
	TArray<int> Temp = InPuzzle;
	int UpIndex = CurrentIndex + Size;
	if (UpIndex > 0 && UpIndex < Size*Size)
	{
		Temp.Swap(CurrentIndex, UpIndex);
		return GetScore(Temp);
	}
	else
	{
		return -1;
	}
}

int ANPuzzle::Left(TArray<int> InPuzzle)
{
	TArray<int> Temp = InPuzzle;
	int UpIndex = CurrentIndex - 1;
	if (CurrentIndex%Size!=0)
	{
		Temp.Swap(CurrentIndex, UpIndex);
		return GetScore(Temp);
	}
	else
	{
		return -1;
	}
}

int ANPuzzle::Right(TArray<int> InPuzzle)
{
	TArray<int> Temp = InPuzzle;
	int UpIndex = CurrentIndex + 1;
	if (CurrentIndex%Size!=Size-1)
	{
		Temp.Swap(CurrentIndex, UpIndex);
		return GetScore(Temp);
	}
	else
	{
		return -1;
	}
}

int ANPuzzle::DoPuzzle()
{
	int UpScore = Up(Puzzle);
	int DownScore = Down(Puzzle);
	int LeftScore = Left(Puzzle);
	int RightScore = Right(Puzzle);

	if (UpScore == -1)
	{
		UpScore = 9999;
	}

	if (DownScore == -1)
	{
		DownScore = 9999;
	}

	if (LeftScore == -1)
	{
		LeftScore = 9999;
	}

	if (RightScore == -1)
	{
		RightScore = 9999;
	}

	TArray<int> Temp = TArray<int>();
	int Array[] = { UpScore,DownScore,LeftScore,RightScore };
	Temp.Append(Array,4);

	int MinScore = FMath::Min(Temp);
	int UpIndex = CurrentIndex - Size;
	int DownIndex = CurrentIndex + Size;
	int LeftIndex = CurrentIndex - 1;
	int RightIndex = CurrentIndex + 1;
	
	if (UpScore == MinScore && UpIndex > 0 && UpIndex!=Fix)
	{
		Puzzle.Swap(CurrentIndex, UpIndex);
		Step++;
		Res += "U";
		CurrentIndex = UpIndex;
		return UpScore;
	}
	else if (DownScore == MinScore && UpIndex < Size*Size && DownIndex!=Fix)
	{
		Puzzle.Swap(CurrentIndex, DownIndex);
		Step++;
		Res += "D";
		CurrentIndex = DownIndex;
		return DownScore;
	}
	else if (LeftScore == MinScore && CurrentIndex%Size != 0 && LeftIndex!=Fix)
	{
		Puzzle.Swap(CurrentIndex, LeftIndex);
		Step++;
		Res += "L";
		CurrentIndex = LeftIndex;
		return LeftScore;
	}
	else if (RightScore == MinScore && CurrentIndex%Size != Size - 1 && RightIndex != Fix)
	{
		Puzzle.Swap(CurrentIndex, RightIndex);
		Step++;
		Res += "R";
		CurrentIndex = RightIndex;
		return RightScore;
	}
	else
	{
		return 0;
	}
}