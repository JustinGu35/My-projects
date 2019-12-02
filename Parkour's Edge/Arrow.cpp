#include "Arrow.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Player.h"
#include "Checkpoint.h"

Arrow::Arrow(Game* inGame, Actor* parent)
:Actor(inGame,parent)
{
    mMC=new MeshComponent(this);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Arrow.gpmesh"));
    SetScale(0.15);
}

void Arrow::OnUpdate(float deltaTime)
{
    Player* mPlayer=mGame->GetPlayer();
    if(mGame->mCheckpoints.empty())
    {
        mPlayer->SetQuaternion(Quaternion::Identity);
    }
    else
    {
        Player* mPlayer=mGame->GetPlayer();
        Vector3 direction=mGame->mCheckpoints.front()->GetPosition()-mPlayer->GetPosition();
        direction.Normalize();
        float angle=Vector3::Dot(Vector3::UnitX,direction);
        Vector3 axis=Vector3::Cross(Vector3::UnitX,direction);
        axis.Normalize();
        if(angle==1)
        {
            SetQuaternion(Quaternion::Identity);
        }
        else if(angle==-1)
        {
            Quaternion mQ(Vector3::UnitZ,Math::Pi);
            SetQuaternion(mQ);
        }
        else
        {
            angle=Math::Acos(angle);
            Quaternion mQ(axis,angle);
            SetQuaternion(mQ);
        }
    }
    Vector3 position=mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f));
    mPosition=position;
}
