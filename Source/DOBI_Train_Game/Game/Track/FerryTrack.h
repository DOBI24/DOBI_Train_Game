// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.h"
#include "FerryTrack.generated.h"

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API UFerryTrack : public UTrack
{
	GENERATED_BODY()
	
public:
	UFerryTrack();

	UPROPERTY()
	int32 FerryCount;
};