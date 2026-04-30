#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpHUD.h"
#include "Kismet/GameplayStatics.h"


ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
    HUDClass = ASpHUD::StaticClass();

    AccumulatedSeconds = 0;

    //MaxPlayTime = 60;
    CurrentStage = 1;

    // 기본 좌표 예시 (에디터에서도 설정 가능)
    StageLocations.Add(1, FVector(0.f, 0.f, 100.f));
    StageLocations.Add(2, FVector(2000.f, 0.f, 100.f));
    StageLocations.Add(3, FVector(4000.f, 0.f, 100.f));



}

void ASpartaGameMode::BeginPlay()
{
    Super::BeginPlay();

    
    // 플레이어 체력 초기 설정
    /*ASpartaCharacter* Player = Cast<ASpartaCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Player)
    {
        Player->CurrentHP = Player->MaxHP;
    }
    
    // HUD 초기화
    if (ASpHUD* SpHUD = Cast<ASpHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
    {
        if (Player) SpHUD->UpdateHP(Player->CurrentHP, Player->MaxHP);
        SpHUD->UpdateTime(0);
    }*/

    // 초당 체력 감소 타이머 시작
    GetWorld()->GetTimerManager().SetTimer(MainTimerHandle, this, &ThisClass::HandleMainTimerElapsed, 1.f, true);
}


void ASpartaGameMode::HandleMainTimerElapsed()
{
    AccumulatedSeconds++;

    ASpartaCharacter* Player = Cast<ASpartaCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    ASpHUD* SpHUD = Cast<ASpHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

    if (Player)
    {
        // 1. 초당 체력 1 감소
        Player->CurrentHP -= 1.0f;

        // HUD 업데이트
        if (SpHUD)
        {
            SpHUD->UpdateHP(Player->CurrentHP, Player->MaxHP);
            SpHUD->UpdateTime(AccumulatedSeconds);
        }

        // 2. 사망 체크
        if (Player->CurrentHP <= 0)
        {
            RestartGame();
            return;
        }
    }

}

// 처음부터 다시 시작

    void ASpartaGameMode::RestartGame()
    {
        CurrentStage = 1;
        AccumulatedSeconds = 0;

        
        TeleportPlayerToCurrentStage();
        UE_LOG(LogTemp, Warning, TEXT("Game Restarted!"));
    }


    void ASpartaGameMode::NextStage()
    {
        CurrentStage++;
        AccumulatedSeconds = 0;

        TeleportPlayerToCurrentStage();
        UE_LOG(LogTemp, Warning, TEXT("Stage Advanced: %d"), CurrentStage);
    }


    void ASpartaGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
    {
        GetWorld()->GetTimerManager().ClearTimer(MainTimerHandle);

        Super::EndPlay(EndPlayReason);
    }

    void ASpartaGameMode::TeleportPlayerToCurrentStage()
    {
        ASpartaCharacter* Player = Cast<ASpartaCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        if (!Player) return;

        // 1. 체력 회복
        Player->CurrentHP = Player->MaxHP;

        // 2. 정의된 좌표가 있는지 확인 후 이동
        if (StageLocations.Contains(CurrentStage))
        {
            FVector TargetLoc = StageLocations[CurrentStage];
            FRotator TargetRot = StageRotations.Contains(CurrentStage) ? StageRotations[CurrentStage] : FRotator::ZeroRotator;

            // ETeleportType::TeleportPhysics를 사용하여 물리 오류 방지
            Player->SetActorLocationAndRotation(TargetLoc, TargetRot, false, nullptr, ETeleportType::TeleportPhysics);
        }

        // 3. HUD 즉시 업데이트
        if (ASpHUD* SpHUD = Cast<ASpHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
        {
            SpHUD->UpdateHP(Player->CurrentHP, Player->MaxHP);
            SpHUD->UpdateTime(AccumulatedSeconds);
        }
    }
