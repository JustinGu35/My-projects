#pragma once

// TODO
#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#include "Math.h"
#include <unordered_map>
#include <string>
#include "SDL/SDL_mixer.h" 

class Game
{
public:
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 448;
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void AddActor(class Actor* inActor);
    void RemoveActor(class Actor* outActor);
    SDL_Texture* GetTexture(std::string filename);
    void AddSprite(class SpriteComponent* inSprite);
    void RemoveSprite(class SpriteComponent* outSprite);
    
    void AddEnemy(std::string theRoom,class Actor* inEnemy);
    std::vector<class Actor*>& GetEnemies(std::string theRoom);
    void RemoveEnemy(std::string theRoom,class Actor* outEnemy);
    //load a room csv
    void LoadRoom(std::string inRoom);
    
    void setRoom(std::string inRoom);
    std::string getRoom(){return curRoom;}
    
    class Player* mPlayer;
    std::vector<class Collider*> mColliders;
    Vector2 camera;
    
    Mix_Chunk* GetSound(const std::string& filename);
    int soundtrack;
    
    std::unordered_map<std::string, std::vector<class Door*> >mDoors;
    std::unordered_map<std::string, std::vector<class SecretBlock*> >mSecretBlocks;
    std::unordered_map<std::string, std::vector<class Spawner*> > mSpawners;
    
private:
    
    void LoadData();
    void UnloadData();
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool condition=true;
    unsigned int preTime;
    float delta;
    int direction;
    //to check if the ball is off
    bool off;
    std::vector<class Actor*> mActors;
    std::unordered_map<std::string, SDL_Texture*> mMap;
    std::vector<class SpriteComponent*> mSprites;
    std::unordered_map<std::string, Mix_Chunk*> mSounds;
    std::unordered_map<std::string, std::vector<class Actor*> > mEnemies;
    std::string curRoom;
};
