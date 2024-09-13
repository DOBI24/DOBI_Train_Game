// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.h"
#include "TunnelTrack.generated.h"

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API UTunnelTrack : public UTrack
{
	GENERATED_BODY()
	
public:
	UTunnelTrack();

	UTunnelTrack(const ETrack_Color& TrackColor, const ETrack_Type& TrackType);
};
