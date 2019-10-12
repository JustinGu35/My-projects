//
//  Player.h
//  Game-mac
//
//  Created by Runshi Gu on 9/19/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma

#include "Actor.h"
#include "SDL/SDL.h"

class Player : public Actor
{
public:
    const int PLAYER_WIDTH=32;
    Player(class Game* inGame);
    ~Player();
    class CollisionComponent* mCC;
    void AddKey(){keys++;}
    int GetKey(){return keys;}
    void RemoveKey(){keys--;}
    void TakeDamage(int amount);
    void OnUpdate(float deltaTime);
private:
    class AnimatedSprite* mAS;
    class PlayerMove* mPM;
    int keys;
    int HitPoint;
    float invulnerabilityTimer;
};

