#include "CameraComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "PlayerMove.h"

CameraComponent::CameraComponent(Actor* mOwner)
:Component(mOwner)
{
}

void CameraComponent::Update(float deltaTime)
{
    mPitchAngle+=mPitchSpeed*deltaTime;
    if(mPitchAngle>Math::PiOver2/2)
    {
        mPitchAngle=Math::PiOver2/2;
    }
    else if(mPitchAngle<-Math::PiOver2/2)
    {
        mPitchAngle=-Math::PiOver2/2;
    }
    
    
    Matrix4 rollM;
    CollSide tempState=mOwner->GetComponent<PlayerMove>()->GetCollidingSide();
    if(mOwner->GetComponent<PlayerMove>()->GetCurrentState()==MoveState::WallRun)
    {
        if(tempState==CollSide::SideX1)
        {
            mRollAngle=Math::Lerp(mRollAngle,(float)-Math::Pi/4,0.1);
            rollM=Matrix4::CreateRotationY(mRollAngle);
        }
        else if(tempState==CollSide::SideX2)
        {
            mRollAngle=Math::Lerp(mRollAngle,(float)Math::Pi/4,0.1);
            rollM=Matrix4::CreateRotationY(mRollAngle);
        }
        else if(tempState==CollSide::SideY1)
        {
            mRollAngle=Math::Lerp(mRollAngle,(float)Math::Pi/4,0.1);
            rollM=Matrix4::CreateRotationX(mRollAngle);
        }
        else if(tempState==CollSide::SideY2)
        {
            mRollAngle=Math::Lerp(mRollAngle,(float)-Math::Pi/4,0.1);
            rollM=Matrix4::CreateRotationX(mRollAngle);
        }
    }
    else
    {
        if(mRollAngle!=0)
        {
            if(Math::NearZero(mRollAngle))
            {
                mRollAngle=0;
                rollM=Matrix4::Identity;
            }
            else
            {
                mRollAngle=Math::Lerp(mRollAngle,0,0.1);
                if(tempState==CollSide::SideX1 ||tempState==CollSide::SideX2)
                {
                    rollM=Matrix4::CreateRotationY(mRollAngle);
                }
                else
                {
                    rollM=Matrix4::CreateRotationX(mRollAngle);
                }
            }
        }
        else
        {
            rollM=Matrix4::Identity;
        }
    }
    
    
    Matrix4 pitchM=Matrix4::CreateRotationY(mPitchAngle);
    Matrix4 yawM=Matrix4::CreateRotationZ(mOwner->GetRotation());
    
    pitchM*=yawM;
    Vector3 forwardVector=Vector3::Transform(Vector3::UnitX,pitchM);
    Vector3 upVector=Vector3::Transform(Vector3::UnitZ,rollM);
    
    
    Vector3 tempPos=mOwner->GetPosition();
    Vector3 TargetPos=tempPos+forwardVector*TARGETDIST;
    Matrix4 look=Matrix4::CreateLookAt(tempPos,TargetPos,upVector);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(look);
}

