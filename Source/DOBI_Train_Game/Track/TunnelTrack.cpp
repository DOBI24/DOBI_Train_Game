// Fill out your copyright notice in the Description page of Project Settings.


#include "TunnelTrack.h"

UTunnelTrack::UTunnelTrack()
{
}

UTunnelTrack::UTunnelTrack(const ETrack_Color& TrackColor, const ETrack_Type& TrackType)
{
	Super(TrackColor, TrackType);
}
