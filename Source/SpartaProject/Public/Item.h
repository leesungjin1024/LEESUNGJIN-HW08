#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UCLASS()
class SPARTAPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:   // 보는 기능만 존재 수정불가
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;
           	// 에디터와 블루프린트에서 수정가능 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;
            // 클래스 기본값만 수정가능
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Components")
	float RotationSpeed;

	virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
	
};
