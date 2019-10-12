#include "Boss.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "Door.h"
#include "Fireball.h"
#include "Math.h"

Boss::Boss(Game* inGame)
:Actor(inGame),
enraged(false),
lastEnraged(false),
fireballTimer(0.0)
{
    mAS=new AnimatedSprite(this);
    mCC=new CollisionComponent(this);
    mEC=new EnemyComponent(this);
    
    std::vector<SDL_Texture*> idleAnim{
        GetGame()->GetTexture("Assets/Dragon/Idle0.png"),
        GetGame()->GetTexture("Assets/Dragon/Idle1.png")
        };
    mAS->AddAnimation("idle", idleAnim);
    
    std::vector<SDL_Texture*> attackAnim{
        GetGame()->GetTexture("Assets/Dragon/Attack0.png"),
        GetGame()->GetTexture("Assets/Dragon/Attack1.png")
        };
    mAS->AddAnimation("attack", attackAnim);
    
    std::vector<SDL_Texture*> enragedAnim{
        GetGame()->GetTexture("Assets/Dragon/Enraged0.png"),
        GetGame()->GetTexture("Assets/Dragon/Enraged1.png"),
        GetGame()->GetTexture("Assets/Dragon/Enraged2.png"),
        GetGame()->GetTexture("Assets/Dragon/Enraged3.png")
        };
    mAS->AddAnimation("enraged", enragedAnim);
    
    mAS->SetAnimation("idle");
    mCC->SetSize(50,64);
    
    mEC->SetHP(5);
    mEC->SetDamage(2);
    mEC->SetOnTakeDamage([this] {
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/BossHit.wav"),0);
        if(mEC->GetHP()<=2&&enraged==false)
        {
            enraged=true;
        }
    });
    mEC->SetOnDeath([this] {
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/BossDie.wav"),0);
        auto it=GetGame()->mDoors.find(GetGame()->getRoom());
        std::vector<Door*> tempDoors=it->second;
        for(auto door : tempDoors)
        {
            if(door->getState()=="Closed")
            {
                door->UpdateTexture(door->getDirection(),"Open");
                Mix_PlayChannel(-1,GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
            }
        }
    });
}


void Boss::OnUpdate(float deltaTime)
{
    if(enraged==false)
    {
        float preTime=fireballTimer;
        fireballTimer+=deltaTime;
        if(preTime<=1.75 && fireballTimer>=1.75)
        {
            mAS->SetAnimation("attack");
        }
        if(fireballTimer>=2.0)
        {
            fireballTimer=0.0;
            mAS->SetAnimation("idle");
            Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/Fireball.wav"),0);
            
            Fireball* tempF1=new Fireball(mGame);
            tempF1->SetPosition(mPosition);
            tempF1->SetRotation(-(Math::Pi*5)/6);
            tempF1->ChangeTexture("Assets/FireballGreen.png");
            
            Fireball* tempF2=new Fireball(mGame);
            tempF2->SetPosition(mPosition);
            tempF2->SetRotation((Math::Pi*5)/6);
            tempF2->ChangeTexture("Assets/FireballGreen.png");
            
            Fireball* tempF3=new Fireball(mGame);
            tempF3->SetPosition(mPosition);
            tempF3->SetRotation(Math::Pi);
            tempF3->ChangeTexture("Assets/FireballGreen.png");
        }
    }
    else{
        if(lastEnraged==false)
        {
            lastEnraged=true;
            fireballTimer=0.0;
            mAS->SetAnimation("enraged");
        }
        fireballTimer+=deltaTime;
        if(fireballTimer>=1.0)
        {
            fireballTimer=0.0;
            Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/Fireball.wav"),0);
            
            for(int i=0;i<=8;i++)
            {
                Fireball* tempF=new Fireball(mGame);
                tempF->SetPosition(mPosition);
                float angle=Math::Pi/2+(i/8.0)*Math::Pi;
                tempF->SetRotation(angle);
                tempF->ChangeTexture("Assets/FireballGreen.png");
            }
            
        }
    }
}
