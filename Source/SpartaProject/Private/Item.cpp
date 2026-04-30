
#include "Item.h"



// Sets default values
AItem::AItem()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

  

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Star_B.SM_Star_B"));
    if (MeshAsset.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Resources/Materials/M_Coin_A.M_Coin_A"));
    if (MaterialAsset.Succeeded())
    {
        StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
    }

    PrimaryActorTick.bCanEverTick = true;

    RotationSpeed = 90.0f;
}


void AItem::BeginPlay()
{
    Super::BeginPlay();
    /*
    SetActorLocation(FVector(300.0f, 200.0f, 10.0f)); //위치이동
    SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));// 회전
    SetActorScale3D(FVector(1.0f, 2.0f, 1.0f)); //스케일

    FVector NewLocation(300.0f, 200.0f, 10.0f);
    FRotator NewRotation(0.0f, 90.0f, 0.0f);
    FVector NewScale(1.0f, 2.0f, 1.0f);

    FTransform NewTransform(NewRotation, NewLocation, NewScale);

    SetActorTransform(NewTransform); //한번에 */
}

void AItem::Tick(float DetaTime)
{
    Super::Tick(DetaTime);
 
    if (!FMath::IsNearlyZero(RotationSpeed))
    {
        AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DetaTime, 0.0f));
    }
}

