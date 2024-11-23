// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

UENUM(BlueprintType)
enum class ECard_Color : uint8
{
	LOCOMOTIVE = 0,
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

USTRUCT(BlueprintType)
struct FWagonCard {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	ECard_Color Color;

	UPROPERTY(BlueprintReadWrite)
	int32 Amount;

	FWagonCard() : Color(ECard_Color::PINK), Amount(0) {}

	FWagonCard(ECard_Color InColor) : Color(InColor), Amount(0) {}
};

UCLASS()
class DOBI_TRAIN_GAME_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	ACard();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	ECard_Color Color;

	UFUNCTION()
	bool CreateCardStaticMesh();

};
