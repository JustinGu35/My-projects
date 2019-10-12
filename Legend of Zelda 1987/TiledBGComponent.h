#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "SDL/SDL.h"

class TiledBGComponent : public SpriteComponent
{
public:
    TiledBGComponent(class Actor* owner, int drawOrder = 50);
    ~TiledBGComponent();
    void Draw(SDL_Renderer* renderer);
    void LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight);
    
    int tileWid;
    int tileHei;
    const int dimension=416;//dimension of the picture
    std::vector<std::vector<int>> storage;
};
