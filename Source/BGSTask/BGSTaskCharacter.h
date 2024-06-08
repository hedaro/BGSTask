// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BGSTaskCharacter.generated.h"


class ABGSTaskGameMode;

UCLASS(config=Game)
class ABGSTaskCharacter : public ACharacter
{
	GENERATED_BODY()

	void HandleJump(float DeltaSeconds);

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	TArray<AActor*> JumpedActors;

	bool TraceObstacles = false;

	float JumpTime = 0.0f;

	ABGSTaskGameMode* GameMode;

	float ForwardWeight = 0.1;

	float AccelerationRate = 0.01;

public:
	ABGSTaskCharacter();
	
	UPROPERTY(BlueprintReadOnly)
	bool Accelerating = false;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TEnumAsByte<ECollisionChannel> JumpableObjectsChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	float ObstacleTraceDistance = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float ForwardInputThreshold = 0.5;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void OnJumped_Implementation() override;

	virtual void Landed(const FHitResult& Hit) override;
};

