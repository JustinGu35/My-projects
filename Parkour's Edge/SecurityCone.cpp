#include "SecurityCone.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Player.h"
#include "PlayerMove.h"

SecurityCone::SecurityCone(Game* inGame, Actor* parent)
:Actor(inGame,parent)
{
    mMC=new MeshComponent(this,true);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    mPosition.Set(30,0,0);
    mScale=3.0f;
}

void SecurityCone::OnUpdate(float deltaTime)
{
    Vector3 mF=GetWorldForward();
    Vector3 mP=GetWorldPosition();
    
    Vector3 toP= mGame->GetPlayer()->GetPosition()-mP;
    mF.Normalize();
    float angle = Math::Acos(Vector3::Dot(mF,Vector3::Normalize(toP)));
    
    bool nowInside=false;
    
    if(angle>CONE_ANGLE)
    {
        nowInside=false;
    }
    else
    {
        float distance= Vector3::Dot(toP,mF);
        if(distance<CONE_HEIGHT*mScale)
        {
            nowInside=true;
        }
        else
        {
            nowInside=false;
        }
    }
    
    //Now i knoww whether it is inside or not
    if(nowInside)
    {
        if(!isInside)
        {
            SecurityDetected=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/SecurityDetected.wav"),0);
            color=1;
            mMC->SetTextureIndex(color);
            insideTimer+=deltaTime;
            isInside=true;
        }
        else
        {
            insideTimer+=deltaTime;
            if(insideTimer>=2)
            {
                if(color==1)
                {
                    color=2;
                    mMC->SetTextureIndex(color);
                }
                if(insideTimer>=2.5&& color==2)
                {
                    Player* mPlayer=mGame->GetPlayer();
                    mPlayer->SetPosition(mPlayer->GetRespawnPos());
                    mPlayer->SetRotation(0);
                    mPlayer->GetComponent<PlayerMove>()->SetVelocityZero();
                    mPlayer->GetComponent<PlayerMove>()->SetPendingForceZero();
                    mPlayer->GetComponent<PlayerMove>()->ChangeState(MoveState::Falling);
                }
            }
        }
    }
    else
    {
        if(isInside)
        {
            Mix_HaltChannel(SecurityDetected);
            color=0;
            mMC->SetTextureIndex(color);
            insideTimer=0.0;
            isInside=false;
        }
    }
}
