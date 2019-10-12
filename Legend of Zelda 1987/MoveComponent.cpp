#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner, 50)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	// TODO: Implement in Part 2
    this->mOwner->SetRotation(this->mOwner->GetRotation()+deltaTime*mAngularSpeed);
    Vector2 forwardV=this->mOwner->GetForward();
    Vector2 tempPosition= this->mOwner->GetPosition()+forwardV*deltaTime*mForwardSpeed;
    this->mOwner->SetPosition(tempPosition);
}
