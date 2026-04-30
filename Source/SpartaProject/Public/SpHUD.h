#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SpHUD.generated.h"

class UHUDWidget;
class UUserWidget;

UCLASS()
class SPARTAPROJECT_API ASpHUD : public AHUD
{
	GENERATED_BODY()

public:
    ASpHUD();

    virtual void BeginPlay() override;

    void ShowGameHUD();

    void UpdateScore(int32 InScore);

    void UpdateTime(int32 InTime);

    void UpdateHP(float InCurrentHP, float InMaxHP);

    void ShowGameOverMenu();

    void ShowMapSelectionMenu();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UHUDWidget>HUDWidgetClass;

    UPROPERTY()
    UHUDWidget* HUDWidgetInstance;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget>MenuWidgetClass;

    UPROPERTY()
    UUserWidget* MenuWidgetInstance;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> MapSelectionWidgetClass;

    UPROPERTY()
    UUserWidget* MapSelectionWidgetInstance;

    void MoveCharacterToLocation(FName TargetPointName);
};
