//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "Player.h"
#include "Spawner.h"
#include "TiledBGComponent.h"
#include "CSVHelper.h"
#include "Collider.h"
#include "Door.h"
#include "SecretBlock.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <SDL/SDL_image.h>

// TODO

Game::Game(){
    
}

bool Game::Initialize(){
    Random::Init();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }
    
    window = SDL_CreateWindow(
                              "Legend of Zelda",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              SDL_WINDOW_OPENGL
                              );
    
    if (window == NULL) {
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    int flags=IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    LoadData();
    preTime=SDL_GetTicks();
    off=false;
    camera.Set(0.0f,0.0f);
    return 1;
}

void Game::Shutdown(){
    Mix_CloseAudio();
    UnloadData();
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::RunLoop(){
    while(condition){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        /* handle your event here */
        if(event.type==SDL_QUIT){
            condition=false;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        condition=false;
    }
    
    //lab 2
    std::vector<class Actor*> tempList=mActors;
    for(unsigned int i=0;i<tempList.size();i++)
    {
        tempList[i]->ProcessInput(state);
    }
}
void Game::UpdateGame(){
    //get the delta
    unsigned int curTime=SDL_GetTicks();
    while (curTime<=preTime+16){
        curTime=SDL_GetTicks();
    }
    if(curTime>preTime+33){
        delta=(float)(0.033);
    }
    else{
        delta=(float)((curTime-preTime)*0.001);
    }
    preTime=curTime;
    
    
    
    //temp list to update (pending)
    std::vector<class Actor*> templist=mActors;
    for(unsigned int i=0;i<templist.size();i++)
    {
        templist[i]->Update(delta);
    }
    //list to destroy
    std::vector<class Actor*> toDes;
    for(unsigned int i=0;i<templist.size();i++)
    {
        if(templist[i]->GetState()==ActorState::Destroy){
            toDes.push_back(templist[i]);
        }
    }
    for(unsigned int i=0;i<toDes.size();i++)
    {
        delete toDes[i];
    }
}
void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for(unsigned int i=0;i<mSprites.size();i++)
    {
        if(mSprites[i]->IsVisible())
        {
            mSprites[i]->Draw(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::AddActor(class Actor* inActor)
{
    mActors.push_back(inActor);
}
void Game::RemoveActor(class Actor* outActor)
{
    std::vector<class Actor*>::iterator it=std::find(mActors.begin(),mActors.end(),outActor);
    mActors.erase(it);
}


void Game::LoadData(){
    //get the sound!!!!
    soundtrack=Mix_PlayChannel(-1,GetSound("Assets/Sounds/Music.ogg"),-1);
    
    
    //load room 1
    
    LoadRoom("Assets/Dungeon/Room1.csv");
    LoadRoom("Assets/Dungeon/Room2.csv");
    LoadRoom("Assets/Dungeon/Room3.csv");
    LoadRoom("Assets/Dungeon/Room4.csv");
    LoadRoom("Assets/Dungeon/Room5.csv");
    LoadRoom("Assets/Dungeon/Room6.csv");
    LoadRoom("Assets/Dungeon/Room7.csv");
    
    curRoom="Room1";
    
    Actor* tiles=new Actor(this);
    TiledBGComponent* tbgc= new TiledBGComponent(tiles);
    tbgc->LoadTileCSV("Assets/Dungeon/DungeonMapBG.csv",32,32);
    tbgc->SetTexture(GetTexture("Assets/Dungeon/DungeonTiles.png"));
    
}

void Game::UnloadData(){
    while(!mActors.empty())
    {
        delete mActors.back();
    }
    
    std::unordered_map<std::string,SDL_Texture*>::iterator it;
    for(it=mMap.begin();it!=mMap.end();++it){
        SDL_DestroyTexture(it->second);
    }
    mMap.clear();
    
    std::unordered_map<std::string,Mix_Chunk*>::iterator it2;
    for(it2=mSounds.begin();it2!=mSounds.end();++it2)
    {
        Mix_FreeChunk(it2->second);
    }
    mSounds.clear();
}

SDL_Texture* Game::GetTexture(std::string filename){
    std::unordered_map<std::string,SDL_Texture*>::iterator it=mMap.find(filename);
    if(it!=mMap.end()){
        return it->second;
    }
    else{
        SDL_Surface *image;
        image=IMG_Load(filename.c_str());
        if(!image) {
            printf("IMG_Load: %s\n", IMG_GetError());
            // handle error
            SDL_Log("fail to load %",filename.c_str());
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
        mMap.insert(std::make_pair(filename,texture));
        return texture;
    }
}


void Game::AddSprite(class SpriteComponent* inSprite)
{
    mSprites.push_back(inSprite);
    // mSprites is std::vector<SpriteComponent*>
    std::sort(mSprites.begin(), mSprites.end(),
              [](SpriteComponent* a, SpriteComponent* b) {
                  return a->GetDrawOrder() < b->GetDrawOrder();
              });
}
void Game::RemoveSprite(class SpriteComponent* outSprite)
{
    std::vector<SpriteComponent*>::iterator it=std::find(mSprites.begin(),mSprites.end(),outSprite);
    mSprites.erase(it);
}





Mix_Chunk* Game::GetSound(const std::string& filename)
{
    std::unordered_map<std::string,Mix_Chunk*>::iterator it=mSounds.find(filename);
    if(it==mSounds.end())
    {
        mSounds.insert(make_pair(filename,Mix_LoadWAV(filename.c_str())));
        return Mix_LoadWAV(filename.c_str());
    }
    else
    {
        return it->second;
    }
}



void Game::LoadRoom(std::string inRoom)
{
    std::ifstream input (inRoom);
    if(input.fail())
    {
        SDL_Log("Fail to read");
    }
    std::string roomName=inRoom;
    roomName.erase(roomName.begin(),roomName.begin()+15);//14 is the length of "Assets/Dungeon/"
    roomName.erase(roomName.end()-4,roomName.end());//4 is the length of ".csv"
    
    //set up the enemy list
    std::vector<Actor*> tempEnemies;
    mEnemies.insert(make_pair(roomName,tempEnemies));
    
    
    while(!input.eof())
    {
        std::string tempL;
        std::getline(input,tempL);
        if(tempL.size()!=0)
        {
            std::vector<std::string> temp=CSVHelper::Split(tempL);
            
            if(temp[0]=="Player")
            {
                int tempX=stoi(temp[1]);
                int tempY=stoi(temp[2]);
                mPlayer= new Player(this);
                Vector2 tempPos((float)tempX,(float)tempY);
                mPlayer->SetPosition(tempPos);
            }
            else if(temp[0]=="Collider")
            {
                int tempX=stoi(temp[1]);
                int tempY=stoi(temp[2]);
                int tempW=stoi(temp[3]);
                int tempH=stoi(temp[4]);
                Collider* tempC=new Collider(this);
                Vector2 tempPos((float)tempX+tempW/2,(float)tempY+tempH/2);
                tempC->SetPosition(tempPos);
                tempC->SetDimension(tempW,tempH);
                mColliders.push_back(tempC);
            }
            else if(temp[0]=="Door")
            {
                int tempX=stoi(temp[1]);
                int tempY=stoi(temp[2]);
                int tempW=stoi(temp[3]);
                int tempH=stoi(temp[4]);
                std::string tempDestination=temp[5];
                std::string tempDirection=temp[6];
                std::string tempState=temp[7];
                Door* tempD=new Door(this);
                Vector2 tempPos((float)tempX+tempW/2,(float)tempY+tempH/2);
                tempD->SetPosition(tempPos);
                tempD->setupDoor(tempDirection,tempState,tempDestination);
                std::unordered_map<std::string,std::vector<Door*>>::iterator it=mDoors.find(roomName);
                if(it!=mDoors.end())
                {
                    it->second.push_back(tempD);
                }
                else
                {
                    std::vector<Door*> temp;
                    temp.push_back(tempD);
                    mDoors.insert(make_pair(roomName,temp));
                }
                
            }
            
            else if(temp[0]=="SecretBlock")
            {
                int tempX=stoi(temp[1]);
                int tempY=stoi(temp[2]);
                int tempW=stoi(temp[3]);
                int tempH=stoi(temp[4]);
                std::string tempD=temp[6];
                SecretBlock* tempSB=new SecretBlock(this);
                Vector2 tempPos((float)tempX+tempW/2,(float)tempY+tempH/2);
                tempSB->SetPosition(tempPos);
                tempSB->setOriginalPosition(tempPos);
                tempSB->setDirection(tempD);
                
                std::unordered_map<std::string,std::vector<SecretBlock*>>::iterator it=mSecretBlocks.find(roomName);
                if(it!=mSecretBlocks.end())
                {
                    it->second.push_back(tempSB);
                }
                else
                {
                    std::vector<SecretBlock*> temp;
                    temp.push_back(tempSB);
                    mSecretBlocks.insert(make_pair(roomName,temp));
                }
            }
            
            else if(temp[0]!="Type")
            {
                std::string type=temp[0];
                int tempX=stoi(temp[1]);
                int tempY=stoi(temp[2]);
                int tempW=stoi(temp[3]);
                int tempH=stoi(temp[4]);
                Spawner* tempS=new Spawner(this);
                Vector2 tempPos((float)tempX+tempW/2,(float)tempY+tempH/2);
                tempS->SetPosition(tempPos);
                tempS->setType(type);
                std::unordered_map<std::string,std::vector<Spawner*>>::iterator it=mSpawners.find(roomName);
                if(it!=mSpawners.end())
                {
                    it->second.push_back(tempS);
                }
                else
                {
                    std::vector<Spawner*> temp;
                    temp.push_back(tempS);
                    mSpawners.insert(make_pair(roomName,temp));
                }
            }
        
        }
    }
}



void Game::setRoom(std::string inRoom)
{
    auto it=mEnemies.find(curRoom);
    if(it!=mEnemies.end())
    {
        for(auto enemy: it->second)
        {
            enemy->SetState(ActorState::Paused);
        }
    }
    
    curRoom=inRoom;
    
    it=mEnemies.find(curRoom);
    if(it!=mEnemies.end())
    {
        for(auto enemy: it->second)
        {
            enemy->SetState(ActorState::Active);
        }
    }
}


void Game::AddEnemy(std::string theRoom,Actor* inEnemy)
{
    auto it=mEnemies.find(theRoom);
    if(it!=mEnemies.end())
    {
        it->second.push_back(inEnemy);
    }
}


std::vector<class Actor*>& Game::GetEnemies(std::string theRoom)
{
    auto it =mEnemies.find(theRoom);
    return it->second;
}

void Game::RemoveEnemy(std::string theRoom,Actor* outEnemy)
{
    auto it=mEnemies.find(theRoom);
    auto it2=std::find(it->second.begin(),it->second.end(),outEnemy);
    it->second.erase(it2);
}
