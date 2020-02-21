//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include <fstream>
#include "Renderer.h"
#include "Random.h"
#include "Player.h"
#include "LevelLoader.h"
#include <sstream>
#include "Checkpoint.h"
#include "Arrow.h"
#include "SecurityCamera.h"
#include <SDL/SDL_ttf.h>

Game::Game()
:mIsRunning(true)
{
	mPlayer=nullptr;
    mRenderer=nullptr;
    mTicksCount= (Uint32)0;
}

bool Game::Initialize()
{
	Random::Init();

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// TODO: Create renderer
    Renderer* temp=new Renderer(this);
    mRenderer=temp;
    if(!mRenderer->Initialize(SCREEN_WIDTH,SCREEN_HEIGHT))
    {
        return false;
    }
    
    
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(32);
    Mix_GroupChannels(22,31,1);
    TTF_Init();
	LoadData();
    
    SDL_SetRelativeMouseMode(SDL_TRUE); // Enable relative mouse mode
    SDL_GetRelativeMouseState(nullptr, nullptr); // Clear any saved values

	mTicksCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
        if(!mNextLevel.empty())
        {
            LoadNextLevel();
        }
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.01667f)
	{
		deltaTime = 0.01667f;
	}
	mTicksCount = SDL_GetTicks();
	
	// Make copy of actor vector
	// (iterate over this in case new actors are created)
	std::vector<Actor*> copy = mActors;
	// Update all actors
	for (auto actor : copy)
	{
		actor->Update(deltaTime);
	}

	// Add any actors to destroy to a temp vector
	std::vector<Actor*> destroyActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == ActorState::Destroy)
		{
			destroyActors.emplace_back(actor);
		}
	}

	// Delete the destroyed actors (which will
	// remove them from mActors)
	for (auto actor : destroyActors)
	{
		delete actor;
	}
    
}

void Game::GenerateOutput()
{
	// TODO: tell renderer to draw
    mRenderer->Draw();
}

void Game::LoadData()
{
    
    
    Matrix4 myProjection=Matrix4::CreatePerspectiveFOV(1.22f,1024.0f,768.0f,10.0f,10000.0f);
    mRenderer->SetProjectionMatrix(myProjection);
    Vector3 eye(-300,0,100);
    Vector3 target(20,0,0);
    Matrix4 view=Matrix4::CreateLookAt(eye,target,Vector3::UnitZ);
    mRenderer->SetViewMatrix(view);
    
    LevelLoader::Load(this,"Assets/Tutorial.json");
    mCheckpoints.front()->SetActive(true);
    mArrow=new Arrow(this,nullptr);
    
    GetSound("Assets/Sounds/CameraMotor.wav");
    GetSound("Assets/Sounds/CameraMotorStop.wav");
    GetSound("Assets/Sounds/Checkpoint.wav");
    GetSound("Assets/Sounds/Coin.wav");
    GetSound("Assets/Sounds/Jump.wav");
    GetSound("Assets/Sounds/Land.wav");
    GetSound("Assets/Sounds/Laser.wav");
    GetSound("Assets/Sounds/Running.wav");
    GetSound("Assets/Sounds/SecurityDetected.wav");
    GetSound("Assets/Sounds/Music.ogg");
    
    Mix_PlayChannel(-1,GetSound("Assets/Sounds/Music.ogg"),-1);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy sounds
	for (auto s : mSounds)
	{
		Mix_FreeChunk(s.second);
	}
	mSounds.clear();
}

Mix_Chunk* Game::GetSound(const std::string& fileName)
{
	Mix_Chunk* chunk = nullptr;
	auto iter = mSounds.find(fileName);
	if (iter != mSounds.end())
	{
		chunk = iter->second;
	}
	else
	{
		chunk = Mix_LoadWAV(fileName.c_str());
		if (!chunk)
		{
			SDL_Log("Failed to load sound file %s", fileName.c_str());
			return nullptr;
		}

		mSounds.emplace(fileName, chunk);
	}
	return chunk;
}

void Game::Shutdown()
{
	UnloadData();
	Mix_CloseAudio();
	// TODO: Delete renderer
    mRenderer->Shutdown();
    delete mRenderer;
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		auto iter2 = mActors.end() - 1;
		std::iter_swap(iter, iter2);
		mActors.pop_back();
	}
}

void Game::AddBlock(class Actor* inBlock)
{
    mBlocks.push_back(inBlock);
}
void Game::RemoveBlock(class Actor* outBlock)
{
    auto it=std::find(mBlocks.begin(),mBlocks.end(),outBlock);
    if(it!=mBlocks.end())
    {
        mBlocks.erase(it);
    }
}

void Game::LoadNextLevel()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    mActors.clear();
    while(!mCheckpoints.empty())
    {
        mCheckpoints.pop();
    }
    LevelLoader::Load(this,mNextLevel);
    if(!mCheckpoints.empty())
    {
        mCheckpoints.front()->SetActive(true);
    }
    mArrow=new Arrow(this,nullptr);
    mNextLevel.clear();
}


void Game::AddSecurityCamera(SecurityCamera* inSC)
{
    mSecurityCameras.push_back(inSC);
}
void Game::RemoveSecurityCamera(SecurityCamera* outSC)
{
    auto it=std::find(mSecurityCameras.begin(),mSecurityCameras.end(),outSC);
    if(it!=mSecurityCameras.end())
    {
        mSecurityCameras.erase(it);
    }
}
