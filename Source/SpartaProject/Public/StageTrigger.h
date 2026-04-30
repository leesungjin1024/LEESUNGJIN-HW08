// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" // Ensure UBoxComponent is included
#include "StageTrigger.generated.h"

UCLASS()
class SPARTAPROJECT_API AStageTrigger : public AActor
{
	GENERATED_BODY()
	
public:
    AStageTrigger();

    // 충돌 감지용 박스 콜리전
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionBox;

    // 충돌 시 실행될 함수
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
