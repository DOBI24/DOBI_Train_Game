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

	UFerryTrack(const ETrack_Color& TrackColor, const ETrack_Type& TrackType, const int32& FerryCount);

	UPROPERTY()
	int32 FerryCount;
};
