#include "Sword.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"


Sword::Sword(Game* inGame)
:Actor(inGame)
{
    mSC=new SpriteComponent(this);
    mCC=new CollisionComponent(this);
    mSC->SetTexture(mGame->GetTexture("Assets/Sword/Up.png"));
    mCC->SetSize(25,25);
    
}
