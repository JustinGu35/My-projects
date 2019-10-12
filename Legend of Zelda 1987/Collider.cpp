#include "Collider.h"
#include "Game.h"
#include "CollisionComponent.h"

Collider::Collider(Game* inGame)
:Actor(inGame)
{
    mCC=new CollisionComponent(this);
}
Collider::~Collider()
{
    
}

void Collider::SetDimension(int inWidth,int inHeight)
{
    mCC->SetSize(inWidth,inHeight);
}

