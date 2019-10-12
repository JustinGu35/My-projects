#include "Actor.h"
#include "Math.h"

class Bat :public Actor
{
public:
    Bat(class Game* inGame);
    void OnUpdate(float deltaTime);
private:
    const int SPEED=50;
    class AnimatedSprite* mAS;
    class CollisionComponent* mCC;
    class EnemyComponent* mEC;
    Vector2 direction;
    float timeElapsed;
};
