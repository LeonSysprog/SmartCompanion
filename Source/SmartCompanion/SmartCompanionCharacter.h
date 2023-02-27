// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#pragma comment(lib, "E:\\portaudio\\build\\Release\\portaudio_static_x64.lib")
#pragma comment(lib, "E:\\vosk-api-master\\wheelhouse\\vosk-win64\\libvosk.lib")

THIRD_PARTY_INCLUDES_START
#include "E:\portaudio\include\portaudio.h"
#include "E:\vosk-api-master\wheelhouse\vosk-win64\vosk_api.h"
THIRD_PARTY_INCLUDES_END

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SmartCompanionCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS(config=Game)
class ASmartCompanionCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Flags")
	bool BattleStateFlag = false;

	UPROPERTY(VisibleAnywhere, Category = "Flags")
	bool StealthStateFlag = false;

	/** speech recognition vars **/
	VoskModel* model;
	VoskRecognizer* recognizer;
	PaStream* stream;
	std::string data;


public:
	ASmartCompanionCharacter();
	~ASmartCompanionCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

	UFUNCTION(BlueprintCallable)
	bool GetBattleStateFlag();

	UFUNCTION(BlueprintCallable)
	void SetBattleStateFlag(bool val);

	UFUNCTION(BlueprintCallable)
	bool GetStealthStateFlag();

	UFUNCTION(BlueprintCallable)
	void StealthActivate();

	UFUNCTION(BlueprintCallable)
	void StealthDeactivate();

protected:
	/** Fires a projectile. */
	void OnPrimaryAction();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void Tick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	void InitializeSpeechRecognition();
	void TickSpeechRecognition();
	void FreeSpeechRecognition();
};

