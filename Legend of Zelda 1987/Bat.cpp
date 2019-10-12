#include "Bat.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "Random.h"
#include "Collider.h"

Bat::Bat(Game* inGame)
:Actor(inGame)
{
    mAS=new AnimatedSprite(this);
    mCC=new CollisionComponent(this);
    mCC->SetSize(25,25);
    
    
    std::vector<SDL_Texture*> BatAnim{
        GetGame()->GetTexture("Assets/Bat0.png"),
        GetGame()->GetTexture("Assets/Bat1.png")
        };
    mAS->AddAnimation("batAnim", BatAnim);
    mAS->SetAnimation("batAnim");
    mEC=new EnemyComponent(this);
    timeElapsed=0;
    Vector2 Max(1,1);
    Vector2 Min(-1,-1);
    direction=Random::GetVector(Min,Max);
    mEC->SetOnDeath([this] {
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/EnemyDie.wav"),0);
    });
}

void Bat::OnUpdate(float deltaTime)
{
    timeElapsed+=deltaTime;
    mPosition+=direction*deltaTime*SPEED;
    if(timeElapsed>=3.0)
    {
        timeElapsed=0.0;
        Vector2 Max(1,1);
        Vector2 Min(-1,-1);
        direction=Random::GetVector(Min,Max);
    }
    
    Vector2 offset;
    for(int i=0;i<mGame->mColliders.size();i++)
    {
        CollSide tempState=mCC->GetMinOverlap(mGame->mColliders[i]->mCC,offset);
        if(tempState!=CollSide::None)
        {
            mPosition+=offset;
            if(tempState==CollSide::Top)
            {
                direction.y=0-direction.y;
            }
            else if(tempState==CollSide::Bottom)
            {
                direction.y=0-direction.y;
            }
            else if(tempState==CollSide::Left)
            {
                direction.x=0-direction.x;
            }
            else
            {
                direction.x=0-direction.x;
            }
        }
    }
}
