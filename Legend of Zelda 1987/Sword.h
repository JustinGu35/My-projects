#include "Actor.h"

class Sword: public Actor
{
public:
    Sword(class Game* inGame);
    class SpriteComponent* getSprite(){return mSC;}
private:
    class SpriteComponent* mSC;
    class CollisionComponent* mCC;
};
