#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_UserInterfaceBase.generated.h"

UCLASS()
class HOLA_API UUMG_UserInterfaceBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* HP_Bar;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* Energy_Bar;

	UPROPERTY(Meta = (BindWidget))
		class UImage* CrossHair;

public:

	
};
