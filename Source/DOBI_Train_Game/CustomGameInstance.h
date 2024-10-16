// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FString InputName;
};
