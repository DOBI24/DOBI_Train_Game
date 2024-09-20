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

};
