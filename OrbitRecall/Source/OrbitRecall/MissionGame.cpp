#include "MissionGame.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/Canvas.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Components/LightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "InputCoreTypes.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

static const FLinearColor Navy(.015f,.03f,.07f), Cyan(.05f,.7f,1.f), Orange(1.f,.3f,.04f);
static const TCHAR* Systems[]={TEXT("FUEL ROUTING"),TEXT("NAVIGATION"),TEXT("LIFE SUPPORT")};
static const TCHAR* Symbols[]={TEXT("A / 1"),TEXT("B / 2"),TEXT("C / 3"),TEXT("D / 4")};
AMissionPawn::AMissionPawn() {
 PrimaryActorTick.bCanEverTick=true;
 RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
 auto Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
 Camera->SetupAttachment(RootComponent);
 Camera->SetRelativeLocation(FVector(-1250,-1500,1100));
 Camera->SetRelativeRotation(FRotator(-24,50,0));
 AutoPossessPlayer=EAutoReceiveInput::Player0;
}
void AMissionPawn::Tick(float Delta) {
 Super::Tick(Delta);
 auto PC=Cast<APlayerController>(GetController()); if(!PC) return;
 // Keep the astronaut on the launch apron. Puzzle actions work anywhere on it.
 FVector D(0);
 if(PC->IsInputKeyDown(EKeys::W)) D.X+=1;
 if(PC->IsInputKeyDown(EKeys::S)) D.X-=1;
 if(PC->IsInputKeyDown(EKeys::D)) D.Y+=1;
 if(PC->IsInputKeyDown(EKeys::A)) D.Y-=1;
 if(auto M=GetWorld()->GetAuthGameMode<AMissionMode>()) {
  if(M->Phase<4) { auto P=GetActorLocation()+D.GetSafeNormal()*Delta*230;
   P.X=FMath::Clamp(P.X,-300.,300.); P.Y=FMath::Clamp(P.Y,-300.,300.); SetActorLocation(P); }
 }
}
AMissionMode::AMissionMode() {
 PrimaryActorTick.bCanEverTick=true;
 DefaultPawnClass=AMissionPawn::StaticClass(); HUDClass=AMissionHUD::StaticClass();
 static ConstructorHelpers::FObjectFinder<USoundWave> A(TEXT("/Game/Audio/Tone1.Tone1"));
 static ConstructorHelpers::FObjectFinder<USoundWave> B(TEXT("/Game/Audio/Tone2.Tone2"));
 static ConstructorHelpers::FObjectFinder<USoundWave> C(TEXT("/Game/Audio/Tone3.Tone3"));
 static ConstructorHelpers::FObjectFinder<USoundWave> D(TEXT("/Game/Audio/Tone4.Tone4"));
 Tones.Add(A.Object); Tones.Add(B.Object); Tones.Add(C.Object); Tones.Add(D.Object);
}
void AMissionMode::Paint(UStaticMeshComponent* Mesh,FLinearColor Color) {
 auto Base=LoadObject<UMaterialInterface>(nullptr,TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
 auto Mat=UMaterialInstanceDynamic::Create(Base,this);
 if(Mat) { Mat->SetVectorParameterValue(TEXT("Color"),Color); Mesh->SetMaterial(0,Mat); }
}
UStaticMeshComponent* AMissionMode::Part(AActor* Owner,const TCHAR* Shape,FVector Location,FVector Scale,FLinearColor Color) {
 auto Mesh=NewObject<UStaticMeshComponent>(Owner);
 Owner->AddInstanceComponent(Mesh);
 if(!Owner->GetRootComponent()) Owner->SetRootComponent(Mesh);
 else Mesh->SetupAttachment(Owner->GetRootComponent());
 Mesh->SetMobility(EComponentMobility::Movable);
 const FString Path=FString::Printf(TEXT("/Engine/BasicShapes/%s.%s"),Shape,Shape);
 Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,*Path));
 Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
 Mesh->SetRelativeLocation(Location); Mesh->SetRelativeScale3D(Scale);
 Mesh->RegisterComponent(); Paint(Mesh,Color); return Mesh;
}
void AMissionMode::BeginPlay() {
 Super::BeginPlay();
 auto PC=GetWorld()->GetFirstPlayerController();
 PC->bShowMouseCursor=true; PC->bEnableClickEvents=true; PC->SetInputMode(FInputModeGameAndUI());
 auto Site=GetWorld()->SpawnActor<AActor>();
 auto SiteRoot=NewObject<USceneComponent>(Site); Site->AddInstanceComponent(SiteRoot); Site->SetRootComponent(SiteRoot); SiteRoot->RegisterComponent();
 Part(Site,TEXT("Cube"),FVector(0,0,-45),FVector(24,24,.4),Navy);
 Part(Site,TEXT("Cylinder"),FVector(500,250,0),FVector(6,6,.2),FLinearColor(.2,.25,.32));
 for(int i=0;i<3;++i) {
  Part(Site,TEXT("Cube"),FVector(50,350+i*150,60),FVector(1,.8,1.2),FLinearColor(.08,.14,.2));
  Indicators.Add(Part(Site,TEXT("Sphere"),FVector(50,350+i*150,140),FVector(.35),Orange));
 }
 Rocket=GetWorld()->SpawnActor<AActor>();
 auto Root=NewObject<USceneComponent>(Rocket); Rocket->AddInstanceComponent(Root); Rocket->SetRootComponent(Root); Root->RegisterComponent();
 Part(Rocket,TEXT("Cylinder"),FVector(0,0,240),FVector(1.3,1.3,4.3),FLinearColor(.85,.87,.9));
 Part(Rocket,TEXT("Cone"),FVector(0,0,505),FVector(1.3,1.3,1.2),Orange);
 Part(Rocket,TEXT("Cylinder"),FVector(0,0,80),FVector(1.4,1.4,.5),Navy);
 for(int i=-1;i<=1;i+=2) Part(Rocket,TEXT("Cube"),FVector(0,i*92,100),FVector(.3,.8,1.5),Orange);
 Rocket->SetActorLocation(FVector(500,250,0));
 auto Astronaut=Cast<AMissionPawn>(PC->GetPawn());
 if(Astronaut) {
  Part(Astronaut,TEXT("Cylinder"),FVector(0,0,65),FVector(.55,.55,.8),FLinearColor(.9,.92,.95));
  Part(Astronaut,TEXT("Sphere"),FVector(0,0,130),FVector(.75),FLinearColor(.9,.92,.95));
  Part(Astronaut,TEXT("Sphere"),FVector(-25,-15,135),FVector(.38,.55,.4),FLinearColor(.12,.28,.4));
  Part(Astronaut,TEXT("Cube"),FVector(28,10,75),FVector(.35,.5,.65),Orange);
  for(int i=-1;i<=1;i+=2) Part(Astronaut,TEXT("Cylinder"),FVector(0,i*19,22),FVector(.22,.22,.55),FLinearColor(.8,.82,.85));
 }
 auto Sun=GetWorld()->SpawnActor<ADirectionalLight>(); Sun->SetActorRotation(FRotator(-55,-30,0)); Sun->GetLightComponent()->SetIntensity(5);
 GetWorld()->SpawnActor<ASkyLight>();
}
void AMissionMode::NewSequence() {
 Mission.Generate([this](){return PatternRandom.RandRange(0,3);}); Phase=1; Clock=0; LastCue=-1;
}
void AMissionMode::Restart() {
 Mission.Reset(); PatternRandom.Initialize(2026); TaskSeconds=0; LastCue=-1; Phase=0; Clock=0; Status=TEXT("Welcome, astronaut. Prepare three flight systems.");
 Rocket->SetActorLocation(FVector(500,250,0));
 if(auto P=GetWorld()->GetFirstPlayerController()->GetPawn()) P->SetActorHiddenInGame(false);
 for(auto I:Indicators) Paint(I,Orange);
}
void AMissionMode::Action(int Symbol) {
 if(Symbol==9) { Restart(); return; }
 if(Symbol==8) {
  if(Phase==0) {
   bool HasAudio=Tones.Num()==4;
   for(auto Tone:Tones) HasAudio=HasAudio && Tone!=nullptr;
   if(Modality>0 && !HasAudio) { Status=TEXT("Audio missing: run Scripts/create_map.py, then restart the editor."); return; }
   NewSequence();
  }
  else if(Phase==3) { Phase=4; Clock=0; Status=TEXT("Crew boarded. Launch sequence engaged."); GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true); }
  return;
 }
 if(Phase!=2) return;
 int Result=Mission.Submit(Symbol);
 if(Result==-1) { Phase=1; Clock=0; LastCue=-1; Status=TEXT("Sequence mismatch. Watch the same pattern and retry."); }
 else if(Result>0) {
  Paint(Indicators[Mission.Stage-1],FLinearColor::Green);
  if(Result==2) { SaveResult(); Phase=3; Status=TEXT("All systems GO. Board the rocket and launch!"); }
  else { Status=TEXT("System secured. Memorize the next flight system."); NewSequence(); }
 }
}
void AMissionMode::Tick(float Delta) {
 Super::Tick(Delta); Clock+=Delta;
 if(Phase==1 || Phase==2) TaskSeconds+=Delta;
 auto PC=GetWorld()->GetFirstPlayerController(); if(!PC) return;
 if(PC->WasInputKeyJustPressed(EKeys::R)) { Restart(); return; }
 if(Phase==0 && PC->WasInputKeyJustPressed(EKeys::M)) Modality=(Modality+1)%3;
 if(PC->WasInputKeyJustPressed(EKeys::SpaceBar)) Action(8);
 if(Phase==1) {
  const int Cue=FMath::FloorToInt(Clock);
  if(Cue<Mission.Length() && Cue!=LastCue) {
   LastCue=Cue;
   if(Modality>0 && Tones.IsValidIndex(Mission.Sequence[Cue]))
    UGameplayStatics::PlaySound2D(this,Tones[Mission.Sequence[Cue]]);
  }
 }
 const FKey Keys[]={EKeys::One,EKeys::Two,EKeys::Three,EKeys::Four};
 for(int i=0;i<4;++i) if(PC->WasInputKeyJustPressed(Keys[i])) Action(i);
 if(Phase==1 && Clock>=Mission.Length()*1.0f) { Phase=2; Clock=0; Status=TEXT("Repeat the pattern using 1-4 or the buttons."); }
 if(Phase==4 && Clock>5) {
  const float T=Clock-5;
  Rocket->SetActorLocation(FVector(500,250,100*T*T));
  if(T>=6) { Phase=5; Status=TEXT("MISSION SUCCESS - orbit achieved! Earth is behind you."); }
 }
}
void AMissionHUD::Label(const FString& Text,float X,float Y,FLinearColor Color,float Scale) { DrawText(Text,Color,X,Y,nullptr,Scale); }
void AMissionHUD::Button(FName Name,const FString& Text,float X,float Y,float W,FLinearColor Color) {
 DrawRect(Color,X,Y,W,48); Label(Text,X+12,Y+13,FLinearColor::White,1.15f);
 AddHitBox(FVector2D(X,Y),FVector2D(W,48),Name,true);
}
void AMissionHUD::DrawHUD() {
 Super::DrawHUD(); auto M=GetWorld()->GetAuthGameMode<AMissionMode>(); if(!M||!Canvas) return;
 const float W=Canvas->SizeX;
 DrawRect(FLinearColor(.01,.02,.045,.94),0,0,W,190);
 Label(TEXT("ORBIT / RECALL"),28,20,Cyan,2);
 Label(TEXT("NASA-INSPIRED FLIGHT READINESS SIMULATOR"),28,54,FLinearColor(.6,.7,.8));
 Label(FString::Printf(TEXT("SYSTEMS %d / 3    |    RETRIES %d"),M->Mission.Stage,M->Mission.Mistakes),28,84);
 Label(M->Status,28,112);
 Label(TEXT("M: mode before start | WASD: move astronaut    1-4: recall    SPACE: start / launch    R: restart"),28,148,Cyan);
 const float Y=FMath::Max(210.f,Canvas->SizeY-190.f);
 DrawRect(FLinearColor(.01,.02,.045,.96),0,Y-15,W,205);
 if(M->Phase==0) {
  Button(TEXT("Start"),TEXT("BEGIN MISSION [SPACE]"),28,Y,265,Cyan*.55f);
  Button(TEXT("Mode"),FString::Printf(TEXT("MODE: %s [M]"),M->Modality==0?TEXT("VISUAL"):M->Modality==1?TEXT("AUDIO"):TEXT("BOTH")),28,Y+60,300,FLinearColor(.08,.19,.28));
  Label(TEXT("Audio mapping: 1 low / 2 mid-low / 3 mid-high / 4 high. Practice before recording."),28,Y+125,Cyan);
 }
 if(M->Phase==1||M->Phase==2) {
  Label(FString::Printf(TEXT("%s | %s | %d-symbol pattern"),Systems[M->Mission.Stage],M->Phase==1?TEXT("OBSERVE"):TEXT("RECALL"),M->Mission.Length()),28,Y);
  const int Showing=FMath::FloorToInt(M->Clock);
  for(int i=0;i<4;++i) {
   bool Lit=M->Modality!=1 && M->Phase==1 && Showing<M->Mission.Length() && M->Clock-Showing<.72f && M->Mission.Sequence[Showing]==i;
   const float BW=FMath::Min(130.f,(W-80)/4.f);
   Button(FName(*FString::FromInt(i)),Symbols[i],28+i*(BW+8),Y+35,BW,Lit?Orange:FLinearColor(.08,.19,.28));
  }
  Label(M->Phase==1?TEXT("Watch each flash. Repeated symbols have a short dark gap."):FString::Printf(TEXT("Correct inputs: %d / %d"),M->Mission.Cursor,M->Mission.Length()),28,Y+100,Cyan);
 }
 if(M->Phase==3) Button(TEXT("Start"),TEXT("BOARD & LAUNCH [SPACE]"),28,Y,285,Orange*.65f);
 if(M->Phase==4) Label(M->Clock<5?FString::Printf(TEXT("T - %d"),FMath::CeilToInt(5-M->Clock)):TEXT("LIFTOFF - climbing to orbit"),28,Y,Orange,2);
 if(M->Phase==5) { Label(TEXT("YOU WIN / MISSION COMPLETE"),28,Y,Cyan,2); Button(TEXT("Reset"),TEXT("FLY AGAIN [R]"),28,Y+50,220,Cyan*.55f); }
}
void AMissionHUD::NotifyHitBoxClick(FName Name) {
 Super::NotifyHitBoxClick(Name); auto M=GetWorld()->GetAuthGameMode<AMissionMode>(); if(!M) return;
 if(Name==TEXT("Mode")) { if(M->Phase==0) M->Modality=(M->Modality+1)%3; }
 else if(Name==TEXT("Start")) M->Action(8);
 else if(Name==TEXT("Reset")) M->Action(9);
 else { FString S=Name.ToString(); if(S.IsNumeric()) M->Action(FCString::Atoi(*S)); }
}

void AMissionMode::SaveResult() {
 const FString Dir=FPaths::ProjectSavedDir()/TEXT("Results");
 IFileManager::Get().MakeDirectory(*Dir,true);
 const FString Path=Dir/TEXT("sessions.csv");
 FString Row;
 if(!FPaths::FileExists(Path)) Row=TEXT("utc,seed,mode,retries,task_seconds,systems\n");
 Row+=FString::Printf(TEXT("%s,2026,%s,%d,%.3f,3\n"),*FDateTime::UtcNow().ToIso8601(),Modality==0?TEXT("visual"):Modality==1?TEXT("audio"):TEXT("combined"),Mission.Mistakes,TaskSeconds);
 if(!FFileHelper::SaveStringToFile(Row,*Path,FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,&IFileManager::Get(),FILEWRITE_Append))
  UE_LOG(LogTemp,Warning,TEXT("Could not save session results to %s"),*Path);
}
