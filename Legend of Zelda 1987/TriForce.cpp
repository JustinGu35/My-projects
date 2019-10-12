#include "TriForce.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "Collectible.h"
#include "Player.h"

TriForce::TriForce(Game* inGame)
:Actor(inGame)
{
    mAS=new AnimatedSprite(this);
    mCC=new CollisionComponent(this);
    mCC->SetSize(20,20);
    std::vector<SDL_Texture*> triforceAnim{
        GetGame()->GetTexture("Assets/Triforce0.png"),
        GetGame()->GetTexture("Assets/Triforce1.png")
        };
    mAS->AddAnimation("triforce", triforceAnim);
    mAS->SetAnimation("triforce");
    Collectible* tempCollectible=new Collectible(this);
    tempCollectible->SetOnCollect([this] {
        Mix_HaltChannel(mGame->soundtrack);
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/Triforce.ogg"),0);
        mGame->mPlayer->SetState(ActorState::Paused);
    });
}
