// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TrainGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATrainGameHUD();

protected:
	virtual void BeginPlay() override;
};
