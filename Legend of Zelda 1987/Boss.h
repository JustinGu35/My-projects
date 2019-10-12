#include "Actor.h"

class Boss: public Actor
{
public:
    Boss(class Game* inGame);
    void OnUpdate(float deltaTime);
private:
    class AnimatedSprite* mAS;
    class CollisionComponent* mCC;
    class EnemyComponent* mEC;
    bool enraged;
    bool lastEnraged;
    float fireballTimer;
};
