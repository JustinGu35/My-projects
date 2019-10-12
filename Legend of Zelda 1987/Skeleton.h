#include "Actor.h"

class Skeleton :public Actor
{
public:
    Skeleton(class Game* inGame);
    void OnUpdate(float deltaTime);
private:
    class AnimatedSprite* mAS;
    class CollisionComponent* mCC;
    class EnemyComponent* mEC;
    float timer;
};
