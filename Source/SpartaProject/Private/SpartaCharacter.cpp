

#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


ASpartaCharacter::ASpartaCharacter()
{
 	
	

    PrimaryActorTick.bCanEverTick = false;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = true;

    Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
    Flashlight->SetupAttachment(CameraComp);
    Flashlight->Intensity = 10000.0f;
    Flashlight->OuterConeAngle = 40.0f;
    Flashlight->AttenuationRadius = 2000.0f;
    

    // 컨트롤러 회전 사용을 끄기
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    // 2. SpringArm 설정 
    SpringArmComp->bUsePawnControlRotation = false; 
    SpringArmComp->bInheritPitch = true;
    SpringArmComp->bInheritYaw = true;
    SpringArmComp->bInheritRoll = false;

  
    NormalSpeed = 600.0f;
    SprintSpeedMultiplier = 1.5f;
    SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

}





void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Enhanced InputComponent로 캐스팅
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // IA를 가져오기 위해 현재 소유 중인 Controller를 ASpartaPlayerController로 캐스팅
        if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                // IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ASpartaCharacter::Move
                );
            }

            if (PlayerController->JumpAction)
            {
                // IA_Jump 액션 키를 "키를 누르고 있는 동안" StartJump() 호출
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ASpartaCharacter::StartJump
                );

                // IA_Jump 액션 키에서 "손을 뗀 순간" StopJump() 호출
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Completed,
                    this,
                    &ASpartaCharacter::StopJump
                );
            }

            if (PlayerController->LookAction)
            {
                // IA_Look 액션 마우스가 "움직일 때" Look() 호출
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ASpartaCharacter::Look
                );
            }

            if (PlayerController->SprintAction)
            {
                // IA_Sprint 액션 키를 "누르고 있는 동안" StartSprint() 호출
                EnhancedInput->BindAction(
                    PlayerController->SprintAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ASpartaCharacter::StartSprint
                );
                // IA_Sprint 액션 키에서 "손을 뗀 순간" StopSprint() 호출
                EnhancedInput->BindAction(
                    PlayerController->SprintAction,
                    ETriggerEvent::Completed,
                    this,
                    &ASpartaCharacter::StopSprint
                );
            }
        }
    }

}


void ASpartaCharacter::Move(const FInputActionValue& value)
{
    if (!Controller) return;

    const FVector2D MoveInput = value.Get<FVector2D>();
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    const float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
    //float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;

    
    FVector DeltaLocation = FVector(
        MoveInput.X * CurrentSpeed * DeltaTime, // 로컬 X (앞/뒤)
        MoveInput.Y * CurrentSpeed * DeltaTime, // 로컬 Y (좌/우)
        0.0f
    );

    
    AddActorLocalOffset(DeltaLocation, true);

    
    //속도 동기화
    if (DeltaTime > 0.0f)
    {
        
        float CurrentVerticalVelocity = GetCharacterMovement()->Velocity.Z;
        FVector WorldDeltaLocation = GetActorRotation().RotateVector(DeltaLocation);
        FVector NewHorizontalVelocity = WorldDeltaLocation / DeltaTime;

   
        GetCharacterMovement()->Velocity = (WorldDeltaLocation / DeltaTime) + FVector(0, 0, CurrentVerticalVelocity);
        

    }
}

void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
    // Jump 함수는 Character가 기본 제공
    if (value.Get<bool>())
    {
        Jump();
    }

}

void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
    // StopJumping 함수도 Character가 기본 제공
    if (!value.Get<bool>())
    {
        StopJumping();
    }
}

void ASpartaCharacter::Look(const FInputActionValue& value)
{
    FVector2D LookInput = value.Get<FVector2D>();
    float DeltaTime = GetWorld()->GetDeltaSeconds();

    // Get LookSensitivity from the player controller
    float LookSensitivity = 1.0f;
   

    if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
    {
        LookSensitivity = PlayerController->LookSensitivity;
    }

    if (!FMath::IsNearlyZero(LookInput.X))
    {
        float YawAmount = LookInput.X * LookSensitivity * DeltaTime;
        AddActorLocalRotation(FRotator(0.0f, YawAmount, 0.0f));
    }

    if (!FMath::IsNearlyZero(LookInput.Y))
    {
        
        //float InvertedPitchInput = LookInput.Y;
        //float PitchAmount = InvertedPitchInput * LookSensitivity * DeltaTime;
        float PitchAmount = LookInput.Y * LookSensitivity * DeltaTime;

        FRotator CurrentRot = SpringArmComp->GetRelativeRotation();
        float NewPitch = FMath::Clamp(CurrentRot.Pitch + PitchAmount, -80.0f, 80.0f);

        SpringArmComp->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));
    }
}

void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
    // Shift 키를 누른 순간 이 함수가 호출된다고 가정
    // 스프린트 속도를 적용
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}

void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
    // Shift 키를 뗀 순간 이 함수가 호출
    // 평상시 속도로 복귀
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    }
}

void ASpartaCharacter::AddHealth(float Amount)
{
    CurrentHP = FMath::Clamp(CurrentHP + Amount, 0.0f, MaxHP);
}

void ASpartaCharacter::Die()
{
    // 게임모드에게 재시작 요청
    //if (ASpartaGameMode* GM = Cast<ASpartaGameMode>(GetWorld()->GetAuthGameMode()))
    //{
    //    GM->RestartGame();
    //}
}


void ASpartaCharacter::ToggleFlashlight()
{
    if (Flashlight)
    {
        // 현재 활성화 상태를 반전시킴
        Flashlight->ToggleVisibility();
    }
}
