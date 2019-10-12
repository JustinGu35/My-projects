#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	// TODO: Implement
    if(this->GetMax().x<other->GetMin().x ||other->GetMax().x<this->GetMin().x||
        this->GetMax().y<other->GetMin().y||other->GetMax().y<this->GetMin().y)
    {
        return false;
    }
	return true;
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
    Vector2 result(mOwner->GetPosition().x-(mWidth*mOwner->GetScale())/2,
                   mOwner->GetPosition().y-(mHeight*mOwner->GetScale())/2);
	return result;
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
    Vector2 result(mOwner->GetPosition().x+(mWidth*mOwner->GetScale())/2,
                   mOwner->GetPosition().y+(mHeight*mOwner->GetScale())/2);
    return result;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector2& offset)
{
	offset = Vector2::Zero;
	// TODO: Implement
    if(!this->Intersect(other))
    {
        return CollSide::None;
    }
    
    float dy1=other->GetMin().y-this->GetMax().y;
    float dy2=other->GetMax().y-this->GetMin().y;
    float dx1=other->GetMin().x-this->GetMax().x;
    float dx2=other->GetMax().x-this->GetMin().x;
    
    float temp=Math::Min(Math::Abs(dy1),Math::Abs(dy2));
    temp=Math::Min(Math::Abs(temp),Math::Abs(dx1));
    temp=Math::Min(Math::Abs(temp),Math::Abs(dx2));
    
    if(temp==Math::Abs(dy1)){
        offset.y=dy1;
        return  CollSide::Top;
    }
    else if(temp==Math::Abs(dy2)){
        offset.y=dy2;
        return CollSide::Bottom;
    }
    else if (temp==Math::Abs(dx1)){
        offset.x=dx1;
        return CollSide::Left;
    }
    else
    {
        offset.x=dx2;
        return CollSide::Right;
    }
}
