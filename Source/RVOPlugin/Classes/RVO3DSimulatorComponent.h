////////////////////////////////////////////////////////////////////////////////
//
// MIT License
// 
// Copyright (c) 2018-2019 Nuraga Wiswakarma
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////
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
