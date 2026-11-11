#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/HUD.h"
#include "MissionLogic.h"
#include "MissionGame.generated.h"
class UStaticMeshComponent;
class USoundWave;
class UStaticMesh;
class UMaterialInterface;
UCLASS()
class MISSIONRECALL_API AMissionPawn : public APawn {
 GENERATED_BODY()
public:
 AMissionPawn();
 virtual void Tick(float Delta) override;
};
UCLASS()
class MISSIONRECALL_API AMissionMode : public AGameModeBase {
 GENERATED_BODY()
public:
 AMissionMode();
 virtual void BeginPlay() override;
 virtual void Tick(float Delta) override;
 void Action(int Symbol);
 void Restart();
 void NewSequence();
 FMissionLogic Mission;
 FRandomStream PatternRandom{2026};
 int Modality=0; // 0 visual, 1 auditory, 2 combined
 int LastCue=-1;
 float TaskSeconds=0;
 UPROPERTY() TArray<TObjectPtr<USoundWave>> Tones;
 void SaveResult();
 // 0 briefing, 1 showing pattern, 2 recall, 3 launch ready, 4 countdown/ascent, 5 won
 int Phase=0;
 float Clock=0;
 FString Status=TEXT("Welcome, astronaut. Prepare three flight systems.");
 UPROPERTY() TArray<TObjectPtr<UStaticMesh>> ShapeAssets;
 UPROPERTY() TObjectPtr<UMaterialInterface> ShapeMaterial;
 UPROPERTY() TObjectPtr<AActor> Rocket;
 UPROPERTY() TArray<TObjectPtr<UStaticMeshComponent>> Indicators;
 UStaticMeshComponent* Part(AActor* Owner,const TCHAR* Shape,FVector Location,FVector Scale,FLinearColor Color);
 void Paint(UStaticMeshComponent* Mesh,FLinearColor Color);
};
UCLASS()
class MISSIONRECALL_API AMissionHUD : public AHUD {
 GENERATED_BODY()
public:
 virtual void DrawHUD() override;
 virtual void NotifyHitBoxClick(FName BoxName) override;
 void Label(const FString& Text,float X,float Y,FLinearColor Color=FLinearColor::White,float Scale=1);
 void Button(FName Name,const FString& Text,float X,float Y,float W,FLinearColor Color);
};
