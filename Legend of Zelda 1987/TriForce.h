#include "Actor.h"

class TriForce: public Actor
{
public:
    TriForce(class Game* inGame);
private:
    class AnimatedSprite* mAS;
    class CollisionComponent* mCC;
};
