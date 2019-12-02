#include "Block.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"

Block::Block(Game* inGame,Actor* parent)
:Actor(inGame,parent)
{
    mScale=64;
    mMC= new MeshComponent(this);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    mCC=new CollisionComponent(this);
    mCC->SetSize(1,1,1);
    
    mGame->AddBlock(this);
}

Block::~Block()
{
    mGame->Remove(this);
}

void Block::OnUpdate(float deltaTime)
{
    if(isRotate)
    {
        mRotation+=deltaTime*Math::Pi/4;
    }
}
