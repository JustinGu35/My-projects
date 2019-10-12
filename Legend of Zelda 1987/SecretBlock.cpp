#include "SecretBlock.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

SecretBlock::SecretBlock( Game* inGame)
:Actor(inGame)
{
    mCC=new CollisionComponent(this);
    mSC=new SpriteComponent(this);
    mSC->SetTexture(mGame->GetTexture("Assets/SecretBlock.png"));
    mCC->SetSize(32.0,32.0);
}
SecretBlock::~SecretBlock()
{
    
}
