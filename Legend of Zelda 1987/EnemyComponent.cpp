#include "Actor.h"
#include "EnemyComponent.h"
#include "Game.h"

EnemyComponent::EnemyComponent(Actor* owner)
:Component(owner),
HitPoint(1),
damage(1),
invulnerabilityTimer(0.0)
{
    existRoom=mOwner->GetGame()->getRoom();
    mOwner->GetGame()->AddEnemy(existRoom,mOwner);
}

EnemyComponent::~EnemyComponent()
{
    mOwner->GetGame()->RemoveEnemy(existRoom,mOwner);
}

void EnemyComponent::TakeDamage(int amount)
{
    if(invulnerabilityTimer<=0.0)
    {
        invulnerabilityTimer=1.0;
        HitPoint-=amount;
        if(HitPoint<=0)
        {
            if(mOnDeath)
            {
                mOnDeath();
            }
            mOwner->SetState(ActorState::Destroy);
        }
        else
        {
            if(mOnTakeDamage)
            {
                mOnTakeDamage();
            }
        }
    }
}

void EnemyComponent::SetOnDeath(std::function<void()> onDeath)
{
    mOnDeath=onDeath;
}

void EnemyComponent::SetOnTakeDamage(std::function<void()> onTakeDamage)
{
    mOnTakeDamage=onTakeDamage;
}

void EnemyComponent::Update(float deltaTime)
{
    if(invulnerabilityTimer>0.0)
    {
        invulnerabilityTimer-=deltaTime;
    }
}
