#include "TiledBGComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <fstream>
#include "CSVHelper.h"
#include <string>

TiledBGComponent::TiledBGComponent(class Actor* owner, int drawOrder)
:SpriteComponent(owner,drawOrder)
{
    
}

TiledBGComponent::~TiledBGComponent()
{
    
}
void TiledBGComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        int num=dimension/tileWid;//number per row
        for(int i=0;i<storage.size();i++)
        {
            for(int j=0;j<storage[i].size();j++)
            {
                if(storage[i][j]!=-1)
                {
                    //destination
                    SDL_Rect r;
                       r.w = tileWid;
                       r.h = tileHei;
                       r.x = j*32-mOwner->GetGame()->camera.x;
                       r.y = i*32-mOwner->GetGame()->camera.y;
                    
                    //rectangle of the tile (source)
                        
                        SDL_Rect srcRect;
                        srcRect.w=tileWid;
                        srcRect.h=tileHei;
                    srcRect.x=(storage[i][j] % num) *32;
                    srcRect.y=(storage[i][j] / num) *32 ;
                        
                        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
                        SDL_RenderCopyEx(renderer,
                            mTexture,
                            &srcRect,
                            &r,
                            0.0,
                            nullptr,
                            SDL_FLIP_NONE);
                }
                
            }
        }
    }
}

void TiledBGComponent::LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight)
{
    tileWid=tileWidth;
    tileHei=tileHeight;
    
    
    std::ifstream input (fileName);
    if(input.fail())
    {
        SDL_Log("Fail to read");
    }
    while(!input.eof())
    {
        std::string tempL;
        std::getline(input,tempL);
        if(tempL.size()!=0)
        {
            std::vector<std::string> temp=CSVHelper::Split(tempL);
            std::vector<int> result;
            for(auto data: temp)
            {
                result.push_back(stoi(data));
            }
            storage.push_back(result);
        }
    }
}
