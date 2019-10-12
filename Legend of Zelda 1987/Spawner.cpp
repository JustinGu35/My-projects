#include "Spawner.h"
#include "Actor.h"
#include "Game.h"
#include "Player.h"
#include "Math.h"
#include "Key.h"
#include "Bat.h"
#include "Skeleton.h"
#include "Boss.h"
#include "TriForce.h"

Spawner::Spawner(class Game* inGame)
:Actor(inGame)
{
    
}
Spawner::~Spawner()
{
    
}

void Spawner::activate()
{
    if(type=="Key")
    {
        Key* newKey=new Key(mGame);
        newKey->SetPosition(mPosition);
    }
    else if(type=="Bat")
    {
        Bat* newBat=new Bat(mGame);
        newBat->SetPosition(mPosition);
    }
    else if(type=="Skeleton")
    {
        Skeleton* newSkeleton=new Skeleton(mGame);
        newSkeleton->SetPosition(mPosition);
    }
    else if(type=="Boss")
    {
        Boss* newBoss=new Boss(mGame);
        newBoss->SetPosition(mPosition);
    }
    else if(type=="Triforce")
    {
        TriForce* newTriForce=new TriForce(mGame);
        newTriForce->SetPosition(mPosition);
    }
    SetState(ActorState::Destroy);
}
