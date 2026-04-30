#include "HPPotionItem.h"
#include "SpartaCharacter.h"
#include "SpHUD.h"
#include "Kismet/GameplayStatics.h"

AHPPotionItem::AHPPotionItem()
{
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    RootComponent = CollisionSphere;

    CollisionSphere->SetSphereRadius(50.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHPPotionItem::OnOverlapBegin);
}

void AHPPotionItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ASpartaCharacter::StaticClass()))
    {
        ASpartaCharacter* Player = Cast<ASpartaCharacter>(OtherActor);
        if (Player)
        {
            // 1. 체력 회복 (최대 체력을 넘지 않도록 제한)
            Player->CurrentHP = FMath::Clamp(Player->CurrentHP + HealAmount, 0.0f, Player->MaxHP);

            // 2. HUD 업데이트
            APlayerController* PC = Cast<APlayerController>(Player->GetController());
            if (PC)
            {
                if (ASpHUD* SpHUD = Cast<ASpHUD>(PC->GetHUD()))
                {
                    SpHUD->UpdateHP(Player->CurrentHP, Player->MaxHP);
                }
            }

            // 3. 로그 출력 및 아이템 제거
            UE_LOG(LogTemp, Warning, TEXT("HP Potion consumed! Current HP: %f"), Player->CurrentHP);
            Destroy();
        }
    }
}
