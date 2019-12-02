#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game,Actor* parent)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
    ,mParent(parent)
{
	// TODO
    if(mParent==nullptr)
    {
        mGame->AddActor(this);
    }
    else{
        mParent->AddChild(this);
    }
}

Actor::~Actor()
{
    while (!mChildren.empty())
    {
        delete mChildren.back();
    }
	// TODO
    if(mParent==nullptr)
    {
        mGame->RemoveActor(this);
    }
    else{
        mParent->RemoveChild(this);
    }
    unsigned int temp=(unsigned int)mComponents.size();
    for(unsigned int i=0;i<temp;i++ )
    {
        delete mComponents[i];
    }
    mComponents.clear();
}

void Actor::Update(float deltaTime)
{
    CalcWorldTransform();
	// TODO
    if(mState==ActorState::Active)
    {
        for(unsigned int i=0;i<mComponents.size();i++)
        {
            mComponents[i]->Update(deltaTime);
        }
        OnUpdate(deltaTime);
    }
    CalcWorldTransform();
    for (auto child : mChildren)
    {
        child->Update(deltaTime);
    }
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// TODO
    if(mState==ActorState::Active)
    {
        for(unsigned int i=0;i<mComponents.size();i++)
        {
            mComponents[i]->ProcessInput(keyState);
        }
        OnProcessInput(keyState);
    }
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

Vector3 Actor::GetForward()
{
    float x=cos(mRotation);
    float y=sin(mRotation);
    float z=0.0f;
    Vector3 output(x,y,z);
    return output;
}

Vector3 Actor::GetRight()
{
    float x=cos(mRotation+Math::PiOver2);
    float y=sin(mRotation+Math::PiOver2);
    float z=0.0f;
    Vector3 output(x,y,z);
    return output;
}


Vector3 Actor::GetQuatForward()
{
    Vector3 temp=Vector3::Transform(Vector3::UnitX,mQuaternion);
    temp.Normalize();
    return temp;
}


void Actor::CalcWorldTransform()
{
    Matrix4 QuatRotation=Matrix4::CreateFromQuaternion(mQuaternion);
    mWorldTransform = Matrix4::CreateScale(mScale) * Matrix4::CreateRotationZ(mRotation)
                    * QuatRotation
                    * Matrix4::CreateTranslation(mPosition);
    if(mParent!=nullptr)
    {
        if(mInheritScale)
        {
            mWorldTransform*=mParent->GetWorldTransform();
        }
        else
        {
            mWorldTransform*=mParent->CalcWorldRotTrans();
        }
    }
}
Matrix4 Actor::CalcWorldRotTrans()
{
    Matrix4 QuatRotation=Matrix4::CreateFromQuaternion(mQuaternion);
    Matrix4 result = Matrix4::CreateRotationZ(mRotation)
                    * QuatRotation
                    * Matrix4::CreateTranslation(mPosition);
    if(mParent!=nullptr)
    {
        if(mInheritScale)
        {
            result*=mParent->GetWorldTransform();
        }
        else
        {
            result*=mParent->CalcWorldRotTrans();
        }
    }
    
    return result;
}



Vector3 Actor::GetWorldPosition()
{
    return mWorldTransform.GetTranslation();
}
Vector3 Actor::GetWorldForward()
{
    return mWorldTransform.GetXAxis();
}


void Actor::AddChild(Actor* inChild)
{
    mChildren.push_back(inChild);
}
void Actor::RemoveChild(Actor* outChild)
{
    auto it=std::find(mChildren.begin(),mChildren.end(),outChild);
    if(it!=mChildren.end())
    {
        mChildren.erase(it);
    }
}
