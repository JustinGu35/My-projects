#include "Game.h"
#include "MeshComponent.h"
#include "Player.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "PlayerMove.h"
#include "CameraComponent.h"


Player::Player(Game* inGame,Actor* parent)
:Actor(inGame,parent)
{
    mPM=new PlayerMove(this);
    mCaC=new CameraComponent(this);
    mCC=new CollisionComponent(this);
    mCC->SetSize(50,175,50);
    
}
