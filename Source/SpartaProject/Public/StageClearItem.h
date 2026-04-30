#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StageClearItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AStageClearItem : public AActor
{
    GENERATED_BODY()

public:
    AStageClearItem();

protected:
    // 충돌 감지용 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    // 플레이어가 겹쳤을 때 실행될 함수
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
