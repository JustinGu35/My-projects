#include "Skeleton.h"
#include "Game.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "Random.h"
#include "Fireball.h"
#include "Math.h"
#include "Player.h"

Skeleton::Skeleton(Game* inGame)
:Actor(inGame)
{
    mAS=new AnimatedSprite(this);
    mCC=new CollisionComponent(this);
    mCC->SetSize(25,25);
    
    
    std::vector<SDL_Texture*> skeletonAnim{
        GetGame()->GetTexture("Assets/Skeleton0.png"),
        GetGame()->GetTexture("Assets/Skeleton1.png")
        };
    mAS->AddAnimation("skeletonAnim", skeletonAnim);
    mAS->SetAnimation("skeletonAnim");
    mEC=new EnemyComponent(this);
    
    timer=Random::GetFloatRange(1.0f,3.0f);
    
    mEC->SetOnDeath([this] {
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/EnemyDie.wav"),0);
    });
}

void Skeleton::OnUpdate(float deltaTime)
{
    timer-=deltaTime;
    if(timer<=0.0)
    {
        timer=4.0;
        Fireball* tempF=new Fireball(mGame);
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/Fireball.wav"),0);
        tempF->SetPosition(mPosition);
        float xDistance=mGame->mPlayer->GetPosition().x-mPosition.x;
        float yDistance=mGame->mPlayer->GetPosition().y-mPosition.y;
        tempF->SetRotation(Math::Atan2(-yDistance,xDistance));
    }
    
}
