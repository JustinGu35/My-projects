#include "LaserComponent.h"
#include "Actor.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Player.h"
#include "Block.h"
#include "PlayerMove.h"

LaserComponent::LaserComponent(Actor* inOwner)
:MeshComponent(inOwner,true)
{
    SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}


void LaserComponent::Draw(class Shader* shader)
{
    if (mMesh)
    {
        // Set the world transform
        for (auto line :mLines)
        {
            shader->SetMatrixUniform("uWorldTransform",
                transformHelper(line));
            
            // Set the active texture
            Texture* t = mMesh->GetTexture(mTextureIndex);
            if (t)
            {
                t->SetActive();
            }
            // Set the mesh's vertex array as active
            VertexArray* va = mMesh->GetVertexArray();
            va->SetActive();
            // Draw
            glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }
    }
}


void LaserComponent::Update(float deltaTime)
{
    mLines.clear();
    Vector3 start=mOwner->GetWorldPosition();
    Vector3 end=start+ mOwner->GetWorldForward()*500;
    LineSegment tempLine;
    tempLine.mStart=start;
    tempLine.mEnd=end;
    
    CastInfo tempInfo;
    bool mirroring=true;
    
    
    Actor* ignoringActor=mOwner->mParent;
    
    while(mirroring)
    {
        if(SegmentCast(mOwner->GetGame()->GetPlayer(),tempLine,tempInfo))
        {
            Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Laser.wav"),0);
            tempLine.mEnd=tempInfo.mPoint;
            mLines.push_back(tempLine);
            mirroring=false;
            Player* mPlayer=mOwner->GetGame()->GetPlayer();
            mPlayer->SetPosition(mPlayer->GetRespawnPos());
            mPlayer->SetRotation(0);
            mPlayer->GetComponent<PlayerMove>()->SetVelocityZero();
            mPlayer->GetComponent<PlayerMove>()->SetPendingForceZero();
            mPlayer->GetComponent<PlayerMove>()->ChangeState(MoveState::Falling);
            
        }
        else
        {
            if(SegmentCast(mOwner->GetGame()->GetBlocks(),tempLine,tempInfo,ignoringActor))
            {
                Block* tempBlock=dynamic_cast<Block*>(tempInfo.mActor);
                if(tempBlock->GetMirror())
                {
                    tempLine.mEnd=tempInfo.mPoint;
                    mLines.push_back(tempLine);
                    
                    ignoringActor=tempInfo.mActor;
                    Vector3 facing=tempLine.mEnd-tempLine.mStart;
                    facing.Normalize();
                    Matrix4 QuatRotation;
                    tempInfo.mNormal.Normalize();
                    float dotProduct=Vector3::Dot(tempInfo.mNormal,facing);
                    if(dotProduct==-1)
                    {
                        QuatRotation=Matrix4::CreateFromQuaternion(Quaternion::Identity);
                    }
                    else
                    {
                        float angle=Math::Acos(dotProduct);
                        Vector3 crossProduct=Vector3::Cross(facing,tempInfo.mNormal);
                        crossProduct.Normalize();
                        Quaternion temp(crossProduct,2*angle);
                        QuatRotation=Matrix4::CreateFromQuaternion(temp);
                    }
                    Vector3 result=Vector3::Transform(facing,QuatRotation);
                    result.Normalize();
                    tempLine.mStart=tempInfo.mPoint;
                    tempLine.mEnd=tempLine.mStart-result*500;//opposite direction
                    mLines.push_back(tempLine);
                }
                else
                {
                    tempLine.mEnd=tempInfo.mPoint;
                    mLines.push_back(tempLine);
                    mirroring=false;
                }
            }
            else
            {
                mLines.push_back(tempLine);
                mirroring=false;
            }
        }
    }
}

Matrix4 LaserComponent::transformHelper(LineSegment inLine)
{
    Vector3 facing=inLine.mEnd-inLine.mStart;
    facing.Normalize();
    Matrix4 QuatRotation;
    float dotProduct=Vector3::Dot(Vector3::UnitX,facing);
    if(dotProduct== 1.0f)
    {
        QuatRotation=Matrix4::CreateFromQuaternion(Quaternion::Identity);
    }
    else if(dotProduct==-1)
    {
        Quaternion temp(Vector3::UnitZ,Math::Pi);
        QuatRotation=Matrix4::CreateFromQuaternion(temp);
    }
    else
    {
        float angle=Math::Acos(dotProduct);
        Vector3 crossProduct=Vector3::Cross(Vector3::UnitX,facing);
        crossProduct.Normalize();
        Quaternion temp(crossProduct,angle);
        QuatRotation=Matrix4::CreateFromQuaternion(temp);
    }
    Matrix4 mWorldTransform = Matrix4::CreateScale(inLine.Length(),1,1)
        * QuatRotation
        * Matrix4::CreateTranslation(inLine.PointOnSegment(0.5));
    return mWorldTransform;
}
