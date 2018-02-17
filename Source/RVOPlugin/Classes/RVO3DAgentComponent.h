// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI/Navigation/NavigationAvoidanceTypes.h"
#include "RVO3DAgentComponent.generated.h"

class URVO3DSimulatorComponent;
class UMovementComponent;

/** 
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class RVOPLUGIN_API URVO3DAgentComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

    // Velocity result of RVO simulation
    FVector AvoidanceVelocity;

    // Locked preferred velocity
    float PreferredVelocityLockTimer;
    FVector PreferredVelocity;

    // Goal adjustment
    bool bRequireGoalAdjustment;
    float GoalAdjustmentLockTimer;
    FVector GoalAdjustment;

    // Agents to ignore
    TSet<const URVO3DAgentComponent*> IgnoredAgents;

    UPROPERTY(EditAnywhere, Category=Component)
    bool bAutoRegisterMovementComponent;

    UPROPERTY(EditAnywhere, Category=RVO)
    int32 MaxNeighbourCount;

    UPROPERTY(EditAnywhere, Category=RVO)
    float NeighbourDistance;

    UPROPERTY(EditAnywhere, Category=RVO)
    float TimeHorizon;

    UPROPERTY(EditAnywhere, Category=RVO)
    float AgentRadius;

	/** Moving actor's group mask */
    UPROPERTY(EditAnywhere, Category=RVO, AdvancedDisplay)
	FNavAvoidanceMask AvoidanceGroup;

	/** Will avoid other agents if they are in one of specified groups */
    UPROPERTY(EditAnywhere, Category=RVO, AdvancedDisplay)
	FNavAvoidanceMask GroupsToAvoid;

	/** Will NOT avoid other agents if they are in one of specified groups, higher priority than GroupsToAvoid */
    UPROPERTY(EditAnywhere, Category=RVO, AdvancedDisplay)
	FNavAvoidanceMask GroupsToIgnore;

    void RegisterSimulatorDependency();
    void UnregisterSimulatorDependency();

protected:

	UPROPERTY(BlueprintReadOnly, Transient, DuplicateTransient, Category=RVO)
    URVO3DSimulatorComponent* SimulatorComponent;

	UPROPERTY(BlueprintReadOnly, Transient, DuplicateTransient, Category=RVO)
    UMovementComponent* MovementComponent;

public:

	/**
	 * Default UObject constructor.
	 */
	//URVO3DAgentComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

//BEGIN UActorComponent Interface
	virtual void InitializeComponent() override;
	virtual void OnRegister() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
//END UActorComponent interface.	

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
    void SetMovementComponent(UMovementComponent* InMovementComponent);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
    bool HasSimulator() const;

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
    void SetSimulatorActor(AActor* InSimulatorActor);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
    void SetSimulatorComponent(URVO3DSimulatorComponent* InSimulatorComponent);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
    void ResetSimulatorComponent();

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void SetAvoidanceGroupMask(const FNavAvoidanceMask& GroupMask);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void SetGroupsToAvoidMask(const FNavAvoidanceMask& GroupMask);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void SetGroupsToIgnoreMask(const FNavAvoidanceMask& GroupMask);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void UpdateIgnoredAgents();

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void AddIgnoredAgent(const URVO3DAgentComponent* AgentComponent);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void RemoveIgnoredAgent(const URVO3DAgentComponent* AgentComponent);

	UFUNCTION(BlueprintCallable, Category="RVO|Components|AgentComponent")
	void ClearIgnoredAgents(bool bAllowShrinking = true);

    FORCEINLINE void SetAvoidanceVelocity(const FVector& Velocity, bool bInRequireGoalAdjustment);

    FORCEINLINE void TickLockTimer(float DeltaTime);

    FORCEINLINE bool HasLockedPreferredVelocity() const;
    FORCEINLINE void LockPreferredVelocity(const FVector& InPreferredVelocity);
    FORCEINLINE void LockPreferredVelocity(const FVector& InPreferredVelocity, float LockDuration);
    FORCEINLINE void UnlockPreferredVelocity();

    FORCEINLINE bool IsGoalAdjustmentRequired() const;
    FORCEINLINE bool HasLockedGoalAdjustment() const;
    FORCEINLINE void LockGoalAdjustment();
    FORCEINLINE void UnlockGoalAdjustment();

    FORCEINLINE bool HasMovementComponent() const;
    FORCEINLINE bool HasUpdatedComponent() const;
    FORCEINLINE bool HasAvoidanceVelocity() const;

    FORCEINLINE FVector GetPreferredVelocity() const;
    FORCEINLINE FVector GetPreferredDirection() const;
    FORCEINLINE FVector GetAvoidanceVelocity() const;
    FORCEINLINE FVector GetAgentVelocity() const;
    FORCEINLINE FVector GetAgentLocation() const;
    FORCEINLINE float GetAgentMaxSpeed() const;

    FORCEINLINE int32 GetMaxNeighbourCount() const
    {
        return MaxNeighbourCount;
    }

    FORCEINLINE float GetNeighbourDistance() const
    {
        return NeighbourDistance;
    }

    FORCEINLINE float GetTimeHorizon() const
    {
        return TimeHorizon;
    }

    FORCEINLINE float GetAgentRadius() const
    {
        return AgentRadius;
    }

	FORCEINLINE int32 GetAvoidanceGroupMask()
    {
        return AvoidanceGroup.Packed;
    }

	FORCEINLINE int32 GetGroupsToAvoidMask()
    {
        return GroupsToAvoid.Packed;
    }

	FORCEINLINE int32 GetGroupsToIgnoreMask()
    {
        return GroupsToIgnore.Packed;
    }

	FORCEINLINE const TSet<const URVO3DAgentComponent*>& GetIgnoredAgents() const
    {
        return IgnoredAgents;
    }
};
