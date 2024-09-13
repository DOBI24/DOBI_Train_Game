// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"

UTrack::UTrack() : FieldCount(0)
{
}

UTrack::UTrack(const ETrack_Color& TrackColor, const ETrack_Type& TrackType) : FieldCount(0), TrackColor(TrackColor), TrackType(TrackType)
{
}

void UTrack::AddFieldToFields(ABaseField* field)
{
	Fields.Emplace(field);
	FieldCount++;
	UE_LOG(LogAudio, Warning, TEXT("Adding successfully %d"), Fields.Num());
}
