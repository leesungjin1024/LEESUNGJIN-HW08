
#include "StageTrigger.h"
#include "SpartaGameMode.h"
#include "SpartaCharacter.h"

AStageTrigger::AStageTrigger()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    // 플레이어와만 충돌하도록 설정
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStageTrigger::OnOverlapBegin);
}

void AStageTrigger::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult) {
    // 충돌한 대상이 플레이어 캐릭터인지 확인
    if (OtherActor && OtherActor->IsA(ASpartaCharacter::StaticClass()))
    {
        // 게임모드를 가져와서 NextStage 실행
        if (ASpartaGameMode* GM = Cast<ASpartaGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GM->NextStage();
            // 한 번 통과하면 사라지게 하거나 비활성화 (선택)
            // Destroy(); 
        }
    }
}

