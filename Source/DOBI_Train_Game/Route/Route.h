// @Copyright Marton Pal SZTE

#pragma once

#include "../City/City.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Route.generated.h"

/**
 * 
 */

UCLASS()
class DOBI_TRAIN_GAME_API URoute : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ECity From;

	UPROPERTY()
	ECity To;

	UPROPERTY()
	int32 Point;
};
