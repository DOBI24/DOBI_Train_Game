// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"

UTrack::UTrack() : FieldCount(0)
{
}

bool UTrack::IsNameStableForNetworking() const
{
	return true;
}

void UTrack::AddFieldToFields(ABaseField* field)
{
	Fields.Emplace(field);
	FieldCount++;
	UE_LOG(LogAudio, Warning, TEXT("Adding successfully %d"), Fields.Num());
}

int32 UTrack::GetFieldCount()
{
	return FieldCount;
}
