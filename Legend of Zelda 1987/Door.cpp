#include "Door.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

Door::Door( Game* inGame)
:Actor(inGame)
{
    mCC=new CollisionComponent(this);
    mSC=new SpriteComponent(this);
    
}
Door::~Door()
{
    
}

void Door::setupDoor(std::string inDirectionState,std::string inDoorState,std::string inDestination)
{
    destination=inDestination;
    UpdateTexture(inDirectionState,inDoorState);
    
    if(inDirectionState=="Up"||inDirectionState=="Down")
    {
        mCC->SetSize(30,64);
    }
    else
    {
        mCC->SetSize(64,30);
    }
}


void Door::UpdateTexture(std::string inDirectionState,std::string inDoorState)
{
    std::string temp;
    temp+=inDirectionState;
    temp+=inDoorState;
    
    mSC->SetTexture(mGame->GetTexture("Assets/Door/"+temp+".png"));
    directionState=inDirectionState;
    doorState=inDoorState;
}


std::string Door::getDestination()
{
    return destination;
}
