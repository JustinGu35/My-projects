#include "Fireball.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Player.h"
#include "Game.h"

Fireball::Fireball(Game* inGame)
:Actor(inGame)
{
    timeElapsed=0;
    mSC=new SpriteComponent(this);
    mCC=new CollisionComponent(this);
    mMC=new MoveComponent(this);
    
    mCC->SetSize(16,16);
    mMC->SetForwardSpeed(200.0f);
    mSC->SetTexture(mGame->GetTexture("Assets/FireballRed.png"));
}

void Fireball::OnUpdate(float deltaTime)
{
    timeElapsed+=deltaTime;
    if(timeElapsed>=2.0)
    {
        SetState(ActorState::Destroy);
    }
    Vector2 offset;
    CollSide tempState=mCC->GetMinOverlap(mGame->mPlayer->GetComponent<CollisionComponent>(),offset);
    if(tempState!=CollSide::None)
    {
        SetState(ActorState::Destroy);
        mGame->mPlayer->TakeDamage(1);
    }
}

void Fireball::ChangeTexture(std::string inTexture)
{
    mSC->SetTexture(mGame->GetTexture(inTexture));
}
