#include "Coin.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "Player.h"

Coin::Coin(Game* inGame, Actor* parent)
:Actor(inGame,parent)
{
    mMC=new MeshComponent(this);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Coin.gpmesh"));
    mCC=new CollisionComponent(this);
    mCC->SetSize(100,100,100);
}

void Coin::OnUpdate(float deltaTime)
{
    mRotation+=deltaTime*Math::Pi/4;
    if(mCC->Intersect(mGame->GetPlayer()->GetComponent<CollisionComponent>()))
    {
        SetState(ActorState::Destroy);
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/Coin.wav"),0);
    }
}
