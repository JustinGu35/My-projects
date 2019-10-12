#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mGame->AddActor(this);
}

Actor::~Actor()
{
	// TODO
    mGame->RemoveActor(this);
    unsigned int temp=(unsigned int)mComponents.size();
    for(unsigned int i=0;i<temp;i++ )
    {
        delete mComponents[i];
    }
    mComponents.clear();
}

void Actor::Update(float deltaTime)
{
	// TODO
    if(mState==ActorState::Active)
    {
        for(unsigned int i=0;i<mComponents.size();i++)
        {
            mComponents[i]->Update(deltaTime);
        }
        OnUpdate(deltaTime);
    }
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// TODO
    if(mState==ActorState::Active)
    {
        for(unsigned int i=0;i<mComponents.size();i++)
        {
            mComponents[i]->ProcessInput(keyState);
        }
        OnProcessInput(keyState);
    }
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

Vector2 Actor::GetForward()
{
    float x=cos(mRotation);
    float y=-sin(mRotation);
    Vector2 output(x,y);
    return output;
}

