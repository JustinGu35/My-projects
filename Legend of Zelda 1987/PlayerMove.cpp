#include "PlayerMove.h"
#include "Actor.h"
#include "Game.h"
#include "Player.h"
#include "CollisionComponent.h"
#include "Collider.h"
#include "SpriteComponent.h"
#include "Door.h"
#include "SecretBlock.h"
#include "Spawner.h"
#include "EnemyComponent.h"
#include "AnimatedSprite.h"
#include <SDL/SDL.h>
#include "Sword.h"


PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
{
    direction.Set(0.0f,0.0f);
    facing=0;
    mSword=new Sword(mOwner->GetGame());
    attackTimer=0.0;
    attacking=false;
    isSpacePressed=false;
}

void PlayerMove::Update(float deltaTime)
{
    Vector2 tempPos=mOwner->GetPosition();
    
    Vector2 offset(0.0,0.0);
    
    if(attackTimer>0.0)
    {
        attackTimer-=deltaTime;
        if(attacking==false)
        {
            attacking=true;
            Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/SwordSlash.wav"),0);
            UpdateSword();
        }
        std::vector<Actor*> tempE=mOwner->GetGame()->GetEnemies(mOwner->GetGame()->getRoom());
        for(auto enemy: tempE)
        {
            CollSide tempState=mSword->GetComponent<CollisionComponent>()->GetMinOverlap
                (enemy->GetComponent<CollisionComponent>(),offset);
            if(tempState!=CollSide::None)
            {
                enemy->GetComponent<EnemyComponent>()->TakeDamage(1);
            }
            else{
                CollSide contact=mOwner->GetComponent<CollisionComponent>()->GetMinOverlap
                    (enemy->GetComponent<CollisionComponent>(),offset);
                if(contact!=CollSide::None)
                {
                    mOwner->GetGame()->mPlayer->TakeDamage(enemy->GetComponent<EnemyComponent>()->getDamage());
                    tempPos+=offset;
                    if(contact==CollSide::Top)
                    {
                        tempPos.y-=TILE_WIDTH;
                    }
                    else if(contact==CollSide::Bottom)
                    {
                        tempPos.y+=TILE_WIDTH;
                    }
                    else if(contact==CollSide::Left)
                    {
                        tempPos.x-=TILE_WIDTH;
                    }
                    else if(contact==CollSide::Right)
                    {
                        tempPos.x+=TILE_WIDTH;
                    }
                    mOwner->SetPosition(tempPos);
                }
            }
        }
    }
    else
    {
        if(attacking==true)
        {
            attacking=false;
            UpdateSword();
        }
        
        if(direction.x==0 && direction.y==0)
        {
            mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(true);
        }
        else{
            tempPos+=direction*SPEED*deltaTime;
            mOwner->SetPosition(tempPos);
            if(facing==0)
            {
                mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkUp");
                mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
            }
            else if(facing==1)
            {
                mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkLeft");
                mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
            }
            else if(facing==2)
            {
                mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkDown");
                mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
            }
            else
            {
                mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkRight");
                mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
            }
        }
        
        
        
        std::vector<Actor*> tempE=mOwner->GetGame()->GetEnemies(mOwner->GetGame()->getRoom());
         for(auto enemy: tempE)
         {
        
             CollSide contact=mOwner->GetComponent<CollisionComponent>()->GetMinOverlap
                 (enemy->GetComponent<CollisionComponent>(),offset);
             if(contact!=CollSide::None)
             {
                 mOwner->GetGame()->mPlayer->TakeDamage(enemy->GetComponent<EnemyComponent>()->getDamage());
                 tempPos+=offset;
                 if(contact==CollSide::Top)
                 {
                     tempPos.y-=TILE_WIDTH;
                 }
                 else if(contact==CollSide::Bottom)
                 {
                     tempPos.y+=TILE_WIDTH;
                 }
                 else if(contact==CollSide::Left)
                 {
                     tempPos.x-=TILE_WIDTH;
                 }
                 else if(contact==CollSide::Right)
                 {
                     tempPos.x+=TILE_WIDTH;
                 }
                 mOwner->SetPosition(tempPos);
             }
         }
    }
    tempPos=mOwner->GetPosition();
    
    
    // for doors
    std::unordered_map<std::string,std::vector<Door*>>::iterator itD=mOwner->GetGame()->mDoors.find(mOwner->GetGame()->getRoom());
    std::vector<Door*> tempD;
    if(itD!=mOwner->GetGame()->mDoors.end())
    {
        tempD=itD->second;
    }
    
    for(auto mDoor : tempD)
    {
        CollSide tempState=mOwner->GetComponent<CollisionComponent>()->GetMinOverlap
        (mDoor->GetComponent<CollisionComponent>(),offset);
        if(tempState!=CollSide::None)
        {
            tempPos+=offset;
            
            if(mDoor->getDirection()=="Down" && facing==2)
            {
                if(mDoor->getState()=="Open")
                {
                    mOwner->GetGame()->setRoom(mDoor->getDestination());
                    auto it=mOwner->GetGame()->mSpawners.find(mDoor->getDestination());
                    if(it!=mOwner->GetGame()->mSpawners.end())
                    {
                        std::vector<Spawner*> tempS=it->second;
                        for(auto mSpawner : tempS)
                        {
                            mSpawner->activate();
                        }
                    }
                    tempPos.y+=TILE_WIDTH*4;
                }
                else if(mDoor->getState()=="Locked")
                {
                    int tempKey=mOwner->GetGame()->mPlayer->GetKey();
                    if(tempKey>0)
                    {
                        mOwner->GetGame()->mPlayer->RemoveKey();
                        mDoor->UpdateTexture(mDoor->getDirection(),"Open");
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                    }
                }
                break;
            }
            else if(mDoor->getDirection()=="Up" && facing==0)
            {
                if(mDoor->getState()=="Open")
                {
                    mOwner->GetGame()->setRoom(mDoor->getDestination());
                    auto it=mOwner->GetGame()->mSpawners.find(mDoor->getDestination());
                    if(it!=mOwner->GetGame()->mSpawners.end())
                    {
                        std::vector<Spawner*> tempS=it->second;
                        for(auto mSpawner : tempS)
                        {
                            mSpawner->activate();
                        }
                    }
                    tempPos.y-=TILE_WIDTH*4;
                }
                else if(mDoor->getState()=="Locked")
                {
                    int tempKey=mOwner->GetGame()->mPlayer->GetKey();
                    if(tempKey>0)
                    {
                        mOwner->GetGame()->mPlayer->RemoveKey();
                        mDoor->UpdateTexture(mDoor->getDirection(),"Open");
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                    }
                }
                break;
            }
            else if(mDoor->getDirection()=="Left" && facing==1)
            {
                if(mDoor->getState()=="Open")
                {
                    mOwner->GetGame()->setRoom(mDoor->getDestination());
                    auto it=mOwner->GetGame()->mSpawners.find(mDoor->getDestination());
                    if(it!=mOwner->GetGame()->mSpawners.end())
                    {
                        std::vector<Spawner*> tempS=it->second;
                        for(auto mSpawner : tempS)
                        {
                            mSpawner->activate();
                        }
                    }
                    tempPos.x-=TILE_WIDTH*4;
                }
                else if(mDoor->getState()=="Locked")
                {
                    int tempKey=mOwner->GetGame()->mPlayer->GetKey();
                    if(tempKey>0)
                    {
                        mOwner->GetGame()->mPlayer->RemoveKey();
                        mDoor->UpdateTexture(mDoor->getDirection(),"Open");
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                    }
                }
                break;
            }
            else if(mDoor->getDirection()=="Right" && facing==3)
            {
                if(mDoor->getState()=="Open")
                {
                    mOwner->GetGame()->setRoom(mDoor->getDestination());
                    auto it=mOwner->GetGame()->mSpawners.find(mDoor->getDestination());
                    if(it!=mOwner->GetGame()->mSpawners.end())
                    {
                        std::vector<Spawner*> tempS=it->second;
                        for(auto mSpawner : tempS)
                        {
                            mSpawner->activate();
                        }
                    }
                    tempPos.x+=TILE_WIDTH*4;
                }
                else if(mDoor->getState()=="Locked")
                {
                    int tempKey=mOwner->GetGame()->mPlayer->GetKey();
                    if(tempKey>0)
                    {
                        mOwner->GetGame()->mPlayer->RemoveKey();
                        mDoor->UpdateTexture(mDoor->getDirection(),"Open");
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                    }
                }
                break;
            }
            else{
                break;
            }
        }
    }
    mOwner->SetPosition(tempPos);
    
    
    
    
    //for the secret block
    //
    //
    std::unordered_map<std::string,std::vector<SecretBlock*>>::iterator itSB=mOwner->GetGame()->mSecretBlocks.find(mOwner->GetGame()->getRoom());
    std::vector<SecretBlock*> tempSB;
    if(itSB!=mOwner->GetGame()->mSecretBlocks.end())
    {
        tempSB=itSB->second;
    }
    for(auto theSB : tempSB)
    {
        CollSide SecretBlockState=mOwner->GetComponent<CollisionComponent>()->GetMinOverlap
                (theSB->GetComponent<CollisionComponent>(),offset);
        if(SecretBlockState != CollSide::None)
        {
            tempPos+=offset;
            Vector2 BlockPos=theSB->GetPosition();
            
            if(theSB->getDirection()=="Left" && SecretBlockState==CollSide::Left&&facing==3)
            {
                Vector2 originalPosition=theSB->getOriginalPosition();
                
                if(BlockPos.x<originalPosition.x+TILE_WIDTH)
                {
                    tempPos+=direction*(SPEED/2)*deltaTime;
                    BlockPos+=direction*(SPEED/2)*deltaTime;
                    
                    //if the block reach the maximum, open the doors
                    if(BlockPos.x>=originalPosition.x+TILE_WIDTH)
                    {
                        float difference=BlockPos.x-(originalPosition.x+TILE_WIDTH);
                        BlockPos.x-=difference;
                        tempPos.x-=difference;
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Secret.wav"),0);
                        auto it=mOwner->GetGame()->mDoors.find(mOwner->GetGame()->getRoom());
                        std::vector<Door*> tempDoors=it->second;
                        for(auto door : tempDoors)
                        {
                            if(door->getState()=="Closed")
                            {
                                door->UpdateTexture(door->getDirection(),"Open");
                                Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                            }
                        }
                    }
                }
            }
            
            else if(theSB->getDirection()=="Right" && SecretBlockState==CollSide::Right&&facing==1)
            {
                Vector2 originalPosition=theSB->getOriginalPosition();
                
                if(BlockPos.x>originalPosition.x-TILE_WIDTH)
                {
                    tempPos+=direction*(SPEED/2)*deltaTime;
                    BlockPos+=direction*(SPEED/2)*deltaTime;
                    
                    //if the block reach the maximum, open the doors
                    if(BlockPos.x<=originalPosition.x-TILE_WIDTH)
                    {
                        float difference=BlockPos.x-(originalPosition.x-TILE_WIDTH);
                        BlockPos.x-=difference;
                        tempPos.x-=difference;
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Secret.wav"),0);
                        auto it=mOwner->GetGame()->mDoors.find(mOwner->GetGame()->getRoom());
                        std::vector<Door*> tempDoors=it->second;
                        for(auto door : tempDoors)
                        {
                            if(door->getState()=="Closed")
                            {
                                door->UpdateTexture(door->getDirection(),"Open");
                                Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                            }
                        }
                    }
                }
            }
            
            else if(theSB->getDirection()=="Up" && SecretBlockState==CollSide::Top&&facing==2)
            {
                Vector2 originalPosition=theSB->getOriginalPosition();
                
                if(BlockPos.y<originalPosition.y+TILE_WIDTH)
                {
                    tempPos+=direction*(SPEED/2)*deltaTime;
                    BlockPos+=direction*(SPEED/2)*deltaTime;
                    
                    //if the block reach the maximum, open the doors
                    if(BlockPos.y>=originalPosition.y+TILE_WIDTH)
                    {
                        float difference=BlockPos.y-(originalPosition.y+TILE_WIDTH);
                        BlockPos.y-=difference;
                        tempPos.y-=difference;
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Secret.wav"),0);
                        auto it=mOwner->GetGame()->mDoors.find(mOwner->GetGame()->getRoom());
                        std::vector<Door*> tempDoors=it->second;
                        for(auto door : tempDoors)
                        {
                            if(door->getState()=="Closed")
                            {
                                door->UpdateTexture(door->getDirection(),"Open");
                                Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                            }
                        }
                    }
                }
            }
            else if(theSB->getDirection()=="Down" && SecretBlockState==CollSide::Bottom&&facing==0)
            {
                Vector2 originalPosition=theSB->getOriginalPosition();
                
                if(BlockPos.y>originalPosition.y-TILE_WIDTH)
                {
                    tempPos+=direction*(SPEED/2)*deltaTime;
                    BlockPos+=direction*(SPEED/2)*deltaTime;
                    
                    //if the block reach the maximum, open the doors
                    if(BlockPos.y<=originalPosition.y-TILE_WIDTH)
                    {
                        float difference=BlockPos.y-(originalPosition.y-TILE_WIDTH);
                        BlockPos.y-=difference;
                        tempPos.y-=difference;
                        Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/Secret.wav"),0);
                        auto it=mOwner->GetGame()->mDoors.find(mOwner->GetGame()->getRoom());
                        std::vector<Door*> tempDoors=it->second;
                        for(auto door : tempDoors)
                        {
                            if(door->getState()=="Closed")
                            {
                                door->UpdateTexture(door->getDirection(),"Open");
                                Mix_PlayChannel(-1,mOwner->GetGame()->GetSound("Assets/Sounds/DoorOpen.wav"),0);
                            }
                        }
                    }
                }
            }
            
            theSB->SetPosition(BlockPos);
            mOwner->SetPosition(tempPos);
        }
        
    }
    
    
    
    for(int i=0;i<mOwner->GetGame()->mColliders.size();i++)
    {
        CollSide tempState=mOwner->GetComponent<CollisionComponent>()->GetMinOverlap
                        (mOwner->GetGame()->mColliders[i]->mCC,offset);
        if(tempState!=CollSide::None)
        {
            tempPos+=offset;
        }
    }
    mOwner->SetPosition(tempPos);
    
    
    tempPos=mOwner->GetPosition();
    //adjust for camera
    tempPos.x-=mOwner->GetGame()->WINDOW_WIDTH/2;
    tempPos.y-=mOwner->GetGame()->WINDOW_HEIGHT/2;
    mOwner->GetGame()->camera.x=tempPos.x;
    mOwner->GetGame()->camera.y=tempPos.y;
    
}
void PlayerMove::ProcessInput(const Uint8* keyState)
{
    //indicator of left or right
    int horizontal=0;
    if(keyState[SDL_SCANCODE_LEFT])
    {
        horizontal--;
    }
    if(keyState[SDL_SCANCODE_RIGHT])
    {
        horizontal++;
    }
    
    int vertical=0;
    if(keyState[SDL_SCANCODE_DOWN])
    {
        vertical--;
    }
    if(keyState[SDL_SCANCODE_UP])
    {
        vertical++;
    }
    if(keyState[SDL_SCANCODE_SPACE])
    {
        if(isSpacePressed==false)
        {
            isSpacePressed=true;
            if(attackTimer<=0.0)
            {
                attackTimer=0.25;
            }
        }
    }
    else
    {
        if(isSpacePressed==true)
        {
            isSpacePressed=false;
        }
    }
    
    //set the direction according to indicators
    
    //only left or right they are the priorities
    if(horizontal!=0)
    {
        if(horizontal==1)
        {
            direction.Set(1,0);
            facing=3;
        }
        else
        {
            direction.Set(-1,0);
            facing=1;
        }
    }
    
    //only up or down
    else{
        if(vertical!=0)
        {
            if(vertical==1)
            {
                direction.Set(0,-1);
                facing=0;
            }
            else
            {
                direction.Set(0,1);
                facing=2;
            }
        }
        else{
            direction.Set(0,0);
        }
    }
    
    
}



void PlayerMove::UpdateSword()
{
    if(attacking==false)
    {
        mSword->getSprite()->SetIsVisible(false);
        if(facing==0)
        {
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkUp",true);
        }
        else if(facing==1)
        {
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkLeft",true);
        }
        else if(facing==2)
        {
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkDown",true);
        }
        else
        {
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkRight",true);
        }
    }
    else
    {
        mSword->getSprite()->SetIsVisible(true);
        Vector2 offset;
        if(facing==0)
        {
            mSword->getSprite()->SetTexture(mOwner->GetGame()->GetTexture("Assets/Sword/Up.png"));
            offset.Set(-8,-16);
            mSword->SetPosition(mOwner->GetPosition()+offset);
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("attackUp",true);
        }
        else if(facing==1)
        {
            mSword->getSprite()->SetTexture(mOwner->GetGame()->GetTexture("Assets/Sword/Left.png"));
            offset.Set(-16,4);
            mSword->SetPosition(mOwner->GetPosition()+offset);
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("attackLeft",true);
        }
        else if(facing==2)
        {
            mSword->getSprite()->SetTexture(mOwner->GetGame()->GetTexture("Assets/Sword/Down.png"));
            offset.Set(8,16);
            mSword->SetPosition(mOwner->GetPosition()+offset);
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("attackDown",true);
        }
        else if(facing==3)
        {
            mSword->getSprite()->SetTexture(mOwner->GetGame()->GetTexture("Assets/Sword/Right.png"));
            offset.Set(16,4);
            mSword->SetPosition(mOwner->GetPosition()+offset);
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("attackRight",true);
        }
    }
}
