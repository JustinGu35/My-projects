#include "Actor.h"
#include "PlayerMove.h"
#include "Game.h"
#include "Renderer.h"
#include <SDL/SDL.h>
#include "Random.h"
#include "CameraComponent.h"
#include "Player.h"
#include "Checkpoint.h"
#include "HUD.h"


PlayerMove::PlayerMove(Actor* inOwner)
:MoveComponent(inOwner)
{
    mGravity.Set(0.0f,0.0f,-980.0f);
    mJumpForce.Set(0.0f,0.0f,35000.0f);
    offsetRecorder.Set(0,0,0);
    mWallClimbForce.Set(0.0,0.0,1800);
    mWallRunForce.Set(0.0f,0.0f,1200.0f);
    ChangeState(MoveState::Falling);
    mRunningSFX=Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Running.wav"),-1);
    Mix_Pause(mRunningSFX);
   
}

PlayerMove::~PlayerMove()
{
    Mix_HaltChannel(mRunningSFX);
}

void PlayerMove::Update(float deltaTime)
{
    if(mCurrentState==MoveState::OnGround){UpdateOnGround(deltaTime);}
    else if(mCurrentState==MoveState::Jump){UpdateJump(deltaTime);}
    else if(mCurrentState==MoveState::Falling){UpdateFalling(deltaTime);}
    else if (mCurrentState==MoveState::WallClimb){UpdateWallClimb(deltaTime);}
    else if (mCurrentState==MoveState::WallRun){UpdateWallRun(deltaTime);}
    
    if(mOwner->GetPosition().z<-750.0)
    {
        Player* mPlayer=dynamic_cast<Player*>(mOwner);
        mOwner->SetPosition(mPlayer->GetRespawnPos());
        mOwner->SetRotation(0);
        mVelocity=Vector3::Zero;
        mPendingForces=Vector3::Zero;
        ChangeState(MoveState::Falling);
    }
    
    Game* mGame=mOwner->GetGame();
    if(!mGame->mCheckpoints.empty())
    {
        bool getCheck=mOwner->GetComponent<CollisionComponent>()->Intersect
                    (mGame->mCheckpoints.front()->GetComponent<CollisionComponent>());
        if(getCheck)
        {
            dynamic_cast<Player*>(mOwner)->SetRespawnPos(mGame->mCheckpoints.front()->GetPosition());
            std::string level=mGame->mCheckpoints.front()->GetLevel();
            if(level.size()!=0)
            {
                mGame->SetNextLevel(level);
            }
            mGame->mCheckpoints.front()->SetState(ActorState::Destroy);
            if(!mGame->mCheckpoints.front()->GetText().empty())
            {
                mGame->SetDisplayText(mGame->mCheckpoints.front()->GetText());
                mGame->SetTextTimer(0.0f);
                dynamic_cast<Player*>(mOwner)->GetComponent<HUD>()->ChangeTextTexture();
            }
            
            Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Checkpoint.wav"),0);
            mGame->mCheckpoints.pop();
            if(!mGame->mCheckpoints.empty())
            {
                mGame->mCheckpoints.front()->SetActive(true);
            }
        }
    }
}
void PlayerMove::ProcessInput(const Uint8* keyState)
{
    int forward=0;
    if(keyState[SDL_SCANCODE_W])
    {
        forward++;
    }
    if(keyState[SDL_SCANCODE_S])
    {
        forward--;
    }
    
    if(forward==1)
    {
        AddForce(mOwner->GetForward()*700.0f);
    }
    else if(forward==-1)
    {
        AddForce(mOwner->GetForward()*-700.0f);
    }
    
    //starfe move------------------------
    int strafe=0;
    if(keyState[SDL_SCANCODE_D])
    {
       strafe++;
    }
    if(keyState[SDL_SCANCODE_A])
    {
       strafe--;
    }
   
    if(strafe==1)
    {
       AddForce(mOwner->GetRight()*700.0f);
    }
    else if(strafe==-1)
    {
       AddForce(mOwner->GetRight()*-700.0f);
    }
    
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    
    float newX=x/500.0f;
    float newY=y/500.0f;
    newX*=Math::Pi*10.0f;
    newY*=Math::Pi*10.0f;
    SetAngularSpeed(newX);
    mOwner->GetComponent<CameraComponent>()->SetPitchSpeed(newY);
    
    
    if(keyState[SDL_SCANCODE_SPACE])
    {
        if(lastSpace==false&& mCurrentState==MoveState::OnGround)
        {
            Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav"),0);
            AddForce(mJumpForce);
            ChangeState(MoveState::Jump);
        }
        lastSpace=true;
    }
    else
    {
        lastSpace=false;
    }
}


void PlayerMove::UpdateOnGround(float deltaTime)
{
    PhysicsUpdate(deltaTime);
    if(mVelocity.Length()>50.0f)
    {
        Mix_Resume(mRunningSFX);
    }
    else
    {
        Mix_Pause(mRunningSFX);
    }
    bool onTop=false;
    for(auto block: mOwner->GetGame()->GetBlocks())
    {
        CollSide temp=FixCollision(mOwner->GetComponent<CollisionComponent>(),block->GetComponent<CollisionComponent>());
        if(temp==CollSide::Top)
        {
            onTop= true;
        }
        else if(temp==CollSide::SideX1||temp==CollSide::SideX2||
                temp==CollSide::SideY1||temp==CollSide::SideY2)
        {
            bool canJump=CanWallClimb(temp);
            if(canJump)
            {
                ChangeState(MoveState::WallClimb);
                mWallClimbTimer=0.0f;
                return;
            }
        }
    }
    if(!onTop)
    {
        ChangeState(MoveState::Falling);
    }
}
void PlayerMove::UpdateJump(float deltaTime)
{
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    Mix_Pause(mRunningSFX);
    
    for(auto block: mOwner->GetGame()->GetBlocks())
    {
        CollSide temp=FixCollision(mOwner->GetComponent<CollisionComponent>(),block->GetComponent<CollisionComponent>());
        if(temp==CollSide::Bottom)
        {
            mVelocity.z=0.0f;
        }
        else if(temp==CollSide::SideX1||temp==CollSide::SideX2||
                temp==CollSide::SideY1||temp==CollSide::SideY2)
        {
            bool canJump=CanWallClimb(temp);
            collidingSide=temp;
            if(canJump)
            {
                ChangeState(MoveState::WallClimb);
                mWallClimbTimer=0.0f;
                return;
            }
            else
            {
                if(CanWallRun(temp))
                {
                    ChangeState(MoveState::WallRun);
                    mWallRunTimer=0.0f;
                    return;
                }
            }
        }
    }
    if(mVelocity.z<=0.0f)
    {
        ChangeState(MoveState::Falling);
    }
}
void PlayerMove::UpdateFalling(float deltaTime)
{
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    Mix_Pause(mRunningSFX);
    
    for(auto block: mOwner->GetGame()->GetBlocks())
    {
        CollSide temp=FixCollision(mOwner->GetComponent<CollisionComponent>(),block->GetComponent<CollisionComponent>());
        if(temp==CollSide::Top)
        {
            mVelocity.z=0.0f;
            Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Land.wav"),0);
            ChangeState(MoveState::OnGround);
        }
    }
}

CollSide PlayerMove::FixCollision(class CollisionComponent* self, class CollisionComponent* block)
{
    Vector3 offset=Vector3::Zero;
    CollSide temp=self->GetMinOverlap(block,offset);
    if(temp!=CollSide::None)
    {
        mOwner->SetPosition(mOwner->GetPosition()+offset);
        offsetRecorder=offset;
        if(temp==CollSide::SideX1)
        {
            Vector3 normal(-700,0,0);
            AddForce(normal);
        }
        else if(temp==CollSide::SideX2)
        {
            Vector3 normal(700,0,0);
            AddForce(normal);
        }
        else if(temp==CollSide::SideY1)
        {
            Vector3 normal(0,-700,0);
            AddForce(normal);
        }
        else if(temp==CollSide::SideY2)
        {
            Vector3 normal(0,700,0);
            AddForce(normal);
        }
    }
    return temp;
}


void PlayerMove::PhysicsUpdate(float deltaTime)
{
    mAcceleration=mPendingForces * (1.0f/mMass);
    mVelocity+=mAcceleration* deltaTime;
    FixXYVelocity();
    mOwner->SetPosition(mOwner->GetPosition()+mVelocity*deltaTime);
    mOwner->SetRotation(mOwner->GetRotation()+deltaTime*GetAngularSpeed());
    mPendingForces=Vector3::Zero;
}
void PlayerMove::AddForce(const Vector3& force)
{
    mPendingForces+=force;
}

void PlayerMove::FixXYVelocity()
{
    Vector2 xyVelocity;
    xyVelocity.Set(mVelocity.x,mVelocity.y);
    
    if(xyVelocity.Length()>=400.0f)
    {
        xyVelocity.Normalize();
        xyVelocity*=400.0f;
    }
    
    if(mCurrentState==MoveState::OnGround||mCurrentState==MoveState::WallClimb)
    {
        if(Math::NearZero(mAcceleration.x))
        {
            xyVelocity.x*=(float)0.9;
        }
        
        if(Math::NearZero(mAcceleration.y))
        {
            xyVelocity.y*=(float)0.9;
        }
        
        if((xyVelocity.x>0 && mAcceleration.x<0) || (xyVelocity.x<0 && mAcceleration.x>0))
        {
            xyVelocity.x*=(float)0.9;
        }
        if((xyVelocity.y>0 && mAcceleration.y<0) || (xyVelocity.y<0 && mAcceleration.y>0))
        {
            xyVelocity.y*=(float)0.9;
        } 
    }
    
    mVelocity.x=xyVelocity.x;
    mVelocity.y=xyVelocity.y;
}


void PlayerMove::UpdateWallClimb(float deltaTime)
{
    AddForce(mGravity);
    mWallClimbTimer+=deltaTime;
    Mix_Resume(mRunningSFX);
    if(mWallClimbTimer<0.4)
    {
        AddForce(mWallClimbForce);
    }
    PhysicsUpdate(deltaTime);
    
    bool colliding=false;
    
    for(auto block: mOwner->GetGame()->GetBlocks())
    {
        CollSide temp=FixCollision(mOwner->GetComponent<CollisionComponent>(),block->GetComponent<CollisionComponent>());
        if(temp==CollSide::SideX1||temp==CollSide::SideX2||
           temp==CollSide::SideY1||temp==CollSide::SideY2)
        {
            colliding=true;
        }
    }
    if(mVelocity.z<=0.0f || colliding==false)
    {
        if(mVelocity.z>0)
        {
            mVelocity.z=0;
        }
        ChangeState(MoveState::Falling);
    }
}


bool PlayerMove::CanWallClimb(CollSide inState)
{
    //we have already known the normal of the side with the offsetRecorder variable
    //called in FixCollision
    offsetRecorder.Normalize();
    float angleForward= Vector3::Dot(mOwner->GetForward(),offsetRecorder);
    if(angleForward<-0.9&&angleForward>-1.1)
    {
        Vector3 xyVelocity=mVelocity;
        xyVelocity.z=0;
        float angleVelocity= Vector3::Dot(Vector3::Normalize(xyVelocity),offsetRecorder);
        if(angleVelocity<-0.9&&angleVelocity>-1.1)
        {
            if(xyVelocity.Length()>350)
            {
                return true;
            }
        }
    }
    return false;
}

void PlayerMove::UpdateWallRun(float deltaTime)
{
    AddForce(mGravity);
    mWallRunTimer+=deltaTime;
    Mix_Resume(mRunningSFX);
    if(mWallRunTimer<0.4)
    {
        AddForce(mWallRunForce);
    }
    
    
    PhysicsUpdate(deltaTime);
    
    for(auto block: mOwner->GetGame()->GetBlocks())
    {
        FixCollision(mOwner->GetComponent<CollisionComponent>()
                     ,block->GetComponent<CollisionComponent>());
    }
    
    if(mVelocity.z<=0.0f)
    {
        ChangeState(MoveState::Falling);
    }
}


bool PlayerMove::CanWallRun(CollSide inState)
{
    offsetRecorder.Normalize();
    float angleForward= Vector3::Dot(mOwner->GetForward(),offsetRecorder);
    if(angleForward<0.6&&angleForward>-0.4)
    {
        Vector3 xyVelocity=mVelocity;
        xyVelocity.z=0;
        float angleVelocity= Vector3::Dot(Vector3::Normalize(xyVelocity),mOwner->GetForward());
        if(angleVelocity<1.3&&angleVelocity>0.7)
        {
            if(xyVelocity.Length()>350)
            {
                return true;
            }
        }
    }
    return false;
}
