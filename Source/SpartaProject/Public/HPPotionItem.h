// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h" // 포션은 주로 구형 충돌체를 사용합니다
#include "HPPotionItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AHPPotionItem : public AActor
{
    GENERATED_BODY()

public:
    AHPPotionItem();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* CollisionSphere;

    // 회복량 (에디터에서 수정 가능)
    UPROPERTY(EditAnywhere, Category = "Stats")
    float HealAmount = 20.0f;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
