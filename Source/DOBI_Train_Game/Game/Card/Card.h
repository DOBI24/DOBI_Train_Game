// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

UENUM()
enum class ECard_Color : uint8
{
	PINK,
	WHITE,
	BLUE,
	YELLOW,
	ORANGE,
	BLACK,
	RED,
	GREEN,
	LOCOMOTIVE
};

USTRUCT(BlueprintType)
struct FWagonCard {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ECard_Color Color;

	FWagonCard() : Color(ECard_Color::PINK) {}

	FWagonCard(ECard_Color InColor) : Color(InColor) {}
};

UCLASS()
class DOBI_TRAIN_GAME_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

	UPROPERTY()
	ECard_Color Color;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool CreateCardStaticMesh();

};
