#include "StageClearItem.h"
#include "SpartaCharacter.h"
#include "SpartaGameMode.h"
#include "Kismet/GameplayStatics.h"

AStageClearItem::AStageClearItem()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    // 충돌 설정: OverlapAllDynamic 혹은 Pawn만 감지하도록 설정
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

    // 델리게이트 연결
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStageClearItem::OnOverlapBegin);
}

void AStageClearItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ASpartaCharacter::StaticClass()))
    {
        ASpartaGameMode* SpartaGM = Cast<ASpartaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
        if (SpartaGM)
        {
            SpartaGM->NextStage();
            Destroy();
        }
    }
}

