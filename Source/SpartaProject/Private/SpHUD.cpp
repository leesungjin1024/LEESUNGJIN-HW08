
#include "SpHUD.h"
#include "HUDWidget.h"
#include "GameFramework/Character.h" // 캐릭터 제어용
#include "Kismet/GameplayStatics.h"

ASpHUD::ASpHUD()
{
    static ConstructorHelpers::FClassFinder<UHUDWidget> FoundHUDWidgetClass(TEXT("/Game/BluePrint/NewFolder/WBP_SPHUD.WBP_SPHUD_C"));

       if (FoundHUDWidgetClass.Succeeded() == true)
       {
           HUDWidgetClass = FoundHUDWidgetClass.Class;
       }

     static ConstructorHelpers::FClassFinder<UUserWidget> FoundMenuWidgetClass(TEXT("/Game/BluePrint/NewFolder/WBP_Menu.WBP_Menu_C"));

       if (FoundMenuWidgetClass.Succeeded() == true)
       {
           MenuWidgetClass = FoundMenuWidgetClass.Class;
       }

       static ConstructorHelpers::FClassFinder<UUserWidget> FoundMapSelectionClass(TEXT("/Game/BluePrint/NewFolder/WBP_MapSelection.WBP_MapSelection_C"));
       if (FoundMapSelectionClass.Succeeded()== true)
       {
           MapSelectionWidgetClass = FoundMapSelectionClass.Class;
       }

}



void ASpHUD::BeginPlay()
{
    Super::BeginPlay();

    ShowGameHUD();
}

void ASpHUD::ShowGameHUD()
{
    if (HUDWidgetClass != nullptr && HUDWidgetInstance == nullptr)
    {
        HUDWidgetInstance = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
    }

    if (HUDWidgetInstance != nullptr)
    {
        HUDWidgetInstance->AddToViewport();
    }
    
}

void ASpHUD::UpdateScore(int32 InScore)
{
    if (HUDWidgetInstance != nullptr)
    {
        HUDWidgetInstance->SetScore(InScore);
    }
}

void ASpHUD::UpdateTime(int32 InTime)
{

    if (HUDWidgetInstance != nullptr)
    {
        HUDWidgetInstance->SetTime(InTime);
    }

}

void ASpHUD::UpdateHP(float InCurrentHP, float InMaxHP)
{
    if (HUDWidgetInstance != nullptr)
    {
        HUDWidgetInstance->SetHp(InCurrentHP, InMaxHP);
    } 

}

void ASpHUD::ShowGameOverMenu()
{
    if (MenuWidgetClass != nullptr && MenuWidgetInstance == nullptr)
    {
        MenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
    }

    if (MenuWidgetInstance != nullptr)
    {
        MenuWidgetInstance->AddToViewport();

        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetShowMouseCursor(true);
            PC->SetInputMode(FInputModeUIOnly());
        }
    }

}

void ASpHUD::ShowMapSelectionMenu()
{
    if (MapSelectionWidgetClass != nullptr && MapSelectionWidgetInstance == nullptr)
    {
        MapSelectionWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MapSelectionWidgetClass);
    }

    if (MapSelectionWidgetInstance != nullptr)
    {
        MapSelectionWidgetInstance->AddToViewport();

        // 마우스 커서 활성화 및 입력 모드 UI로 전환
        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetShowMouseCursor(true);
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(MapSelectionWidgetInstance->TakeWidget());
            PC->SetInputMode(InputMode);
        }
    }
}


void ASpHUD::MoveCharacterToLocation(FName TargetPointName)
{
    APlayerController* PC = GetOwningPlayerController();
    if (!PC) return;

    APawn* Pawn = PC->GetPawn();
    if (!Pawn) return;

    
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetPointName, FoundActors);

    if (FoundActors.Num() > 0)
    {
        //캐릭터 위치 이동 
        FVector TargetLocation = FoundActors[0]->GetActorLocation();
        FRotator TargetRotation = FoundActors[0]->GetActorRotation();

        Pawn->SetActorLocationAndRotation(TargetLocation, TargetRotation);

        //이동 후게임 모드로 전환
        PC->SetShowMouseCursor(false);
        PC->SetInputMode(FInputModeGameOnly());

        //맵 선택 닫기

        if (MapSelectionWidgetInstance)
        {
            MapSelectionWidgetInstance->RemoveFromParent();
        }
    }
}
