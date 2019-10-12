#include "Key.h"
#include "Game.h"
#include "Player.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Collectible.h"

Key::Key(Game* inGame)
:Actor(inGame)
{
    CollisionComponent* tempC=new CollisionComponent(this);
    SpriteComponent* tempS=new SpriteComponent(this);
    tempS->SetTexture(mGame->GetTexture("Assets/Key.png"));
    tempC->SetSize(16,32);
    Collectible* tempCollectible=new Collectible(this);
    tempCollectible->SetOnCollect([this] {
        mGame->mPlayer->AddKey();
        Mix_PlayChannel(-1,mGame->GetSound("Assets/Sounds/Key.wav"),0);
    });
}
