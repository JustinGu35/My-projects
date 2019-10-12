//
//  Player.cpp
//  Game-mac
//
//  Created by Runshi Gu on 9/19/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "PlayerMove.h"

Player::Player(Game* inGame)
:Actor(inGame),
HitPoint(10),
keys(0),
invulnerabilityTimer(0.0)
{
    mAS=new AnimatedSprite(this,200);
   
    //add animations
    std::vector<SDL_Texture*> attackUpAnim{
    GetGame()->GetTexture("Assets/Link/AttackUp.png")
    };
    mAS->AddAnimation("attackUp", attackUpAnim);
    
    std::vector<SDL_Texture*> attackDownAnim{
    GetGame()->GetTexture("Assets/Link/AttackDown.png")
    };
    mAS->AddAnimation("attackDown", attackDownAnim);
    
    std::vector<SDL_Texture*> attackLeftAnim{
    GetGame()->GetTexture("Assets/Link/AttackLeft.png")
    };
    mAS->AddAnimation("attackLeft", attackLeftAnim);
    
    std::vector<SDL_Texture*> attackRightAnim{
    GetGame()->GetTexture("Assets/Link/AttackRight.png")
    };
    mAS->AddAnimation("attackRight", attackRightAnim);
    
    std::vector<SDL_Texture*> walkUpAnim{
        GetGame()->GetTexture("Assets/Link/WalkUp0.png"),
        GetGame()->GetTexture("Assets/Link/WalkUp1.png")
        };
    mAS->AddAnimation("walkUp", walkUpAnim);
    
    std::vector<SDL_Texture*> walkDownAnim{
        GetGame()->GetTexture("Assets/Link/WalkDown0.png"),
        GetGame()->GetTexture("Assets/Link/WalkDown1.png")
        };
    mAS->AddAnimation("walkDown", walkDownAnim);
    
    std::vector<SDL_Texture*> walkLeftAnim{
        GetGame()->GetTexture("Assets/Link/WalkLeft0.png"),
        GetGame()->GetTexture("Assets/Link/WalkLeft1.png")
        };
    mAS->AddAnimation("walkLeft", walkLeftAnim);
    
    std::vector<SDL_Texture*> walkRightAnim{
        GetGame()->GetTexture("Assets/Link/WalkRight0.png"),
        GetGame()->GetTexture("Assets/Link/WalkRight1.png")
        };
    mAS->AddAnimation("walkRight", walkRightAnim);
    
    mAS->SetAnimation("walkUp");
    mAS->SetIsPaused(true);
    mCC=new CollisionComponent(this);
    mCC->SetSize(20,20);
    
    mPM=new PlayerMove(this);
}

Player::~Player()
{
    
}

void Player::TakeDamage(int amount)
{
    if(invulnerabilityTimer<=0.0)
    {
        HitPoint-=amount;
        invulnerabilityTimer=0.5;
        if(HitPoint<=0)
        {
            SetState(ActorState::Paused);
            Mix_HaltChannel(mGame->soundtrack);
            Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/LinkDie.wav"),0);
        }
        else{
            Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/LinkHit.wav"),0);
        }
    }
}

void Player::OnUpdate(float deltaTime)
{
    if(invulnerabilityTimer>0.0)
    {
        invulnerabilityTimer-=deltaTime;
    }
}
