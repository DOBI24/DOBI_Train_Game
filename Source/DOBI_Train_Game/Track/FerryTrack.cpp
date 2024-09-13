// Fill out your copyright notice in the Description page of Project Settings.


#include "FerryTrack.h"


UFerryTrack::UFerryTrack()
{
}

UFerryTrack::UFerryTrack(const ETrack_Color& TrackColor, const ETrack_Type& TrackType, const int32& FerryCount) : FerryCount(FerryCount)
{
	Super(TrackColor, TrackType);
}
