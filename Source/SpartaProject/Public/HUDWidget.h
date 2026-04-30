
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class SPARTAPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()


public:
    void SetScore(int32 InScore);
    void SetTime(int32 InTime);
    void SetHp(float InCurrentHp, float InMaxHp);

protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TimeText;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HPBar;

};
