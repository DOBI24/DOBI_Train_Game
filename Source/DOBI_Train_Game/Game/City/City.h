// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "City.generated.h"

UENUM(BlueprintType)
enum class ECity : uint8
{
	AMSTERDAM,
	ANGORA,
	ATHINA,
	BARCELONA,
	BERLIN,
	BREST,
	BRINDISI,
	BRUXELLES,
	BUCURESTI,
	BUDAPEST,
	CADIZ,
	CONSTANTINOPLE,
	DANZIG,
	DIEPPE,
	EDINBURGH,
	ERZURUM,
	ESSEN,
	FRANKFURT,
	KHARKOV,
	KOBENHAVN,
	KYIV,
	LISBOA,
	LONDON,
	MADRID,
	MARSEILLE,
	MOSKVA,
	MUNCHEN,
	PALERMO,
	PAMPLONA,
	PARIS,
	PETROGRAD,
	RIGA,
	ROMA,
	ROSTOV,
	SARAJEVO,
	SEVASTOPOL,
	SMOLENSK,
	SMYRNA,
	SOCHI,
	SOFIA,
	STOCKHOLM,
	VENEZIA,
	WARSZAWA,
	WIEN,
	WILNO,
	ZAGRAB,
	ZURICH
};

UCLASS()
class DOBI_TRAIN_GAME_API ACity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	ECity City;
};
