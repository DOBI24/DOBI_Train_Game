// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ETrack_Color : uint8
{
	NO_COLOR = 0,
	PINK = 1,
	WHITE = 2,
	BLUE = 3,
	YELLOW = 4,
	ORANGE = 5,
	BLACK = 6,
	RED = 7,
	GREEN = 8,
	DEFAULT_VALUE = 9
};

UENUM(BlueprintType)
enum class ETrack_Type : uint8
{
	NORMAL,
	TUNNEL,
	FERRY
};
