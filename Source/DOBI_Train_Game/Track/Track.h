// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Track.generated.h"

UENUM()
enum class ETrack_Route : uint8
{
	EDI_LON_O,
	EDI_LON_B,
	LON_AMS,
	LON_DIE_1,
	LON_DIE_2,
	BRE_DIE,
	BRE_PAM,
	BRE_PAR,
	DIE_PAR,
	DIE_BRU,
	PAM_MAD_B,
	PAM_MAD_W,
	PAM_BAR,
	PAM_MAR,
	PAM_PAR_B,
	PAM_PAR_G,
	MAD_LIS,
	MAD_CAD,
	MAD_BAR,
	BAR_MAR,
	CAD_LIS,
	PAR_BRU_Y,
	PAR_BRU_R,
	PAR_ZUR,
	PAR_MAR,
	PAR_FRA_W,
	PAR_FRA_O,
	BRU_AMS,
	BRU_FRA,
	AMS_FRA,
	AMS_ESS,
	MAR_ZUR,
	MAR_ROM,
	ZUR_MUN,
	ZUR_VEN,
	FRA_ESS,
	FRA_BER_B,
	FRA_BER_R,
	FRA_MUN,
	ESS_KOB_1,
	ESS_KOB_2,
	ESS_BER,
	MUN_VEN,
	MUN_WIE,
	VEN_ROM,
	VEN_ZAG,
	ROM_BRI,
	ROM_PAL,
	PAL_BRI,
	PAL_SMY,
	BRI_ATH,
	WIE_ZAG,
	WIE_BUD_R,
	WIE_BUD_W,
	WIE_BER,
	WIE_WAR,
	BUD_ZAG,
	BUD_SAR,
	BUD_BUC,
	BUD_KYI,
	ZAG_SAR,
	BER_WAR_P,
	BER_WAR_Y,
	BER_DAN,
	WAR_DAN,
	WAR_KYI,
	WAR_WIL,
	DAN_RIG,
	RIG_WIL,
	RIG_PET,
	WIL_PET,
	WIL_SMO,
	WIL_KYI,
	PET_STO,
	PET_MOS,
	STO_KOB_Y,
	STO_KOB_W,
	SMO_MOS,
	SMO_KYI,
	MOS_KHA,
	KYI_KHA,
	KYI_BUC,
	KHA_ROS,
	ROS_SEV,
	ROS_SOC,
	SEV_BUC,
	SEV_SOC,
	SEV_ERZ,
	SEV_CON,
	SOC_ERZ,
	CON_ANG,
	CON_SMY,
	CON_SOF,
	CON_BUC,
	ERZ_ANG,
	ANG_SMY,
	BUC_SOF,
	SOF_SAR,
	SOF_ATH,
	ATH_SMY,
	ATH_SAR,
};

UENUM()
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
	GREEN = 8
};

UENUM()
enum class ETrack_Type : uint8
{
	NORMAL,
	TUNNEL,
	FERRY
};


class ABaseField;

UCLASS()
class DOBI_TRAIN_GAME_API UTrack : public UObject
{
	GENERATED_BODY()
	
public:
	UTrack();
	UTrack(const ETrack_Color& TrackColor, const ETrack_Type& TrackType);

	UPROPERTY()
	ETrack_Color TrackColor;

	UPROPERTY()
	ETrack_Type TrackType;
	
	UPROPERTY()
	int32 FieldCount;

	TArray<ABaseField*> Fields;

	UFUNCTION()
	void AddFieldToFields(ABaseField* field);
};
