//
//  Spawner.h
//  Game-mac
//
//  Created by Runshi Gu on 9/21/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma

#include "Actor.h"
#include "SDL/SDL.h"
#include <string>

class Spawner : public Actor
{
public:
    Spawner(class Game* inGame);
    ~Spawner();
    void setType(std::string inType){type=inType;}
    std::string getType(){return type;}
    void activate();
private:
    std::string type;
};
