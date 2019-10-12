#include "Collectible.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Actor.h"
#include "Math.h"
#include "Player.h"


Collectible::Collectible(class Actor* owner)
:Component(owner)
{
    
}

void Collectible::SetOnCollect(std::function<void()> onCollect)
{
    mOnCollect=onCollect;
}

void Collectible::Update(float deltaTime)
{
    Vector2 offset;
    CollSide tempState=mOwner->GetComponent<CollisionComponent>()->GetMinOverlap
        (mOwner->GetGame()->mPlayer->GetComponent<CollisionComponent>(),offset);
    if(tempState!=CollSide::None)
    {
        mOwner->SetState(ActorState::Destroy);
        if(mOnCollect)
        {
            mOnCollect();
        }
    }
    
}
