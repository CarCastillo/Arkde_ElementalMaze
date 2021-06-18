// Fill out your copyright notice in the Description page of Project Settings.


#include "EM_AIController.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "EM_Enemy.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "EM_Character.h"

AEM_AIController::AEM_AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	LoopPathParameterName = "bLoopPath";
	DirectionIndexParemeterName = "DirectionIndex";
	WaitingTimeParemeterName = "WaitingTimeOnPathPoint";
	CanSeePlayerParemeterName = "bCanSeePlayer";
	InvestigatingParemeterName = "bIsInvestigating";
	TargetLocationParemeterName = "TargetLocation";
}

void AEM_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EnemyBehaviorTree))
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

	MyEnemy = Cast<AEM_Enemy>(K2_GetPawn());

	if (IsValid(MyEnemy))
	{
		MyBlackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);

		if (IsValid(MyBlackboard))
		{
			MyBlackboard->SetValueAsBool(LoopPathParameterName, MyEnemy->GetLoopPath());
			MyBlackboard->SetValueAsInt(DirectionIndexParemeterName, MyEnemy->GetDirectionIndex());
			MyBlackboard->SetValueAsFloat(WaitingTimeParemeterName, MyEnemy->GetWaitingTime());
		}
	}

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEM_AIController::UpdateSenses);
}

void AEM_AIController::UpdateSenses(const TArray<AActor*>& UpdatedActors)
{
	if (!IsValid(MyBlackboard))
	{
		return;
	}
	
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo PerceptionInfo;
		AIPerceptionComponent->GetActorsPerception(Actor, PerceptionInfo);

		AEM_Character* SensedCharacter = Cast<AEM_Character>(Actor);
		if (IsValid(SensedCharacter) && SensedCharacter->GetCharacterType() == EEM_CharacterType::CharacterType_Player)
		{
			for (int i = 0; i < PerceptionInfo.LastSensedStimuli.Num(); i++)
			{
				switch (i)
				{
				case 0:
					MyBlackboard->SetValueAsBool(CanSeePlayerParemeterName, PerceptionInfo.LastSensedStimuli[i].WasSuccessfullySensed());
					break;
				case 1:
					MyBlackboard->SetValueAsBool(InvestigatingParemeterName, bReceivingDamage);
					if (bReceivingDamage)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Enemy has been damaged!");
						MyBlackboard->SetValueAsVector(TargetLocationParemeterName, PerceptionInfo.LastSensedStimuli[i].StimulusLocation);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}
