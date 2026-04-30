// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpartaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ASpartaGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASpartaGameMode();

    void NextStage();

    void RestartGame();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
    int32 MaxPlayTime = 100;
    // 현재 스테이지 번호
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    int32 CurrentStage;


protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // 스테이지 번호를 키로, 이동할 좌표를 값으로 가집니다.
    UPROPERTY(EditAnywhere, Category = "Level Design")
    TMap<int32, FVector> StageLocations;

    UPROPERTY(EditAnywhere, Category = "Level Design")
    TMap<int32, FRotator> StageRotations;

private:
    void HandleMainTimerElapsed();
    void TeleportPlayerToCurrentStage();

    FTimerHandle MainTimerHandle;

    int32 AccumulatedSeconds;



};
