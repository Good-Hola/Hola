#pragma once

#include "CoreMinimal.h"
#include "HolaTypes.generated.h"

UENUM(BlueprintType)
enum class  EWeaponType : uint8
{
	MELEE	UMETA(DisplayName = "Melee"),
	RANGED	UMETA(DisplayName = "Ranged"),
	MAX_COUNT UMETA(DisplayName = "MaxCount")
};