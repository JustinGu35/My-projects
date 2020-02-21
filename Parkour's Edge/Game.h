#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include "Math.h"

class Game
{
public:
    const float SCREEN_WIDTH=1024.0f;
    const float SCREEN_HEIGHT=768.0f;
    
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }
    class Player* GetPlayer(){return mPlayer;}
    void SetPlayer(class Player* inPlayer){mPlayer=inPlayer;}
    
    void AddBlock(class Actor* inBlock);
    void RemoveBlock(class Actor* outBlock);
    std::vector<class Actor*>& GetBlocks(){return mBlocks;}
    std::queue<class Checkpoint*> mCheckpoints;
    void SetNextLevel(std::string inS){mNextLevel=inS;}
    void LoadNextLevel();
    
    void AddTime(float deltaTime){time+=deltaTime;}
    float GetTime(){return time;}
    void Addcoins(){coins++;}
    int Getcoins(){return coins;}
    void SetTextTimer(float inT){textTimer=inT;}
    float GetTextTimer(){return textTimer;}
    void SetDisplayText(std::string inS){displayText=inS;}
    std::string GetDisplayText(){return displayText;}
    
    void AddSecurityCamera(class SecurityCamera* inSC);
    void RemoveSecurityCamera(class SecurityCamera* outSC);
    std::vector<class SecurityCamera*>& GetSecurityCameras(){return mSecurityCameras;}
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
    
	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	class Renderer* mRenderer;
    class Player* mPlayer;

	Uint32 mTicksCount;
	bool mIsRunning;
    
    std::vector<class Actor*> mBlocks;
    std::string mNextLevel;
    class Arrow* mArrow;
    
    float time=0;
    int coins=0;
    std::string displayText = "";
    float textTimer=0;
    
    std::vector<class SecurityCamera*> mSecurityCameras;
};
