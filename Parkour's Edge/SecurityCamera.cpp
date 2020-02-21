#include "SecurityCamera.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "SecurityCone.h"
#include "Player.h"

SecurityCamera::SecurityCamera(Game* inGame, Actor* parent)
:Actor(inGame,parent)
{
    mMC=new MeshComponent(this);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    mSC=new SecurityCone(inGame,this);
    mQuaternion=startQ;
    mChild=dynamic_cast<SecurityCone*>(mChildren[0]);
    
    mGame->AddSecurityCamera(this);
}

SecurityCamera::~SecurityCamera()
{
    if(CameraRotate!=-1)
    {
        Mix_HaltChannel(CameraRotate);
    }
    mGame->RemoveSecurityCamera(this);
}

void SecurityCamera::OnUpdate(float deltaTime)
{
    if(CameraRotate!=-1)
    {
        SetVolume(CameraRotate);
    }
    
    if(mCameraState==CameraState::StartToEnd)
    {
        interpTimer+=deltaTime;
        if(interpTimer>=interpT)
        {
            if(CameraRotate!=-1)
            {
                Mix_HaltChannel(CameraRotate);
            }
            CameraRotate=-1;
            int temp=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
            SetVolume(temp);
            interpTimer=0;
            mCameraState=CameraState::PausedAtEnd;
        }
        else
        {
            mQuaternion=Quaternion::Slerp(startQ,endQ,interpTimer/interpT);
        }
        
        if(mChild->GetColor()!=0)
        {
            Mix_HaltChannel(CameraRotate);
            CameraRotate=-1;
            int temp=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
            SetVolume(temp);
            mLastState=mCameraState;
            mCameraState=CameraState::Disrupted;
        }
    }
    
    else if(mCameraState==CameraState::EndToStart)
    {
        interpTimer+=deltaTime;
        if(interpTimer>=interpT)
        {
            if(CameraRotate!=-1)
            {
                Mix_HaltChannel(CameraRotate);
            }
            CameraRotate=-1;
            int temp=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
            SetVolume(temp);
            interpTimer=0;
            mCameraState=CameraState::PausedAtStart;
        }
        else
        {
            mQuaternion=Quaternion::Slerp(endQ,startQ,interpTimer/interpT);
        }
        if(mChild->GetColor()!=0)
        {
            Mix_HaltChannel(CameraRotate);
            CameraRotate=-1;
            int temp=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
            SetVolume(temp);
            mLastState=mCameraState;
            mCameraState=CameraState::Disrupted;
        }
    }
    
    
    else if(mCameraState==CameraState::PausedAtStart)
    {
        pauseTimer+=deltaTime;
        if(pauseTimer>=pauseT)
        {
            CameraRotate=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotor.wav"),0);
            SetVolume(CameraRotate);
            pauseTimer=0;
            mCameraState=CameraState::StartToEnd;
        }
        if(mChild->GetColor()!=0)
        {
            mLastState=mCameraState;
            mCameraState=CameraState::Disrupted;
        }
    }
    
    
    else if(mCameraState==CameraState::PausedAtEnd)
    {
        pauseTimer+=deltaTime;
        if(pauseTimer>=pauseT)
        {
            CameraRotate=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotor.wav"),0);
            SetVolume(CameraRotate);
            pauseTimer=0;
            mCameraState=CameraState::EndToStart;
        }
        if(mChild->GetColor()!=0)
        {
            mLastState=mCameraState;
            mCameraState=CameraState::Disrupted;
        }
    }
    else
    {
        if(mChild->GetColor()==0)
        {
            mCameraState=mLastState;
            if(mLastState!=CameraState::PausedAtEnd &&mLastState!=CameraState::PausedAtStart)
            {
                CameraRotate=Mix_PlayChannel(Mix_GroupAvailable(1),mGame->GetSound("Assets/Sounds/CameraMotor.wav"),0);
                SetVolume(CameraRotate);
            }
        }
    }
}


float SecurityCamera::DistanceToPlayer()
{
    Vector3 playerPos=mGame->GetPlayer()->GetPosition();
    Vector3 theD=playerPos-mPosition;
    return theD.Length();
}

void SecurityCamera::SetVolume(int channel)
{
    float distance=DistanceToPlayer();
    if(distance>1500)
    {
        Mix_Volume(channel,0);
    }
    else if(distance<=500)
    {
        Mix_Volume(channel,128);
    }
    else
    {
        float division=(1500-distance)/1000;
        division*=128;
        Mix_Volume(channel,(int)division);
    }
}
