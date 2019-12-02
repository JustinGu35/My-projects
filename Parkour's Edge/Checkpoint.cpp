#include "Checkpoint.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "Player.h"

Checkpoint::Checkpoint(Game* inGame,Actor* parent)
:Actor(inGame,parent)
{
    mMC=new MeshComponent(this);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    mMC->SetTextureIndex(1);
    mCC=new CollisionComponent(this);
    mCC->SetSize(25,25,25);
}

void Checkpoint::SetActive(bool inA)
{
    if(inA!=isActive)
    {
        if(inA)
        {
            mMC->SetTextureIndex(0);
        }
        else
        {
            mMC->SetTextureIndex(1);
        }
    }
    isActive=inA;
}


