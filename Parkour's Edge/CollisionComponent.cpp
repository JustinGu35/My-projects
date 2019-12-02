#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
,mDepth(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	Vector3 aMin = GetMin();
	Vector3 aMax = GetMax();
	Vector3 bMin = other->GetMin();
	Vector3 bMax = other->GetMax();

	bool no = aMax.x < bMin.x ||
		aMax.y < bMin.y ||
		aMax.z < bMin.z ||
		bMax.x < aMin.x ||
		bMax.y < aMin.y ||
		bMax.z < aMin.z;

	return !no;
}

Vector3 CollisionComponent::GetMin() const
{
	Vector3 v = mOwner->GetPosition();
	v.x -= mDepth * mOwner->GetScale() / 2.0f;
	v.y -= mWidth * mOwner->GetScale() / 2.0f;
	v.z -= mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

Vector3 CollisionComponent::GetMax() const
{
	Vector3 v = mOwner->GetPosition();
	v.x += mDepth * mOwner->GetScale() / 2.0f;
	v.y += mWidth * mOwner->GetScale() / 2.0f;
	v.z += mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

const Vector3& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector3& offset)
{
	offset = Vector3::Zero;
	// TODO: Implement
    if(!this->Intersect(other))
    {
        return CollSide::None;
    }
    
    Vector3 aMin=this->GetMin();
    Vector3 aMax=this->GetMax();
    Vector3 bMin=other->GetMin();
    Vector3 bMax=other->GetMax();
    
    float dy1=bMin.y-aMax.y;
    float dy2=bMax.y-aMin.y;
    float dx1=bMin.x-aMax.x;
    float dx2=bMax.x-aMin.x;
    float dz1=bMin.z-aMax.z;
    float dz2=bMax.z-aMin.z;
    
    float temp=Math::Min(Math::Abs(dy1),Math::Abs(dy2));
    temp=Math::Min(Math::Abs(temp),Math::Abs(dx1));
    temp=Math::Min(Math::Abs(temp),Math::Abs(dx2));
    temp=Math::Min(Math::Abs(temp),Math::Abs(dz1));
    temp=Math::Min(Math::Abs(temp),Math::Abs(dz2));
    
    if(temp==Math::Abs(dz2)){
        offset.z=dz2;
        return  CollSide::Top;
    }
    else if(temp==Math::Abs(dz1)){
        offset.z=dz1;
        return  CollSide::Bottom;
    }
    else
    {
        if(temp==Math::Abs(dy1)){
            offset.y=dy1;
            return CollSide::SideY1;
        }
        else if(temp==Math::Abs(dy2)){
            offset.y=dy2;
            return CollSide::SideY2;
        }
        else if (temp==Math::Abs(dx1)){
            offset.x=dx1;
            return CollSide::SideX1;
        }
        else
        {
            offset.x=dx2;
            return CollSide::SideX2;
        }
    }
    
    
    
	return CollSide::None;
}
