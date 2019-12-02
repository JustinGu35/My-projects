#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner, 50)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
,mStrafeSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	// TODO: Implement in Part 2
    this->mOwner->SetRotation(this->mOwner->GetRotation()+deltaTime*mAngularSpeed);
    Vector3 forwardV=this->mOwner->GetForward();
    Vector3 tempPosition= this->mOwner->GetPosition()+forwardV*deltaTime*mForwardSpeed;
    this->mOwner->SetPosition(tempPosition);
    
    tempPosition= this->mOwner->GetPosition()+mStrafeSpeed*deltaTime*this->mOwner->GetRight();
    this->mOwner->SetPosition(tempPosition);
}
