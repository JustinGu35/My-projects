#include "AnimatedSprite.h"
#include "Actor.h"
#include "Game.h"

AnimatedSprite::AnimatedSprite(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
}

void AnimatedSprite::Update(float deltaTime)
{
	// TODO: Implement
    if(mAnimName.empty())
    {}
    else{
        std::unordered_map<std::string, std::vector<SDL_Texture*>>::iterator it= mAnims.find(mAnimName);
        if(mIsPaused==false)
        {
            mAnimTimer+=deltaTime*mAnimFPS;
            float size= it->second.size();
            while(mAnimTimer>=size)
            {
                mAnimTimer-=size;
            }
        }
        SetTexture(it->second[(int)mAnimTimer]);
    }
}

void AnimatedSprite::SetAnimation(const std::string& name, bool resetTimer)
{
	if (mAnimName != name)
	{
		mAnimName = name;
	}
	
	if (resetTimer)
	{
		mAnimTimer = 0.0f;
	}
}

void AnimatedSprite::AddAnimation(const std::string& name,
								  const std::vector<SDL_Texture*>& images)
{
	mAnims.emplace(name, images);
}
