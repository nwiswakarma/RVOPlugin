// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RVO3DSimulatorComponent.generated.h"

namespace RVO
{
    class RVOSimulator;
}

class URVO3DAgentComponent;

/** 
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class RVOPLUGIN_API URVO3DSimulatorComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

    TSharedPtr<RVO::RVOSimulator> Simulator;
    TMap<URVO3DAgentComponent*, int32> AgentMap;

    FORCEINLINE bool HasSimulator() const
    {
        return Simulator.IsValid();
    }

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=RVO)
    float LockTimeAfterAvoid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=RVO)
    float LockTimeAfterGoalAdjustment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=RVO)
    float GoalAdjustmentAngleOffset;

    //URVO3DSimulatorComponent();

	// Begin UActorComponent interface.
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// Begin UActorComponent interface.	

    UFUNCTION(BlueprintCallable, Category="RVO")
    void AddAgentActor(AActor* AgentActor);

    UFUNCTION(BlueprintCallable, Category="RVO")
    void RemoveAgentActor(AActor* AgentActor);

    UFUNCTION(BlueprintCallable, Category="RVO")
    void AddAgentComponent(URVO3DAgentComponent* AgentComponent);

    UFUNCTION(BlueprintCallable, Category="RVO")
    void RemoveAgentComponent(URVO3DAgentComponent* AgentComponent);

    void UpdateIgnoredAgents(const URVO3DAgentComponent* AgentComponent);
    void AddIgnoredAgent(const URVO3DAgentComponent* AgentComponent, const URVO3DAgentComponent* IgnoredAgent);
    void RemoveIgnoredAgent(const URVO3DAgentComponent* AgentComponent, const URVO3DAgentComponent* IgnoredAgent);
    void ClearIgnoredAgents(const URVO3DAgentComponent* AgentComponent, bool bAllowShrinking = false);
};
