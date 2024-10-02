// @Copyright Marton Pal SZTE


#include "Card.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACard::CreateCardStaticMesh()
{
	switch (Color)
	{
	case ECard_Color::PINK:
		break;
	case ECard_Color::WHITE:
		break;
	case ECard_Color::BLUE:
		break;
	case ECard_Color::YELLOW:
		break;
	case ECard_Color::ORANGE:
		break;
	case ECard_Color::BLACK:
		break;
	case ECard_Color::RED:
		break;
	case ECard_Color::GREEN:
		break;
	case ECard_Color::LOCOMOTIVE:
		break;
	default:
		break;
	}
	return false;
}

